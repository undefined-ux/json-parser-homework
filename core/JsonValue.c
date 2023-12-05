#include "JsonValue.h"
#include "JsonString.h"
#include "JsonArray.h"
#include "JsonObject.h"
#include "outputer.h"

void printJsonVal(struct JsonVal* val) {
	switch (val->type)
	{
	    case NUMBER:
		case STRING:
		case NONE:
		case BOOL:
			printfString(val->val); break;
		case ARRAY:
			printfArray(val->arr); break;
		case OBJECT:
			printfObject(val->obj); break;
		default:
			break;
	}
}
