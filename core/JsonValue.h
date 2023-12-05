#pragma once

#include "JsonArray.h"

typedef enum {
	STRING,
	NUMBER,
	BOOL,
	ARRAY,
	OBJECT,
	NONE
} JsonType;

/// <summary>
/// Json����ֵ
/// char* val ����String�� Number�� None�� Bool����
/// ��Ϊ�����������ʽ����ѹ�����﷨��鹦�ܣ� ��������ֵ�Ķ������ݣ� 
/// ����ʹ���ַ�����ʾʵ��Number�����ͣ� ���ٺ��ڿ���ѹ���� ����洢ֵ
/// ����Json��JavaScript�Դ��߾���JSON��������Number��С�����ȡ�����JSON��Number������ʵ�ָ߾�
/// Type�����JsonType�� �����ж���ʽ��ʹ�ö�Ӧ�������
/// </summary>
typedef struct JsonVal {
	JsonType type;
	union {
		char* val; // String, Number, NONE, BOOL
		JsonArray* arr;
		JsonObj* obj;
	};
} JsonVal;