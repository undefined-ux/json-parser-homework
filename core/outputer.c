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

void printfJsonVal(struct JsonVal* val, int hierarchy) {
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

void printJsonVal(struct JsonVal* val) {
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
	if (!str->length) {
		fprintf(f, "\"\"");
	}
	else {
		fprintf(f, "\"%s\"", str->str);
	}
}

void printfObject(const struct JsonObj* obj, const int hierarchy) {
	 printf("{\n");
	for (int i = 0; i < obj->size; i++) {
		indent(hierarchy + 1);
		printString(obj->key + i); fprintf(f, ": ");
		printfJsonVal((obj->value + i), hierarchy + 1);
		if (i != obj->size - 1) fprintf(f, ",");
		fprintf(f, "\n");
	}
	indent(hierarchy); fprintf(f, "}");
}



void printfArray(const struct JsonArray* array, int hierarchy) {
	fprintf(f, "[\n");
	for (int i = 0; i < array->length; i++) {
		indent(hierarchy + 1);
		printfJsonVal(&((array->arr)[i]), hierarchy + 1);
		if (i != array->length - 1) fprintf(f, ","); fprintf(f, "\n");
	}
	indent(hierarchy); fprintf(f, "]");
}


void printNumber(const struct JsonString* num) {
	fprintf(f, "%s", num->str);
}

void printBool(const struct JsonString* bl) {
	fprintf(f, "%s", bl->str);
}

void printNONE() {
	fprintf(f, "Null");
}

void printObject(const struct JsonObj* obj){
	fprintf(f, "{");
	for (int i = 0; i < obj->size; i++) {
		printString(obj->key + i); fprintf(f, ":");
		printJsonVal(obj->value + i);
		if (i != obj->size - 1) fprintf(f, ",");
	} fprintf(f, "}");
}
void printArray(const struct JsonArray* array){
	fprintf(f, "[");
	for (int i = 0; i < array->length; i++) {
		printJsonVal(array->arr + i);
		if (i != array->length - 1) fprintf(f, ",");
	}fprintf(f, "]");
}