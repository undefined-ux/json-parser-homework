#pragma once

#include "JsonString.h"
#include "JsonValue.h"

struct JsonObj {
	size_t size;
	struct JsonString* key;
	struct JsonVal* value;
};


void JsonObjInsert(struct JsonObj* obj, const struct JsonString* key, const struct JsonVal* value);