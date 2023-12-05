#include "outputer.h"

void printJsonVal(struct JsonVal* val) {
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
		printfArray(val->arr); break;
	case OBJECT:
		printfObject(val->obj); break;
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

void printfObject(const struct JsonObj* obj) {
	printf("{");
	printfString(obj->key); printf(": ");
	printJsonVal(obj->value);
	printf("}");
}



void printfArray(const struct JsonArray* array) {
	printf("[");
	if (array->length > 3) printf("\n");
	for (int i = 0; i < array->length; i++) {
		printf("\t");
		printJsonVal(&((array->arr)[i]));
		if (i != array->length - 1) printf(", ");
		if (array->length > 3) printf("\n");
	}printf("]");
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

