#include <stdlib.h>

#include "attack.h"

#include "display.h"
#include "player.h"
#include "monst.h"
#include "stats.h"
#include "util.h"



const char *user_attack_text[] = {
	"asks you to fix its computer",
	"asks you to fix its cupholder",
	"asks you to fix its email",
	"complains that the Internet is broken",
	NULL
};

const char *manager_attack_text[] = {
	"tells you to have that report done by Thursday",
	"tells you to attend a meeting on productivity",
	"tells you to attend a meeting on synergy",
	NULL
};

void attack_player(struct monst *monster, struct player *player)
{
	unsigned int attack_type;

	/* This does not support monsters who don't attack */

	do {
		attack_type = monster->type->attacks[random() % 8];
	} while(attack_type == ATTACK_NONE);

	switch(attack_type) {
	case ATTACK_USER:
		msg_printf("The %s %s.",
			   monster->type->name,
			   random_string(user_attack_text));

		player_hurt(5);
		break;
	case ATTACK_MANAGER:
		msg_printf("The %s %s.",
			   monster->type->name,
			   random_string(manager_attack_text));
		player_hurt(10);
		break;
	}
}



void attack_monster(struct player *player, struct monst *monster)
{
	/* To hit roll */

	if(test_stat(&player->stats, STAT_DEX, 0)) {

		msg_printf("You hit the %s.", monster->type->name);

	} else msg_printf("You miss the %s.", monster->type->name);
}
