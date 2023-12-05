#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#include "Json.h"

int main() {
	setlocale(LC_ALL, ""); // 设置本地化环境以支持宽字符
	// Initalize A Json Object
	setOutputStream(stdout);
	setInputStream(fopen("d:\\test.txt", "r+"));
	struct JsonArray arr;
	arr.arr = (struct JsonVal*)malloc(sizeof(struct JsonVal) * 10);
	arr.length = 10;
	for (int i = 0; i < 10; i++) {
		arr.arr[i].type = NUMBER;
		arr.arr[i].val = JsonStringFromChar((char)(i + '0'));
	}
	struct JsonVal v = {
		STRING, JsonStringFromCharArray("Test")
	};
	struct JsonObj objVal = {
		1, JsonStringFromCharArray("key"), &v
	};
	struct JsonVal* valArr = malloc(sizeof(struct JsonVal) * 5);
	valArr[0].type = ARRAY; valArr[0].arr = &arr;
	valArr[1].type = STRING; valArr[1].val = JsonStringFromCharArray("Test");
	valArr[2].type = BOOL; valArr[2].val = JsonStringFromCharArray("True");
	valArr[3].type = NONE;
	valArr[4].type = OBJECT; valArr[4].obj = &objVal;

	struct JsonString* keyArr = malloc(sizeof(struct JsonString) * 5);
	keyArr[0] = *JsonStringFromCharArray("ArrayKey");
	keyArr[1] = *JsonStringFromCharArray("StringKey");
	keyArr[2] = *JsonStringFromCharArray("布尔值");
	keyArr[3] = *JsonStringFromCharArray("NoneKey");
	keyArr[4] = *JsonStringFromCharArray("ObjectKey");
	struct JsonObj obj = {
		5, keyArr, valArr
	};
	//printfObject(&obj, 0); printf("\n");
	//printObject(&obj);
	printBool(parseBool());

	return 0;
}