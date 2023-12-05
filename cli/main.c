#include <stdio.h>
#include <stdlib.h>

#include "JsonArray.h"
#include "JsonObject.h"


int main() {
	struct JsonArray arr;
	arr.arr = (struct JsonVal *) malloc(sizeof(struct JsonVal) * 10);
	arr.length = 10;
	for (int i = 0; i < 10; i++) {
		arr.arr[i].type = NUMBER;
		char s = i + '0';
		arr.arr[i].val = &s;
	}

	printfArray(&arr);
	return 0;
}