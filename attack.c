#include <stdlib.h>

#include "attack.h"

#include "display.h"
#include "player.h"
#include "monst.h"
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
	/* TODO: different monsters should have a different range of
	         attack types */

	msg_printf("The %s %s.",
		   monster->type->name,
		   random_string(user_attack_text));

		player_hurt(5);
}

