---
title: 解析
sidebar: 'auto'
---
:::warning
输入流被默认初始化为NULL

调用前必须[重定向输入流](#设置输入流-setinputstream)
:::
# 设置输入流 `setInputStream`

| 参数          | 类型           |
| ------------- |:-------------:| 
| stream      | `FILE*` | 

返回值`void`

# 解析Json文本
:::tip 
String， Number，Bool， Null字面量值统一保存于 val->val; 

详情见[对String，Number，Bool，Null内部表示实现的一些说明](/core/types#JsonVal)
:::
```c
// val->val
struct JsonVal* parseString(); 
struct JsonVal* parseNumber();
struct JsonVal* parseBool();
struct JsonVal* parseNull(); 
// val->arr
struct JsonVal* parseArray();
// val->obj
struct JsonVal* parseObject();
struct JsonVal* parseValue();
```
