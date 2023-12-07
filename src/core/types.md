---
title: 类型
sidebar: 'auto'
---

# JsonType
用于判定JsonVal结构体中值类型
##  定义
```c
typedef enum {
	STRING,
	NUMBER,
	BOOL,
	ARRAY,
	OBJECT,
	NONE
} JsonType;
```

# JsonObj
用于存储Object字面量,例如 `{"testKey": "testVal"}`
## 定义
```c
struct JsonObj {
	size_t size;
	struct JsonString* key;
	struct JsonVal* value;
};
```
## 方法
### 插入元素 `JsonObjInsert`
:::warning
在内存分配失败情况下将直接导致程序非零退出
:::
| 参数          | 类型           | 备注                  |
| ------------- |:-------------:| :--------------------:|
| obj      | ` struct JsonObj*` | 被插入的Object类型指针  |
| key      | `const struct JsonString*`| 插入值的键      |
| value | `const struct JsonVal*`      | 插入值          |

返回值： `void`

### 析构 `destoryJsonObj`
| 参数          | 类型           |
| ------------- |:-------------:| 
| obj      | ` struct JsonObj*` | 
返回值： `void`

# JsonVal
:::tip
### 关于String，Number，None，Bool类型实现的解释
因为仅需解析并格式化，压缩及语法检查功能， 后续无数值改动等内容，且格式化输出等需求四个类型所需方法及实现几乎完全一致，
所以直接使用String类型存储，减轻开发难度
:::
## 定义
```c
struct JsonVal {
	JsonType type;
	union {
		struct JsonString* val; // String, Number, NONE, BOOL
		struct JsonArray* arr;
		struct JsonObj* obj;
	};
};
```
## 方法
### 析构 `destoryJsonVal`
| 参数          | 类型           |
| ------------- |:-------------:| 
| obj      | ` struct JsonVal*` | 
返回值： `void`
# JsonString
## 定义
```c
struct JsonString {
	char* str;
	size_t length;
	size_t capacity;
};
```
## 方法
:::warning
在内存分配失败情况下将直接导致程序非零退出
:::
### 初始化
#### 由空值初始化    `JsonString_New`

| 参数          | 类型           |
| ------------- |:-------------:| 
|    无   | `void` | 

返回值: `struct JsonString*`
:::tip
空值初始化默认JsonString容量为10
:::

#### 由char数组初始化 `JsonStringFromCharArray`
| 参数          | 类型           |
| ------------- |:-------------:| 
|    str   | `const char*` | 
返回值: `struct JsonString*`

#### 由char数组切片初始化 `JsonStringFromCharArraySlice`
| 参数          | 类型           |备注                      |
| ------------- |:-------------:|:------------------------:|
|    start   | `const char*` |                             |
|    end   | `const char*` | 与C++STL容器相同，指向切片后一位|
返回值: `struct JsonString*`
#### 由char值初始化 `JsonStringFromChar`
| 参数          | 类型           |
| ------------- |:-------------:| 
|    c   | `const char` | 
返回值: `struct JsonString*`
:::tip
char值初始化默认JsonString容量为10
:::
### 追加字符 `JsonStringPushBackChar`
| 参数          | 类型           |
| ------------- |:-------------:| 
|    c   | `const char` | 
|    str   | `struct JsonString*` | 
返回值 `void`
### 析构 `destoryJsonString`
| 参数          | 类型           |
| ------------- |:-------------:| 
|    str   | `struct JsonString*` | 
返回值 `void`
# JsonArray
## 定义
```c
struct JsonArray {
	struct JsonVal* arr;
	size_t length;
}
```
## 方法
:::warning
在内存分配失败情况下将直接导致程序非零退出
:::
### 初始化
## 空值 `JsonArrayNew`
| 参数          | 类型           |
| ------------- |:-------------:| 
|    无   | `void` | 

返回值: `struct JsonArray*`
:::tip
空值初始化默认JsonArray容量为10
:::

## 由JsonVal数组作为初始化 `JsonArrayFromArray`
| 参数          | 类型           |
| ------------- |:-------------:| 
|    arr   | `struct JsonVal*` | 
|    length   | `size_t` | 

返回值: `struct JsonArray*`

## 追加值 `JsonArrayPushBack`
| 参数          | 类型           |
| ------------- |:-------------:| 
|    arr   | `struct JsonVal*` | 
|    val   | `struct JsonVal*` | 

返回值: `void`

## 析构 `destoryJsonArray`
| 参数          | 类型           |
| ------------- |:-------------:| 
|    arr   | `struct JsonVal*` | 
返回值: `void`