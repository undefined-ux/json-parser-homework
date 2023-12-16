#pragma once
#include "../types/JsonString.h"
#include "../types/JsonValue.h"
#include "../types/JsonArray.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void setOutputStream(FILE* stream);
void printString(const struct JsonString* str, const int color);
void printfJsonVal(const struct JsonVal* val, int hierarchy, const int color);
void printJsonVal(const struct JsonVal* val, const int color);
void printfObject(const struct JsonObj* obj, int hierarchy, const int color);
void printfArray(const struct JsonArray* array, int hierarchy, const int color);
void printNONE(const int color);
void printBool(const struct JsonString* bl, const int color);
void printNumber(const struct JsonString* num, const int color);
void printObject(const struct JsonObj* obj, const int color);
void printArray(const struct JsonArray* array, const int color);