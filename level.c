#include <stdlib.h>

#include "level.h"

void level_init(struct level *level)
{
	level->map = generate_map();
	level->monsters = NULL;
	level->nmonst = 0;
}
