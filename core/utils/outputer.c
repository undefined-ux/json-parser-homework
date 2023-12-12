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

void printfJsonVal(const struct JsonVal* val, const int hierarchy) {
	switch (val->type){
	case NUMBER:
		printNumber(val->val); break;
	case STRING:
		printString(val->val); break;
	case NONE:
		printNONE(); break;
	case BOOL:
		printBool(val->val); break;
	case ARRAY:
		printfArray(val->arr, hierarchy); break;
	case OBJECT:
		printfObject(val->obj, hierarchy); break;
	default:
		break;
	}
}

void printJsonVal(const struct JsonVal* val) {
	switch (val->type) {
	case NUMBER:
		printNumber(val->val); break;
	case STRING:
		printString(val->val); break;
	case NONE:
		printNONE(); break;
	case BOOL:
		printBool(val->val); break;
	case ARRAY:
		printArray(val->arr); break;
	case OBJECT:
		printObject(val->obj); break;
	default:
		break;
	}
}

void printString(const struct JsonString* str) {
	fputc('"', f);
	char * reader = str->str;
	while (*reader) {
		if (*reader == '\n') fputs("\\n", f);
		else if (*reader == '\t') fputs("\\t", f);
		else if (*reader == '\r') fputs("\\r", f);
		else if (*reader == '"') fputs("\\\"", f);
		else if (*reader == '\'') fputs("\\'", f);
		else fputc(*reader, f);

		reader++;
	}

	fputc('"', f);
}

void printfObject(const struct JsonObj* obj, const int hierarchy) {
	fputs("{\n", f);
	for (int i = 0; i < obj->size; i++) {
		indent(hierarchy + 1); printString(obj->key + i);
		fputs(": ", f); printfJsonVal(obj->value + i, hierarchy + 1);
		if (i != obj->size - 1) fputs(",", f);
		fputs("\n", f);
	}
	indent(hierarchy); fputs("}", f);
}



void printfArray(const struct JsonArray* array, int hierarchy) {
	fputs("[\n", f);
	for (int i = 0; i < array->length; i++) {
		indent(hierarchy + 1); printfJsonVal(&array->arr[i], hierarchy + 1);
		if (i != array->length - 1) fputs(",", f);
		fputs("\n", f);
	}
	indent(hierarchy); fputs("]", f);
}


void printNumber(const struct JsonString* num) {
	fputs(num->str, f);
}

void printBool(const struct JsonString* bl) {
	fputs(bl->str, f);
}

void printNONE() {
	fputs("null", f);
}

void printObject(const struct JsonObj* obj){
	fputc('{', f);
	for (int i = 0; i < obj->size; i++) {
		printString(obj->key + i); putc(':', f);
		printJsonVal(obj->value + i);
		if (i != obj->size - 1) fputc(',', f);
	} fputc('}', f);
}
void printArray(const struct JsonArray* array){
	fputc('[', f);
	for (int i = 0; i < array->length; i++) {
		printJsonVal(array->arr + i);
		if (i != array->length - 1) fputc(',', f);
	}fputc(']', f);
}