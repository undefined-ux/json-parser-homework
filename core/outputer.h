#pragma once
#include "JsonObject.h"
#include "JsonString.h"
#include "JsonValue.h"
#include "JsonArray.h"

void setOutputStream(FILE* stream);
void printString(const struct JsonString* str);
void printfJsonVal(const struct JsonVal* val, int hierarchy);
void printJsonVal(const struct JsonVal* val);
void printfObject(const struct JsonObj* obj, int hierarchy);
void printfArray(const struct JsonArray* array, int hierarchy);
void printNONE();
void printBool(const struct JsonString* bl);
void printNumber(const struct JsonString* num);
void printObject(const struct JsonObj* obj);
void printArray(const struct JsonArray* array);