#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

static FILE* f = 0;

void setInputStream(FILE* stream) { f = stream; }

void ignoreWhiteCharactor() {
	char c;
	while ((c = fgetc(f)) != EOF && (c == ' ' || c == '\r' || c == '\n' || c == '\t'));
	if (!(c == ' ' || c == '\r' || c == '\n' || c == '\t' || c == EOF)) { ungetc(c, f); }
}


struct JsonVal* parseValue() {
	ignoreWhiteCharactor();
	const char c = fgetc(f);
	if (c == '{') return parseObject();
	if (c == '[') return parseArray();
	if (c == 'n' || c == 'N') {
		ungetc(c, f);
		return parseNull();
	}
	if (c == 't' || c == 'T' || c == 'F' || c == 'f') {
		ungetc(c, f);
		return parseBool();
	}
	if (c <= '9' && c >= '0' || c == '-') {
		ungetc(c, f);
		return parseNumber();
	}
	if (c == '"' || c == '\'') return parseString(c);
	fprintf(
		stderr,
		"Unexcepted token %c at %llu",
		c, ftell(f) / sizeof(char)
	);
	exit(1);
}

struct JsonString* parseStringToStr(char token) {
	char c;
	struct JsonString* str = JsonString_New();
	const size_t pos = ftell(f) / sizeof(char);

	while ((c = fgetc(f)) && c != EOF && c != token) {
		if (c == '\\') {
			c = fgetc(f);
			if (c == EOF) {
				fprintf(stderr, "Unexpected EOF after escape character.\tString value parse begin with %llu\n", pos);
				exit(1);
			}
			switch (c) {
			case '"':
			case '\'':
			case '\\':
				JsonStringPushBackChar(c, str);
				break;
			case 'n':
				JsonStringPushBackChar('\n', str);
				break;
			case 't':
				JsonStringPushBackChar('\t', str);
				break;
			case 'u':
				JsonStringPushBackChar('\\', str);
				JsonStringPushBackChar('u', str);
				break;
			default:
				fprintf(stderr, "Invalid escape sequence: \\%c\tString value parse begin with %llu\n", c, pos);
				exit(1);
			}
		}
		else { JsonStringPushBackChar(c, str); }
	}

	if (c != token) {
		fprintf(stderr, "Expected character %c, but got EOF.\tString value parse begin with %llu\n", token, pos);
		exit(1);
	}
	return str;
}

struct JsonVal* parseString(char token) {
	struct JsonString* str = parseStringToStr(token);

	struct JsonVal* res = malloc(sizeof(struct JsonVal));
	if (res == NULL) {
		// Memory allocation failure (OOM)
		// Handle the error and exit
		exit(1);
	}

	res->type = STRING;
	res->val = str;
	return res;
}


struct JsonVal* parseNumber() {
	char c;
	struct JsonString* str = JsonString_New();
	int isFloat = 0, isNegative = 0;

	// 修复了循环条件，添加了对换行符和空格的判断
	while ((c = fgetc(f)) != EOF && ((c >= '0' && c <= '9') || c == '-' || c == '.')) {
		JsonStringPushBackChar(c, str);
		if (c == '-' && !isNegative) { isNegative = 1; }
		else if (c == '-' && isNegative) {
			fprintf(
				stderr,
				"Expected character [1-9], but got '.' at %llu",
				ftell(f) / sizeof(char)
			);
			exit(1);
		}
		if (c == '.' && !isFloat) { isFloat = 1; }
		else if (c == '.' && isFloat) {
			fprintf(
				stderr,
				"Expected character [1-9], but got '.' at %llu",
				ftell(f) / sizeof(char)
			);
			exit(1);
		}
	}

	struct JsonVal* res = malloc(sizeof(struct JsonVal));
	if (res == NULL) {
		// 内存分配失败
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
		const char trueStr[] = "true";
		for (int i = 1; i < 4; i++) {
			c = fgetc(f);
			if (c != trueStr[i] && c != trueStr[i] - 'a' + 'A') {
				fprintf(
					stderr,
					"Unexcepted value at %llu",
					ftell(f) / sizeof(char)
				); // 写入报错到标准错误流
				exit(1);
			}
		}
		c = fgetc(f);
		if (c != ' ' && c != '\n' && c != ',' && c != ']' && c != '}') {
			fprintf(
				stderr,
				"Unexcepted token %c at %llu",
				c, ftell(f) / sizeof(char)
			); // 写入报错到标准错误流
			exit(1);
		}
		ungetc(c, f);
		struct JsonVal* res = malloc(sizeof(struct JsonVal));
		if (res == NULL) {
			// 内存分配失败 OOM (?)
			// 异常退出， OS进行内存回收
			exit(1);
		}

		res->type = BOOL;
		res->val = JsonStringFromCharArray("true");
		return res;
	}
	else if (c == 'f' || c == 'F') {
		// false
		const char falseStr[] = "false";
		for (int i = 1; i < 5; i++) {
			c = fgetc(f);
			if (c != falseStr[i] && c != falseStr[i] - 'a' + 'A') {
				fprintf(
					stderr,
					"Unxcepted token %c at %llu",
					c, ftell(f) / sizeof(char)
				); // 写入报错到标准错误流
				exit(1);
			}
		}
		c = fgetc(f);
		if (c != ' ' && c != '\n' && c != ',' && c != ']' && c != '}') {
			fprintf(
				stderr,
				"Unxcepted token %c at %llu",
				c, ftell(f) / sizeof(char)
			); // 写入报错到标准错误流
			exit(1);
		}
		ungetc(c, f);
		struct JsonVal* res = malloc(sizeof(struct JsonVal));
		if (res == NULL) {
			// 内存分配失败 OOM (?)
			// 异常退出， OS进行内存回收
			exit(1);
		}
		res->type = BOOL;
		res->val = JsonStringFromCharArray("false");
		return res;
	}
	else {
		fprintf(
			stderr,
			"Unexcepted token %c at %llu",
			c, ftell(f) / sizeof(char)
		); // 写入报错到标准错误流
		exit(1);
	}
}


struct JsonVal* parseObject() {
	char c;
	struct JsonObj* obj = malloc(sizeof(struct JsonObj));
	struct JsonVal* res = malloc(sizeof(struct JsonVal));
	if (res == NULL) exit(1);
	if (obj == NULL) exit(1);
	res->type = OBJECT;

	const struct JsonString* keyVal = NULL;
	obj->size = 0;

	while ((c = fgetc(f)) != EOF && c != '}') {
		if (c == ' ' || c == '\n' || c == '\r' || c == ',') continue;
		if (c == '"' || c == '\'') keyVal = parseStringToStr(c);

		else if (c == ':') {
			const struct JsonVal* Val = parseValue();
			if(keyVal == NULL) {
				fprintf(stderr, "Unexcepted token %c at %llu", c, ftell(f) / sizeof(char));
				exit(1);
			}
			JsonObjInsert(obj, keyVal, Val); ignoreWhiteCharactor();
			c = fgetc(f);
			if(c != ',' && c != '}') {
				fprintf(stderr, "Unexcepted token %c at %llu", c, ftell(f) / sizeof(char));
				exit(1);
			}
			if(c == '}') {
				ungetc(c, f);
			}
		}
		else {
			fprintf(stderr, "Unexcepted token %c at %llu", c, ftell(f) / sizeof(char));
			exit(1);
		}
	}
	if (c != '}') {
		fprintf(stderr, "Unexcepted token EOF at %llu", ftell(f) / sizeof(char));
		exit(1);
	}
	res->obj = obj;
	return res;
}

struct JsonVal* parseArray() {
	struct JsonArray* arr = malloc(sizeof(struct JsonArray));
	struct JsonVal* res = malloc(sizeof(struct JsonVal));

	if (arr == NULL || res == NULL) exit(1);
	res->type = ARRAY;
	arr->length = 0;
	char c;
	ignoreWhiteCharactor(f);

	while ((c = fgetc(f)) != EOF && c != ']') {
		ignoreWhiteCharactor();
		if (c != ',') ungetc(c, f);
		struct JsonVal* val = parseValue();
		JsonArrayPushBack(arr, val);

		ignoreWhiteCharactor();
	}
	if (c != ']') {
		fprintf(stderr, "Unexcepted token EOF at %llu", ftell(f) / sizeof(char));
		exit(1);
	}
	res->arr = arr;
	return res;
}

struct JsonVal* parseNull() {
	const char nullStr[] = "null";
	char c;
	for (int i = 0; i < 4; i++) {
		c = fgetc(f);
		if (c != nullStr[i] && c != nullStr[i] - 'a' + 'A') {
			fprintf(
				stderr,
				"Unexcepted token %c at %llu",
				c, ftell(f) / sizeof(char)
			); // 写入报错到标准错误流
			exit(1);
		}
	}
	c = fgetc(f);
	if (c != ' ' && c != '\n' && c != ',' && c != ']' && c != '}') {
		fprintf(
			stderr,
			"Unexcepted token %c at %llu",
			c, ftell(f) / sizeof(char)
		); // 写入报错到标准错误流
		exit(1);
	}
	ungetc(c, f);
	struct JsonVal* res = (struct JsonVal*)malloc(sizeof(struct JsonVal));
	if (res == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	res->type = BOOL;
	res->val = JsonStringFromCharArray("false");
	return res;
}
