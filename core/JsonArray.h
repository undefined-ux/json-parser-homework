#pragma once

#include "JsonValue.h"
#include <stdio.h>

typedef struct JsonArray {
	JsonVal* arr;
	size_t length;
} JsonArray;


void printfArray(JsonArray* array){
	printf("[");
	if (array->length > 3) printf("\n");
	for (int i = 0; i < array->length; i++) {
		printJsonVal(&(array->arr)[i]);
		if (i != array->length - 1) printf(", ");
		if (array->length > 3) printf("\n");
	}printf("]");
}