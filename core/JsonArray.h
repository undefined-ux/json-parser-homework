#pragma once

#include "JsonValue.h"


typedef struct JsonArray {
	JsonVal* arr;
	size_t length;
} JsonArray;