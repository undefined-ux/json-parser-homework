---
title: 输出
sidebar: 'auto'
---
:::warning
输出流被默认初始化为NULL

调用前必须[重定向输出流](#设置输入流-setinputstream)
:::
# 设置输出流 `setOutputStream`
| 参数          | 类型           |
| ------------- |:-------------:| 
| stream      | `FILE*` | 

返回值`void`

# 输出
## 树状缩进格式输出
:::tip
以四空格为一层缩进
:::

```c
// hierarchy 为缩进层级， 0不缩进
void printfJsonVal(struct JsonVal* val, int hierarchy);
void printfArray(const struct JsonArray* array, int hierarchy); 
```
## 压缩形式输出
```c
void printString(const struct JsonString* str);
void printNONE();
void printBool(const struct JsonString* bl);
void printNumber(const struct JsonString* num);
void printObject(const struct JsonObj* obj);
void printArray(const struct JsonArray* array);
void printJsonVal(struct JsonVal* val);
```
