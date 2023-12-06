#include "JsonArray.h"

#include <stdlib.h>

struct JsonArray* JsonArrayFromArray(struct JsonVal* arr, size_t length)
{
	struct JsonArray* res = (struct JsonArray*)malloc(sizeof(struct JsonArray));
	if (res == NULL) { // From JsonString
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	res->length = length; 
	res->arr =(struct JsonVal* ) malloc(sizeof(struct JsonVal) * length);
	if (res->arr == NULL) {
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	if (arr != NULL) {
		// ��� arr�����Ƿ�ᱻ����δ֪
		for (size_t i = 0; i < length; i++) (res->arr)[i] = arr[i]; 
	}
	
	return res;
}

struct JsonArray* JsonArrayNew()
{
	struct JsonArray* arr = (struct JsonArray*)malloc(sizeof(struct JsonArray));
	if (arr == NULL) { // From JsonString
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	arr->length = 10; arr->arr =(struct JsonVal*) malloc(sizeof(struct JsonVal));
	return arr;
}


void JsonArrayPushBack(struct JsonArray* arr, struct JsonVal* val) {
	arr->length++;
	struct JsonVal* tempArr = (struct JsonVal*)malloc(sizeof(struct JsonArray) * arr->length);
	if (tempArr == NULL) exit(1);
	for (size_t i = 0; i < arr->length - 1; i++) tempArr[i] = arr->arr[i];
	arr->arr = tempArr;
	arr->arr[arr->length - 1] = *val;
}

void destoryJsonArray(struct JsonArray* arr) {
	if (arr == NULL) return;
	for (size_t i = 0; i < arr->length; i++) 
		if(arr->arr + i != NULL) 
			free(arr->arr + i); // Avoid double free
	free(arr);
}
