#include <stdlib.h>
#include <string.h>

#include "monst.h"


/* Standard bodys */

const struct body humanoid_body = {
	"head",
	"chest",
	"torso",
	"arm",
	"hand",
	"leg",
	"foot",
	"heart",
	"lungs",
	"stomach",
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};

const struct body server_body = {
	NULL,
	"upper casing",
	"lower casing",
	NULL,
	NULL,
	NULL,
	NULL,
	"CPU",
	"motherboard",
	"PSU",
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
};


const struct monst_type mons[] = {
	{ 'h', "User", &humanoid_body },
	{ 'h', "Manager", &humanoid_body }
};



struct monst *generate_monster(const struct monst_type *type,
			       map m)
{
	struct monst *monster =
		(struct monst *) malloc(sizeof(struct monst));

	monster->name = NULL;
	monster->type = type;

	monster->current_map = m;

	do {
		monster->x = random() % MAP_X;
		monster->y = random() % MAP_Y;

	} while ((m[MAP_OFFSET(monster->x, monster->y)].tile != TILE_EMPTY) ||
		 m[MAP_OFFSET(monster->x, monster->y)].monster);

	m[MAP_OFFSET(monster->x, monster->y)].monster = monster;

	return monster;
}



char *body_text(struct monst *monst,
		const char *str1,
		unsigned int part,
		const char *str2)
{
	static char str[32];
	const char **body;
	unsigned int len = 0;

	body = (const char **) monst->type->body;


	/* Start with an empty string */
	str[0] = 0;

	if(body[part]) {
		if(str1) len += strlen(str1);
		len += strlen(body[part]);
		if(str2) len += strlen(str2);

		if(len < 32) {
			strcpy(str, str1);
			strcat(str, body[part]);
			strcat(str, str2);
		}

		// TODO: print a debug message if string too long
	}

	return str;
}
