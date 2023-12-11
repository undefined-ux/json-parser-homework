//
// Created by undefined on 2023/12/10.
//
#pragma once
#include <stdio.h>

FILE* convertUtf8ToGbk(FILE* input);
void convertGbkToUtf8(FILE* input);
int isUtf8(FILE* file);