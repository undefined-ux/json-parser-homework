#pragma once
#include "Json.h"


void setInputStream(FILE* stream);
struct JsonVal* parseString();
struct JsonVal* parseNumber();
struct JsonVal* parseBool();
struct JsonVal* parseNull();
struct JsonVal* parseArray();
struct JsonVal* parseObject();
struct JsonVal* parseValue();