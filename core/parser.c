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
		(c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == '\r')
		);
	if (!(c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == '\r' || c == EOF)) {
		ungetc(c, f);
	}
}


struct JsonVal* parseValue() {
	ignoreWhiteCharactor();
	char c = fgetc(f);
	if (c == '{') return parseObject();
	else if (c == '[') return parseArray();
	else if (c == 'n' || c == 'N') {
		ungetc(c, f);
		return parseNull();
	}
	else if (c == 't' || c == 'T' || c == 'F' || c == 'f') {
		ungetc(c, f);
		return parseBool();
	}
	else if (c <= '9' && c >= '0' || c == '-') {
		ungetc(c, f);
		return parseNumber();
	}
	else if (c == '"' || c == '\'') return parseString();
	else {
		fprintf(
			stderr,
			"Unexcepted token %c at %llu",
			c, ftell(f) / sizeof(char)
		); exit(1);
	}
}

struct JsonVal* parseString() {
	char c; struct JsonString* str = JsonString_New();
	size_t pos = ftell(f) / sizeof(char);
	while ((c = fgetc(f)) && c != EOF && c != '"' && c != '\'') {
		JsonStringPushBackChar(c, str);
	}
		
	if (c != '"' && c != '\'') {
		fprintf(
			stderr, 
			"Excepted charactor \" or ', but got EOF.\tString value parse begin with %llu\n",
			pos
		); // д�뱨������׼������
		exit(1);
	}
	struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
	if (res == NULL) {
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	res->type = STRING; res->val = str;
	return res;
}


struct JsonVal* parseNumber() {
	char c;
	struct JsonString* str = JsonString_New();
	int isFloat = 0 , isNegative = 0;

	// �޸���ѭ�������������˶Ի��з��Ϳո���ж�
	while ((c = fgetc(f)) != EOF && ((c >= '0' && c <= '9') || c == '-' || c == '.')) {
		JsonStringPushBackChar(c, str);
		if (c == '-' && !isNegative) {
			isNegative = 1;
		}
		else if (c == '-' && isNegative) {
			fprintf(
				stderr,
				"Expected character [1-9], but got '.' at %llu",
				ftell(f) / sizeof(char)
			);
			exit(1);
		}
		if (c == '.' && !isFloat) {
			isFloat = 1;
		}
		else if (c == '.' && isFloat) {
			fprintf(
				stderr,
				"Expected character [1-9], but got '.' at %llu",
				ftell(f) / sizeof(char)
			);
			exit(1);
		}
	}

	struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
	if (res == NULL) {
		// �ڴ����ʧ��
		exit(1);
	}
	ungetc(c, f);
	res->type = NUMBER;
	res->val = str;
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
					"Unexcepted value at %llu",
					ftell(f) / sizeof(char)
				); // д�뱨������׼������
				exit(1);
			}
		}
		c = fgetc(f);
		if (c != ' ' && c != '\n' && c != ',' && c != ']' && c != '}') {
			fprintf(
				stderr,
				"Unexcepted token %c at %llu",
				c, ftell(f) / sizeof(char)
			); // д�뱨������׼������
			exit(1);
		}
		ungetc(c, f);
		struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
		if (res == NULL) {
			// �ڴ����ʧ�� OOM (?)
			// �쳣�˳��� OS�����ڴ����
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
					"Unxcepted token %c at %llu",
					c, ftell(f) / sizeof(char)
				); // д�뱨������׼������
				exit(1);
			}
		}
		c = fgetc(f);
		if (c != ' ' && c != '\n' && c != ',' && c != ']' && c != '}') {
			fprintf(
				stderr,
				"Unxcepted token %c at %llu",
				c, ftell(f) / sizeof(char)
			); // д�뱨������׼������
			exit(1);
		}
		ungetc(c, f);
		struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
		if (res == NULL) {
			// �ڴ����ʧ�� OOM (?)
			// �쳣�˳��� OS�����ڴ����
			exit(1);
		}
		res->type = BOOL; res->val = JsonStringFromCharArray("false");
		return res;
	}
	else {
		fprintf(
			stderr,
			"Unexcepted token %c at %llu",
			c, ftell(f) / sizeof(char)
		); // д�뱨������׼������
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
		if (c == ' ' || c == '\n' || c == '\r' || c == ',') continue;
		else if (c == '"' || c == '\'') keyVal = parseString()->val;
		else if (keyVal != NULL && c == ':') JsonObjInsert(obj, keyVal, parseValue());
		else {
			fprintf(stderr, "Unexcepted token %c at %llu", c, ftell(f) / sizeof(char)); exit(1);
		}
	}
	if (c != '}') {
		fprintf(stderr, "Unexcepted token EOF at %llu", ftell(f) / sizeof(char)); exit(1);
	}
	res->obj = obj;
	return res;
}

struct JsonVal* parseArray() {
	struct JsonArray* arr = (struct JsonArray*)malloc(sizeof(struct JsonArray));
	struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));

	if (arr == NULL || res == NULL) exit(1);
	res->type = ARRAY; arr->length = 0; 
	char c;
	ignoreWhiteCharactor(f);

	while ((c = fgetc(f)) != EOF && c != ']') {
		ignoreWhiteCharactor();

		if (arr->length > 0) {
			if (c == ',') {
				ignoreWhiteCharactor();
			}
			else {
				fprintf(stderr, "Expected ',' but got '%c' at %llu\n", c, ftell(f) / sizeof(char));
				exit(1);
			}
		}

		if(c != ',') ungetc(c, f);
		struct JsonVal* val = parseValue();
		JsonArrayPushBack(arr, val);

		ignoreWhiteCharactor();
	}
	if (c != ']') {
		fprintf(stderr, "Unexcepted token EOF at %llu", ftell(f) / sizeof(char)); exit(1);
	}
	res->arr = arr;
	return res;
}

struct JsonVal* parseNull() {
	char nullStr[] = "null", c;
	for (int i = 0; i < 4; i++) {
		c = fgetc(f);
		if (c != nullStr[i] && c != nullStr[i] - 'a' + 'A') {
			fprintf(
				stderr,
				"Unexcepted token %c at %llu",
				c, ftell(f) / sizeof(char)
			); // д�뱨������׼������
			exit(1);
		}
	}
	c = fgetc(f);
	if (c != ' ' && c != '\n' && c != ',' && c != ']' && c != '}') {
		fprintf(
			stderr,
			"Unexcepted token %c at %llu",
			c, ftell(f) / sizeof(char)
		); // д�뱨������׼������
		exit(1);
	}
	ungetc(c, f);
	struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
	if (res == NULL) {
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	res->type = BOOL; res->val = JsonStringFromCharArray("false");
	return res;
}