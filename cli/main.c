#include <stdio.h>
#include <stdlib.h>

#include "Json.h"

int main() {
	struct JsonArray arr;
	arr.arr = (struct JsonVal *) malloc(sizeof(struct JsonVal) * 10);
	arr.length = 10;
	for (int i = 0; i < 10; i++) {
		arr.arr[i].type = NUMBER;
		arr.arr[i].val = JsonStringFromChar((char)(i + '0'));
	}

	printfArray(&arr);
	return 0;
}