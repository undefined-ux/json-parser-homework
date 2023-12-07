# 总览

```
用法：json [选项]...
从输入中解析和格式化JSON数据，可选择压缩或格式化输出


长选项的强制性参数对于短选项也是强制性的。    
        -if, --input 指定输入文件（默认为标准输入）
        -of, --output 指定输出文件（默认为标准输出）
        -f, --format 使用树形缩进输出格式化的JSON
        -h, --help 显示此帮助并退出
        -c, --compress 输出压缩的JSON
```
::: tip
如果未指定输入或输出文件，则程序将默认使用标准输入或标准输出。
:::

::: warning
注意：-c / --compress 和 -f / --format 选项不能同时使用
:::

### 示例
```json
// input_f.json
{
    "ArrayKey": [
        0,
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9
    ],
    "StringKey": "Test",
    "BoolKey": True,
    "NoneKey": Null,
    "ObjectKey": {
        "key": "Test"
    }
}
// input_c.json
{"ArrayKey":[0,1,2,3,4,5,6,7,8,9],"StringKey":"Test","BoolKey":true,"NoneKey":false,"ObjectKey":{"key":"Test"}}
```
```bash
$ json -if input_c.json -of output.json -f
$ cat output.json
{
    "ArrayKey": [
        0,
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9
    ],
    "StringKey": "Test",
    "BoolKey": true,
    "NoneKey": null,
    "ObjectKey": {
        "key": "Test"
    }
}
$ json -if input_c.json -f
{
    "ArrayKey": [
        0,
        1,
        2,
        3,
        4,
        5,
        6,
        7,
        8,
        9
    ],
    "StringKey": "Test",
    "BoolKey": true,
    "NoneKey": null,
    "ObjectKey": {
        "key": "Test"
    }
}
$ json -if input_f.json -c
{"ArrayKey":[0,1,2,3,4,5,6,7,8,9],"StringKey":"Test","BoolKey":true,"NoneKey":false,"ObjectKey":{"key":"Test"}}
```
