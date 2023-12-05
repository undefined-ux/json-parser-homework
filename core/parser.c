#pragma once
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

static FILE* f = 0;

void setInputStream(FILE* stream) { f = stream; }

void ignoreWhiteCharactor() {
	char c;
	while (
		(c = fgetc(f)) != EOF &&
		(c == ' ' || c == '\r' || c == '\n')
		);
	if (!feof(f)) {
		fseek(f, -sizeof(char), SEEK_CUR);
	}
}


struct JsonVal* parseValue() {
	char c = fgetc(f);
	if (c == '{') return parseObject();
	else if (c == '[') return parseArray();
	else if (c == 'n') return parseNull();
	else if (c == 't' || c == 'f') {
		fseek(f, -sizeof(char), SEEK_CUR);
		return parseBool();
	}
	else if (c <= '9' && c >= '0') {
		fseek(f, -sizeof(char), SEEK_CUR); 
		return parseNumber();
	}
	else if (c == '"' || c == '\'') return parseString();
	else {
		fprintf(
			stderr,
			"Unexcepted token %c at %ld",
			c, ftell(f)
		); exit(1);
	}
}

struct JsonVal* parseString() {
	char c; struct JsonString* str = JsonString_New();
	size_t pos = ftell(f) / sizeof(char);
	while ((c = fgetc(f)) && c != EOF && c != '"' && c != '\'') 
		JsonStringPushBackChar(c, str);
	if (c != '"' && c != '\'') {
		fprintf(
			stderr, 
			"Excepted charactor \" or ', but got EOF.\tString value parse begin with %llu\n",
			pos
		); // 写入报错到标准错误流
		exit(1);
	}
	struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
	if (res == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	res->type = STRING; res->val = str;
	return res;
}


struct JsonVal* parseNumber() {
	char c; struct JsonString* str = JsonString_New();
	int isFloat = 0;
	while ((c = fgetc(f)) && c != EOF && c != ',') {
		JsonStringPushBackChar(c, str);
		if (c == '.' && !isFloat) isFloat = 1;
		else if (c == '.' && isFloat) {
			fprintf(
				stderr,
				"Excepted charactor [1-9], but got '.' at %ld",
				ftell(f)
			); // 写入报错到标准错误流
			exit(1);
		}
	}
	struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
	if (res == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	res->type = NUMBER; res->val = str;
	return res;
}

struct JsonVal* parseBool() {
	char c; 
	// true or false
	
	if ((c = fgetc(f)) == 't' || c == 'T') {
		// true
		char trueStr[] = "true";
		for (int i = 1; i < 4; i++) {
			c = fgetc(f);
			if (c != trueStr[i] && c != trueStr[i] - 'a' + 'A') {
				fprintf(
					stderr,
					"Excepted value at %ld",
					ftell(f)
				); // 写入报错到标准错误流
				exit(1);
			}
		}
		c = fgetc(f);
		if (c != ' ' && c != '\n' && c != ',' && c != ']' && c != '}') {
			fprintf(
				stderr,
				"Excepted token %c at %ld",
				c, ftell(f)
			); // 写入报错到标准错误流
			exit(1);
		}
		fseek(f, -sizeof(char), SEEK_CUR);
		struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
		if (res == NULL) {
			// 内存分配失败 OOM (?)
			// 异常退出， OS进行内存回收
			exit(1);
		}
		res->type = BOOL; res->val = JsonStringFromCharArray("true");
		return res;
	}
	else if (c == 'f' || c == 'F') {
		// false
		char falseStr[] = "false";
		for (int i = 1; i < 5; i++) {
			c = fgetc(f);
			if (c != falseStr[i] && c != falseStr[i] - 'a' + 'A') {
				fprintf(
					stderr,
					"Excepted token %c at %ld",
					c, ftell(f)
				); // 写入报错到标准错误流
				exit(1);
			}
		}
		c = fgetc(f);
		if (c != ' ' && c != '\n' && c != ',' && c != ']' && c != '}') {
			fprintf(
				stderr,
				"Excepted token %c at %ld",
				c, ftell(f)
			); // 写入报错到标准错误流
			exit(1);
		}
		fseek(f, -sizeof(char), SEEK_CUR);
		struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
		if (res == NULL) {
			// 内存分配失败 OOM (?)
			// 异常退出， OS进行内存回收
			exit(1);
		}
		res->type = BOOL; res->val = JsonStringFromCharArray("false");
		return res;
	}
	else {
		fprintf(
			stderr,
			"Unexcepted token %c at %ld",
			c, ftell(f)
		); // 写入报错到标准错误流
		exit(1);
	}
}


struct JsonVal* parseObject() {
	// "KEY" : VALUE,
	char c;
	struct JsonObj* obj = (struct JsonObj*)malloc(sizeof(struct JsonObj));
	struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
	if (res == NULL) exit(1); if (obj == NULL) exit(1);
	res->type = OBJECT;
	
	struct JsonString* keyVal = NULL;
	obj->size = 0; int isClosed = 0;

	while ((c = fgetc(f)) != EOF && c != '}') {
		if (c == " " || c == "\n" || c == "\r" || c == ',') continue;
		else if (c == '"' || c == '\'') keyVal = parseString()->val;
		else if (keyVal != NULL && c == ':') JsonObjInsert(obj, keyVal, parseValue());
		else {
			fprintf(stderr, "Unexcepted token %c at %ld", c, ftell(f));
		}
	}
	if (c != '}') {
		fprintf(stderr, "Unexcepted token EOF at %ld", ftell(f));
	}
	res->obj = obj;
	return res;
}

struct JsonVal* parseArray() {
	struct JsonArray* arr = (struct JsonArray*)malloc(sizeof(struct JsonArray));
	struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
	if (arr == NULL) exit(1); if (res == NULL) exit(1);
	res->type = ARRAY; arr->length = 0; 
	char c;
	while ((c = fgetc(f)) != EOF && c != ']') {
		ignoreWhiteCharactor(); JsonArrayPushBack(arr, parseValue());
	}
	if (c != ']') {
		fprintf(stderr, "Unexcepted token EOF at %ld", ftell(f));
	}
	res->arr = arr;
	return res;
}

struct JsonVal* parseNull() {
	char nullStr[] = "null", c;
	for (int i = 1; i < 5; i++) {
		c = fgetc(f);
		if (c != nullStr[i] && c != nullStr[i] - 'a' + 'A') {
			fprintf(
				stderr,
				"Excepted token %c at %ld",
				c, ftell(f)
			); // 写入报错到标准错误流
			exit(1);
		}
	}
	c = fgetc(f);
	if (c != ' ' && c != '\n' && c != ',' && c != ']' && c != '}') {
		fprintf(
			stderr,
			"Excepted token %c at %ld",
			c, ftell(f)
		); // 写入报错到标准错误流
		exit(1);
	}
	fseek(f, -sizeof(char), SEEK_CUR);
	struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
	if (res == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	res->type = BOOL; res->val = JsonStringFromCharArray("false");
	return res;
}
