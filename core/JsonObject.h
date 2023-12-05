#pragma once

#include "JsonString.h"
#include "JsonValue.h"

typedef struct JsonObj {
	size_t size;
	JsonString* key;
	JsonVal* value;
} JsonObj;