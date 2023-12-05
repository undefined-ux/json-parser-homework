#pragma once

#include "JsonValue.h"
#include <stdio.h>

struct JsonArray {
	struct JsonVal* arr;
	size_t length;
};


void printfArray(struct JsonArray* array);