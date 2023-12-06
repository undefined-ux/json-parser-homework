#pragma once
#include <stddef.h>


struct JsonString {
	char* str;
	size_t length;
	size_t capacity;
};


struct JsonString* JsonStringFromCharArray(const char* str);
struct JsonString* JsonStringFromChar(const char c);
struct JsonString* JsonStringFromCharArraySlice(const char* start, const char* end);
struct JsonString* JsonString_New();

void JsonStringPushBackChar(const char c, struct JsonString* str);
void destoryJsonString(struct JsonString* str);
