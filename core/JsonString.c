#include "JsonString.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

struct JsonString* JsonStringFromCharArray(const char* str) {
	size_t strlength = strlen(str) + 1;
	if (strlength == 1) {
		// ¿Õ×Ö·û´®
		return JsonString_New();
	}
	struct JsonString* res = (struct JsonString*) malloc(sizeof(struct JsonString));
	res->capacity = strlength;
	res->length = strlength;
	res->str = (char*)malloc(sizeof(char) * strlength);
	strncpy(res->str, str, strlength);

	return res;
}

struct JsonString* JsonStringFromChar(const char c)
{
	struct JsonString* res = (struct JsonString*)malloc(sizeof(struct JsonString));
	res->capacity = 10;
	res->length = 2;
	res->str = (char*)malloc(sizeof(char) * res->capacity);
	sprintf(res->str, "%c", c);

	return res;
}

struct JsonString* JsonString_New() {
	struct JsonString* res = (struct JsonString*)malloc(sizeof(struct JsonString));
	res -> capacity = 10;
	res -> length = 1;
	res -> str = (char*)malloc(sizeof(char) * res->length);
	(res->str)[0] = 0;
	return res;
}
void printfString(const struct JsonString* str){
	if (!str->length) {
		printf("");
	}
	else {
		printf("\"%s\"", str->str);
	}
}
