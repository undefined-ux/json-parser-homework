#pragma once


typedef struct JsonString {
	char* str;
	size_t length;
	size_t capacity;
} JsonString;