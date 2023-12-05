#pragma once
#include "JsonObject.h"
#include "JsonString.h"
#include "JsonValue.h"
#include "JsonArray.h"

FILE* f = stdout;

void setOutputStream(FILE* stream) { f = stream; }
void printString(const struct JsonString* str);
void printfJsonVal(struct JsonVal* val, int hierarchy);
void printJsonVal(struct JsonVal* val);
void printfObject(const struct JsonObj* obj, int hierarchy);
void printfArray(const struct JsonArray* array, int hierarchy);
void printNONE();
void printBool(const struct JsonString* bl);
void printNumber(const struct JsonString* num);
void printObject(const struct JsonObj* obj);
void printArray(const struct JsonArray* array);