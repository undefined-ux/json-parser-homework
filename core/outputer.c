#include "outputer.h"
int max(int a, int b) { return a > b ? a : b; }
void indent(int hierarchy) {
	for (int i = 0; i < max(hierarchy, 0); i++) printf("    "); 
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
		printfArray(val->arr, hierarchy + 1); break;
	case OBJECT:
		printfObject(val->obj, hierarchy + 1); break;
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
		printf("\"\"");
	}
	else {
		printf("\"%s\"", str->str);
	}
}

void printfObject(const struct JsonObj* obj, int hierarchy) {
	 printf("{\n");
	for (int i = 0; i < obj->size; i++) {
		indent(hierarchy + 1);
		printString(obj->key + i); printf(": ");
		printfJsonVal((obj->value + i), hierarchy);
		if (i != obj->size - 1) printf(",");
		printf("\n");
	}
	indent(hierarchy); printf("}");
}



void printfArray(const struct JsonArray* array, int hierarchy) {
	printf("[\n");
	for (int i = 0; i < array->length; i++) {
		indent(hierarchy + 1);
		printfJsonVal(&((array->arr)[i]), hierarchy + 1);
		if (i != array->length - 1) printf(","); printf("\n");
	}
	indent(hierarchy); printf("]");
}


void printNumber(const struct JsonString* num) {
	printf("%s", num->str);
}

void printBool(const struct JsonString* bl) {
	printf("%s", bl->str);
}

void printNONE() {
	printf("Null");
}

void printObject(const struct JsonObj* obj){
	printf("{");
	for (int i = 0; i < obj->size; i++) {
		printString(obj->key + i); printf(":");
		printJsonVal(obj->value + i);
		if (i != obj->size - 1) printf(",");
	} printf("}");
}
void printArray(const struct JsonArray* array){
	printf("[");
	for (int i = 0; i < array->length; i++) {
		printJsonVal(array->arr + i);
		if (i != array->length - 1) printf(",");
	}printf("]");
}