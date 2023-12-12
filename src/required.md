---
title: Start up
sidebar: 'auto'
---
# 使用

## 使用[预构建版本](https://github.com/undefined-ux/json-parser-homework/release)
或者使用[CI构建版本](https://github.com/undefined-ux/json-parser-homework/actions/workflows/build-ci.yaml)
## 自行编译
### Windows & Msys2
```bash
pacman -S mingw-w64-x86_64-cmake mingw-w64-x86_64-iconv mingw-w64-x86_64-ninja --needed
mkdir build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=DEBUG .. && cmake --build .
```
### Linux (Arch)
```bash
pacman -S libiconv cmake ninja gcc --needed
mkdir build && cd build
cmake -G Ninja -DCMAKE_BUILD_TYPE=DEBUG .. && cmake --build . # Debug Version
cmake -G Ninja -DCMAKE_BUILD_TYPE=Release .. && cmake --build . # Release Version
```
:::tip
### 编译环境
```
Windows11 22h2
Msys2 GCC 12 CMake 2.27
```
---------------------

以及Github Action中 windows-latest及ubuntu-latest编译通过
:::


# 项目结构
cli交互部分位于${project_folder}/cli

解析/输出于${project_folder}/core

单元测试等位于${project_folder}/test

<del>但是测试还一点没写</del>

# 更新历史
- 2023-12-07 Bug Fix: 析构时报错   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-06 修改项目属性以更改cli应用默认生成名   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-06  添加命令行帮助信息   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-06 取消对cli项目中debug参数的修改   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-06 BUG FIX 修复资源释放导致的异常退出   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-06 BUG FIX: 修复缩进层级错误问题   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-06 完成解析部分   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 Bug Fix 修复无法输入的问题   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 Bug fix   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 完成cli应用对命令行参数解析工作   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 完成Json解析部分   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 new branch   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 添加parser头， 准备为outputer头内方法实现重定向输出流至文件功能   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 输出功能实现完成   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 完成缩进功能   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 完善各类型输出，暂未实现缩进功能   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 为JsonArray实现构造及析构函数   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 为JsonString的初始化方法实现malloc异常捕获,新增ToDoList.md记录未完成需求   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 JsonString新增JsonStringFromCharArraySlice方法   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 将输出功能移动至outputer头，新建Json.h批量导入   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 Bug fix: 修复cli及test项目中链接时无法找到core中导出函数的问题   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 初步实现JsonArray带格式输出功能   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 完善基础类型定义， 未定义与实现具体方法   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 修复解决方案路径问题   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 引入CuTest作为单元测试框架   Author: @[undefined](mailto:undefined_1@outlook.com)
- 2023-12-05 弃用CMake， 改用vs进行构建   Author: @[undefined](mailto:undefined_1@outlook.com)
