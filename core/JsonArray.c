#include "JsonArray.h"

void printfArray(struct JsonArray* array) {
	printf("[");
	if (array->length > 3) printf("\n");
	for (int i = 0; i < array->length; i++) {
		printf("\t");
		printJsonVal(&((array->arr)[i]));
		if (i != array->length - 1) printf(", ");
		if (array->length > 3) printf("\n");
	}printf("]");
}