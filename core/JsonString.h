#pragma once
#include <stddef.h>


struct JsonString {
	char* str;
	size_t length;
	size_t capacity;
};


void printfString(const struct JsonString* str);
struct JsonString* JsonStringFromCharArray(const char* str);
struct JsonString* JsonStringFromChar(const char c);
struct JsonString* JsonString_New();