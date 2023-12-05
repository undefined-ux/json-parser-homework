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

void printJsonVal(struct JsonVal* val, int hierarchy) {
	switch (val->type){
	case NUMBER:
		printfNumber(val->val); break;
	case STRING:
		printfString(val->val); break;
	case NONE:
		printfNONE(); break;
	case BOOL:
		printfBool(val->val); break;
	case ARRAY:
		printfArray(val->arr, hierarchy + 1); break;
	case OBJECT:
		printfObject(val->obj, hierarchy + 1); break;
	default:
		break;
	}
}


void printfString(const struct JsonString* str) {
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
		printfString(obj->key + i); printf(": ");
		printJsonVal((obj->value + i), hierarchy + 1);
		if (i != obj->size - 1) printf(",");
		printf("\n");
	}
	indent(hierarchy); printf("}");
}



void printfArray(const struct JsonArray* array, int hierarchy) {
	printf("[\n");
	for (int i = 0; i < array->length; i++) {
		indent(hierarchy);
		printJsonVal(&((array->arr)[i]), hierarchy + 1);
		if (i != array->length - 1) printf(","); printf("\n");
	}
	indent(hierarchy - 1); printf("]");
}


void printfNumber(const struct JsonString* num) {
	printf("%s", num->str);
}

void printfBool(const struct JsonString* bl) {
	printf("%s", bl->str);
}

void printfNONE() {
	printf("Null");
}

