#include "JsonObject.h"
#include <stdlib.h>

void JsonObjInsert(
	struct JsonObj* obj,
	const struct JsonString* key,
	const struct JsonVal* value) {
	obj->size++; 
	struct JsonString* tempKey = (struct JsonString*) malloc(obj->size * sizeof(struct JsonString));
	if (tempKey == NULL) exit(1);
	for (int i = 0; i < obj->size - 1; i++) {
		tempKey[i] = *(obj->key + i);
		//destoryJsonString(obj->key + i);
	}
	struct JsonVal* tempVal = (struct JsonVal*)malloc(obj->size * sizeof(struct JsonVal));
	if (tempVal == NULL) exit(1);
	for (int i = 0; i < obj->size - 1; i++) {
		tempVal[i] = *(obj->value + i);
		//destoryJsonVal(obj->value + i);
	}
	tempVal[obj->size - 1] = *value;
	tempKey[obj->size - 1] = *key;
	obj->key = tempKey; obj->value = tempVal;
}

void destoryJsonObj(struct JsonObj* obj) {
	for (int i = 0; i < obj->size; i++) {
		destoryJsonString(obj->key + i);
		destoryJsonVal(obj->value + i);
	}
}