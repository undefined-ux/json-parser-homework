#include "JsonValue.h"
#include "JsonString.h"
#include "JsonArray.h"
#include "JsonObject.h"
#include "../utils/outputer.h"

#include <stdlib.h>

void destoryJsonVal(struct JsonVal* val) {
	switch (val->type)
	{
	case NUMBER:
	case STRING:
	case NONE:
	case BOOL:
		destoryJsonString(val->val); break;
	case OBJECT:
		destoryJsonObj(val->obj); break;
	case ARRAY:
		destoryJsonArray(val->arr); break;
	default:
		break;
	}
	free(val);
}