---
title: 指定输入/输出流
sidebar: 'auto'
---

::: tip
如果未指定输入或输出文件，则程序将默认使用标准输入或标准输出流。
:::
## 输入 -if, --input
```
-if, --input 指定输入文件（默认为标准输入）
```
### Demo
```bash
$ json -if input.json -f
$ json --input input.json -f # 两者完全等效
$ json # 默认使用stdin/stdout
```

## 输出 -of, --output
```
-of, --output 指定输出文件（默认为标准输出）
```

### Demo
```bash
$ json -of input.json -f
$ json --output input.json -f # 两者完全等效
$ json # 默认使用stdin/stdout
```