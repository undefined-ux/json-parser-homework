---
title: 输出格式化选项
sidebar: 'auto'
---
::: warning
注意：-c / --compress 和 -f / --format 选项不能同时使用
:::

::: tip
未指定参数的情况下， 默认将以树状缩进的形式进行输出
:::



## 以树状缩进形式输出 -f, --format

```bash
# 从stdin读入并输出至stdout, 显式指定树状缩进输出
$ json -f 
$ json --format
$ json # 从stdin读入并输出至stdout, 默认指定树状缩进输出
```

## 以压缩形式输出 -c, --compress

```bash
# 从stdin读入并输出至stdout, 以压缩后形式输出
$ json -c 
$ json --compress
```

## 支持UTF-8编码输出
:::tip
仅当你需要输出至控制台并读入了utf-8编码的文件时使用
:::
```bash
# 从stdin读入并输出至stdout, 以压缩后形式输出
$ json -u
$ json --utf
```