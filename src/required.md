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