#include "object.h"

#include "display.h"



const char object_symbols[] = {
	')',    /* LART */
	'['     /* CLOTHING */
}

const struct object_type larts[] = {
	{ OBJECT_CLASS_LART, "clue-by-four", COL_BROWN, 100 },
	{ OBJECT_CLASS_LART, "chainsaw", COL_GREY, 200 },
	{ OBJECT_CLASS_LART, "bytesaber", COL_GREY, 20 }
}
