#pragma once

#include "JsonValue.h"
#include <stdio.h>

struct JsonArray {
	struct JsonVal* arr;
	size_t length;
};


struct JsonArray* JsonArrayFromArray(struct JsonVal* arr, size_t length);
struct JsonArray* JsonArrayNew();

void destroyJsonArray(struct JsonArray* arr);