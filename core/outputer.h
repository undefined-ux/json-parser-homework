#pragma once
#include "JsonObject.h"
#include "JsonString.h"
#include "JsonValue.h"
#include "JsonArray.h"

void printfString(const struct JsonString* str);
void printJsonVal(struct JsonVal* val, int hierarchy);
void printfObject(const struct JsonObj* obj, int hierarchy);
void printfArray(const struct JsonArray* array, int hierarchy);
void printfNONE();
void printfBool(const struct JsonString* bl);
void printfNumber(const struct JsonString* num);