#include <stdlib.h>

#include "level.h"

void level_init(struct level *level, int floor)
{
	unsigned int i;

	level->floor = floor;
	level->map = generate_map();
	level->monsters = (struct monst **) calloc(5, sizeof(struct monst *));
	level->amonst = 5;
	level->nmonst = 0;

	/* Add a few test monsters */
	for(i = 0; i < 5; i++) level_addmonster(level);
}



void level_addmonster(struct level *level)
{
	struct monst **monsters;

	/* Allocate more mem if needed */
	if(level->nmonst == level->amonst) {
		monsters = (struct monst **)
			realloc(level->monsters,
				(level->amonst + 16) * sizeof(struct monst *));

		if(monsters == NULL) return;  /* or report an error, mumble */

		level->monsters = monsters;
		level->amonst += 16;
	}

	level->monsters[level->nmonst] = generate_monster(level);
	level->nmonst++;
}

