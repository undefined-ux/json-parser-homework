#pragma once

#include "JsonString.h"
#include "JsonValue.h"

struct JsonObj {
	size_t size;
	struct JsonString* key;
	struct JsonVal* value;
};


