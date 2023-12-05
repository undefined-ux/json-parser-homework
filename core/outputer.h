#pragma once
#include "JsonObject.h"
#include "JsonString.h"
#include "JsonValue.h"
#include "JsonArray.h"

void printfString(const struct JsonString* str);
void printJsonVal(const struct JsonVal* val);
void printfObject(const struct JsonObj* obj);
void printfArray(const struct JsonArray* array);