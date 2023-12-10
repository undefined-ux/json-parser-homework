#include "JsonString.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


struct JsonString* JsonStringFromCharArray(const char* str) {
	const size_t strlength = strlen(str);
	if (!strlength) {
		// 空字符串
		return JsonString_New();
	}
	struct JsonString* res = (struct JsonString*) malloc(sizeof(struct JsonString));
	if (res == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	res->capacity = strlength + 1;
	res->length = strlength;
	res->str = (char*)malloc(sizeof(char) * res->capacity);
	if (res->str == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	strncpy(res->str, str, strlength);
	res->str[strlength] = 0;
	return res;
}

struct JsonString* JsonStringFromChar(const char c)
{
	struct JsonString* res = (struct JsonString*)malloc(sizeof(struct JsonString));
	if (res == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	res->capacity = 10;
	res->length = 1;
	res->str = (char*)malloc(sizeof(char) * res->capacity);
	if (res->str == NULL) {
		// 这逼玩意最后必须要封装出来
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	sprintf(res->str, "%c", c);

	return res;
}

struct JsonString* JsonString_New() {
	struct JsonString* res = malloc(sizeof(struct JsonString));
	if (res == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	res -> capacity = 10;
	res -> length = 0;
	res -> str = (char*)malloc(sizeof(char) * res->capacity);
	if (res->str == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	(res->str)[0] = 0;
	return res;
}

/// <summary>
/// 将字符串切片char[start: end)转换为生成JsonString类型。
/// end指针于C++STL迭代器.end()相同， 指向位置将不纳入JsonString范围
/// 长度为end - start + 1；（末尾补0)
/// </summary>
/// <param name="start">起始位置指针</param>
/// <param name="end">末尾位置后一位的指针</param>
/// <returns>struct JsonString* </returns>

struct JsonString* JsonStringFromCharArraySlice(char* start, const char* end) {
	size_t length = 0;
	for (char* s = start; s != end; s++) length++; length++;// 末尾补零用
	struct JsonString* res = malloc(sizeof(struct JsonString));
	if (res == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	res->capacity = length; res->length = length - 1; 
	res->str = (char*)malloc(sizeof(char) * length);
	if (res->str == NULL) {
		// 内存分配失败 OOM (?)
		// 异常退出， OS进行内存回收
		exit(1);
	}
	char* writer = res->str; // 单独声明， 后续方便补零
	for (char* reader = start; reader != end; reader++, writer++) 
		*writer = *reader;
	*writer = 0; // for循环中已自增至字符串未应补0处
	return res;
}



void JsonStringPushBackChar(const char c, struct JsonString* str) {
	if (str->length + 2 > str->capacity) {
		str->capacity = str->length + 5;
		if (str->str == NULL) {
			// 野指针
			// 异常退出， OS进行内存回收
			exit(1);
		}
		str -> str = (char*) realloc(str->str, sizeof(char) * str->capacity);
		if (str->str == NULL) {
			// 内存分配失败 OOM (?)
			// 异常退出， OS进行内存回收
			exit(1);
		}
	}
	str->str[str->length] = c; str->str[str->length + 1] = 0;
	str->length++;
}


void destoryJsonString(struct JsonString* str) {
	free(str->str); free(str);
}