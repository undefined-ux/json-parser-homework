#include "JsonString.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>


struct JsonString* JsonStringFromCharArray(const char* str) {
	size_t strlength = strlen(str);
	if (!strlength) {
		// ���ַ���
		return JsonString_New();
	}
	struct JsonString* res = (struct JsonString*) malloc(sizeof(struct JsonString));
	if (res == NULL) {
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	res->capacity = strlength + 1;
	res->length = strlength;
	res->str = (char*)malloc(sizeof(char) * res->capacity);
	if (res->str == NULL) {
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
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
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	res->capacity = 10;
	res->length = 1;
	res->str = (char*)malloc(sizeof(char) * res->capacity);
	if (res->str == NULL) {
		// �������������Ҫ��װ����
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	sprintf(res->str, "%c", c);

	return res;
}

struct JsonString* JsonString_New() {
	struct JsonString* res = (struct JsonString*)malloc(sizeof(struct JsonString));
	if (res == NULL) {
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	res -> capacity = 10;
	res -> length = 0;
	res -> str = (char*)malloc(sizeof(char) * res->capacity);
	if (res->str == NULL) {
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	(res->str)[0] = 0;
	return res;
}

/// <summary>
/// ���ַ�����Ƭchar[start: end)ת��Ϊ����JsonString���͡�
/// endָ����C++STL������.end()��ͬ�� ָ��λ�ý�������JsonString��Χ
/// ����Ϊend - start + 1����ĩβ��0)
/// </summary>
/// <param name="start">��ʼλ��ָ��</param>
/// <param name="end">ĩβλ�ú�һλ��ָ��</param>
/// <returns>struct JsonString* </returns>

struct JsonString* JsonStringFromCharArraySlice(const char* start, const char* end) {
	size_t length = 0;
	for (char* s = start; s != end; s++) length++; length++;// ĩβ������
	struct JsonString* res = (struct JsonString*)malloc(sizeof(struct JsonString));
	if (res == NULL) {
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	res->capacity = length; res->length = length - 1; 
	res->str = (char*)malloc(sizeof(char) * length);
	if (res->str == NULL) {
		// �ڴ����ʧ�� OOM (?)
		// �쳣�˳��� OS�����ڴ����
		exit(1);
	}
	char* writer = res->str; // ���������� �������㲹��
	for (char* reader = start; reader != end; reader++, writer++) 
		*writer = *reader;
	*writer = 0; // forѭ�������������ַ���δӦ��0��
	return res;
}



void JsonStringPushBackChar(const char c, struct JsonString* str) {
	if (str->length + 2 > str->capacity) {
		str->capacity = str->length + 5;
		if (str->str == NULL) {
			// Ұָ��
			// �쳣�˳��� OS�����ڴ����
			exit(1);
		}
		str -> str = (char*) realloc(str->str, sizeof(char) * str->capacity);
		if (str->str == NULL) {
			// �ڴ����ʧ�� OOM (?)
			// �쳣�˳��� OS�����ڴ����
			exit(1);
		}
	}
	str->str[str->length] = c; str->str[str->length + 1] = 0;
	str->length++;
}


void destoryJsonString(struct JsonString* str) {
	free(str->str); free(str);
}