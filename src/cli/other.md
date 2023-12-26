---
title: 其它
sidebar: 'auto'
---

::: tip
部分功能待实现（画饼）
:::

## 输出帮助 -h， --help

```bash
$ json -h
用法：json [选项]...
从输入中解析和格式化JSON数据，可选择压缩或格式化输出。

长选项的强制性参数对于短选项也是强制性的。
    -if, --input 指定输入文件（默认为标准输入）
    -of, --output 指定输出文件（默认为标准输出）
    -f, --format 使用树形缩进输出格式化的JSON
    -c, --compress 输出压缩的JSON
    -h, --help 显示此帮助并退出

示例：
    json -if input.json -of output.json -f
    json --input=input.json --output=output.json --compress

如果未指定输入或输出文件，则程序将默认使用标准输入或标准输出。

注意：--compress 和 --format 选项不能同时使用。
```
