#ifndef PLAYER_H
#define PLAYER_H

#include "monst.h"
#include "level.h"
#include "stats.h"

/* This struct begins exactly the same as struct monst,
   so that we can cast it */

struct player {
	const char *name;
	const struct monst_type *type;

	struct level *level;
	unsigned int x, y;

	struct stats stats;

	/* Stuff from here on is player-only */

	unsigned int role;

	unsigned int xp;
	unsigned int turn;
};

int player_init();
void player_status();
void player_set_level(struct level *);
void player_see();
void player_poll();

void player_move(int, int);
void player_open(int, int);
void player_close(int, int);
void player_kick(int, int);
void player_look();

void player_hurt(unsigned int);

#endif
