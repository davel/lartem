#ifndef OBJECT_H
#define OBJECT_H

typedef enum {
	OBJECT_CLASS_LART,
	OBJECT_CLASS_CLOTHING
} object_class;

struct object_type {
	object_class class;
	const char *name;
	unsigned int colour;
	unsigned int weight;
}

struct object {
	const char *name;
	struct object_type *type;
}

#endif
