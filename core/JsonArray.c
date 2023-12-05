#include "JsonArray.h"

#include <stdlib.h>

struct JsonArray* JsonArrayFromArray(struct JsonVal* arr, size_t length)
{
	struct JsonArray* res = (struct JsonArray*)malloc(sizeof(struct JsonArray));
	if (res == NULL) { // From JsonString
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	res->length = length; 
	res->arr =(struct JsonVal* ) malloc(sizeof(struct JsonVal) * length);
	if (arr != NULL) {
		// 深拷贝 arr后续是否会被析构未知
		for (size_t i = 0; i < length; i++) (res->arr)[i] = arr[i]; 
	}
	
	return res;
}

struct JsonArray* JsonArrayNew()
{
	struct JsonArray* arr = (struct JsonArray*)malloc(sizeof(struct JsonArray));
	if (arr == NULL) { // From JsonString
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	arr->length = 10; arr->arr =(struct JsonVal*) malloc(sizeof(struct JsonVal));
	return arr;
}

void destroyJsonArray(struct JsonArray* arr) {
	if (arr == NULL) return;
	for (size_t i = 0; i < arr->length; i++) 
		if(arr->arr + i != NULL) 
			free(arr->arr + i); // Avoid double free
	free(arr);
}
