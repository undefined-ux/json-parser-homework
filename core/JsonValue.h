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
/// Json对象值
/// char* val 包含String， Number， None， Bool类型
/// 因为仅需解析并格式化，压缩及语法检查功能， 后续无数值改动等内容， 
/// 于是使用字符串表示实现Number等类型， 减少后期开发压力， 方便存储值
/// 否则Json因JavaScript自带高精，JSON对象不限制Number大小及精度。导致JSON中Number需自行实现高精
/// Type定义见JsonType， 用于判定格式并使用对应方法输出
/// </summary>
typedef struct JsonVal {
	JsonType type;
	union {
		char* val; // String, Number, NONE, BOOL
		JsonArray* arr;
		JsonObj* obj;
	};
} JsonVal;