#ifndef PLAYER_H
#define PLAYER_H

#include "stats.h"
#include "map.h"

struct player {
	const char *name;
	unsigned int role;

	map current_map;
	int floor;
	unsigned int x, y;

	struct stats stats;

	unsigned int xp;

	unsigned int turn;
};

int player_init();
void player_status();
void player_set_map(map);
void player_see();
void player_move(int, int);
void player_open(int, int);
void player_close(int, int);

#endif
