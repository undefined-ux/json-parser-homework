#include "JsonObject.h"
#include <stdlib.h>

void JsonObjInsert(
	struct JsonObj* obj,
	const struct JsonString* key,
	const struct JsonVal* value) {
	obj->size++; 
	obj->value = (struct JsonVal*)realloc(obj->value, obj->size * sizeof(struct JsonVal));
	if (obj->value == NULL) exit(1);
	obj->value[obj->size - 1] = *value;
	obj->key = (struct JsonString*)realloc(obj->key, obj->size * sizeof(struct JsonString));
	if (obj->key == NULL) exit(1);
	obj->key[obj->size - 1] = *key;
}
