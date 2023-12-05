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
	struct JsonVal* valArr = malloc(sizeof(struct JsonVal) * 4);
	valArr[0].type = ARRAY; valArr[0].arr = &arr;
	valArr[1].type = STRING; valArr[1].val = JsonStringFromCharArray("Test");
	valArr[2].type = BOOL; valArr[2].val = JsonStringFromCharArray("True");
	valArr[3].type = NONE;

	struct JsonString* keyArr = malloc(sizeof(struct JsonString) * 4);
	keyArr[0] = *JsonStringFromCharArray("ArrayKey");
	keyArr[1] = *JsonStringFromCharArray("StringKey");
	keyArr[2] = *JsonStringFromCharArray("BoolKey");
	keyArr[3] = *JsonStringFromCharArray("NoneKey");

	struct JsonObj obj = {
		4, keyArr, valArr
	};
	printfObject(&obj, 0);
	return 0;
}