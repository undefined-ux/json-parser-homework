---
title: 总览
sidebar: 'auto'
---

::: tip
解析后返回值为[JsonVal](/core/types/#JsonVal)
:::

### 引入
```c
#include "Json.h" // 整体引入
// .....
```

### 使用
```c
#include <stdio.h>

#include "Json.h"
int main() {
    // 设置输入输出流
    setInputStream(stdin);
    setOutputStream(stdout);
    //解析Json
    struct JsonVal* json = parseValue();
    printfJsonVal(json); // 以树状缩进形式输出
    return 0;
}
```

:::warning
由于懒

所以存在部分内存泄漏问题
:::