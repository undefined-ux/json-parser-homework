#include "outputer.h"
#include <stdio.h>

static FILE *f = 0; // 初始化为空指针

void setOutputStream(FILE* stream) { f = stream; }
int max(int a, int b) { return a > b ? a : b; }

void indent(int hierarchy) {
	for (int i = 0; i < max(hierarchy, 0); i++) fprintf(f, "    "); 
	// 四空格缩进
	// Reason：
	//		暂无标准
	//		Python四空格缩进习惯了
	// XXX: 后续增加其它缩进方式
	// XXX: 实现setIndentation // XXX vs无高亮？
}

void printfJsonVal(const struct JsonVal* val, const int hierarchy, const int color) {
	switch (val->type){
	case NUMBER:
		printNumber(val->val, color); break;
	case STRING:
		printString(val->val, color); break;
	case NONE:
		printNONE(color); break;
	case BOOL:
		printBool(val->val, color); break;
	case ARRAY:
		printfArray(val->arr, hierarchy, color); break;
	case OBJECT:
		printfObject(val->obj, hierarchy, color); break;
	default:
		break;
	}
}

void printJsonVal(const struct JsonVal* val, const int color) {
	switch (val->type) {
	case NUMBER:
		printNumber(val->val, color); break;
	case STRING:
		printString(val->val, color); break;
	case NONE:
		printNONE(color); break;
	case BOOL:
		printBool(val->val, color); break;
	case ARRAY:
		printArray(val->arr, color); break;
	case OBJECT:
		printObject(val->obj, color); break;
	default:
		break;
	}
}

void printString(const struct JsonString* str, const int color) {
	if(color) fputs(ANSI_COLOR_GREEN, f);
	fputc('"', f);
	char * reader = str->str;
	while (*reader) {
		fputc(*reader, f);
		reader++;
	}
	fputc('"', f);if(color) fputs(ANSI_COLOR_RESET, f);

}

void printfObject(const struct JsonObj* obj, const int hierarchy, const int color) {
	fputs("{\n", f);
	for (int i = 0; i < obj->size; i++) {
		indent(hierarchy + 1);
		if(color) {
			fputs(ANSI_COLOR_MAGENTA, f);
			printString(obj->key + i, 0);
			fputs(ANSI_COLOR_RESET, f);
		}else printString(obj->key + i, 0);
		fputs(": ", f); printfJsonVal(obj->value + i, hierarchy + 1, color);
		if (i != obj->size - 1) fputs(",", f);
		fputs("\n", f);
	}
	indent(hierarchy); fputs("}", f);
}



void printfArray(const struct JsonArray* array, int hierarchy, const int color) {
	fputs("[\n", f);
	for (int i = 0; i < array->length; i++) {
		indent(hierarchy + 1); printfJsonVal(&array->arr[i], hierarchy + 1, color);
		if (i != array->length - 1) fputs(",", f);
		fputs("\n", f);
	}
	indent(hierarchy); fputs("]", f);
}


void printNumber(const struct JsonString* num, const int color) {
	if(color) fputs(ANSI_COLOR_CYAN, f);
	fputs(num->str, f);
	if(color) fputs(ANSI_COLOR_RESET, f);
}

void printBool(const struct JsonString* bl, const int color) {
	if(color) fputs(ANSI_COLOR_YELLOW, f);
	fputs(bl->str, f);
	if(color) fputs(ANSI_COLOR_RESET, f);

}

void printNONE(const int color) {
	if(color) fputs(ANSI_COLOR_YELLOW, f);
	fputs("null", f);
	if(color) fputs(ANSI_COLOR_RESET, f);
}

void printObject(const struct JsonObj* obj, const int color){
	fputs("{", f);
	for (int i = 0; i < obj->size; i++) {
		if(color) {
			fputs(ANSI_COLOR_MAGENTA, f);
			printString(obj->key + i, 0);
			fputs(ANSI_COLOR_RESET, f);
		}else printString(obj->key + i, 0);
		fputs(": ", f); printJsonVal(obj->value + i, color);
		if (i != obj->size - 1) fputs(",", f);
	}fputs("}", f);
}
void printArray(const struct JsonArray* array, const int color){
	fputc('[', f);
	for (int i = 0; i < array->length; i++) {
		printJsonVal(array->arr + i, color);
		if (i != array->length - 1) fputc(',', f);
	}fputc(']', f);
}