#include <stdlib.h>

#include "stats.h"

#include "display.h"


/*
  Roll a d20 - if the result is less that their
  (modified) stat, they pass.

  This means if their (modified) stat is zero, they never pass.
  Sounds reasonable to me.
*/

int test_stat(struct stats *stats, unsigned int stat, int modifier)
{
	int val;

	val = ((unsigned int *) stats)[stat];  /* See? I told you we might. */

	val += modifier;
	if(val <= 0) return 0;
	if(val >= 20) return 1;

	return ((random() % 20) < val);
}



void exercise_stat(struct stats_exe *s, unsigned int stat, int direction)
{
	((int *) s)[stat] += direction;
}


void increment_stat(struct stats *stats, unsigned int stat)
{
	char *message;

	if(((unsigned int *) stats)[stat] >= 16) return;

	((unsigned int *) stats)[stat]++;

	switch(stat) {
	case STAT_STR:
		message = "stronger";
		break;
	case STAT_DEX:
		message = "more dextrous";
		break;
	case STAT_CON:
		message = "tougher";
		break;
	case STAT_INT:
		message = "more intelligent";
		break;
	case STAT_WIS:
		message = "wiser";
		break;
	case STAT_CHA:
		message = "more charismatic";
		break;
	}

	msg_printf("You feel a little %s.", message);
}



void decrement_stat(struct stats *stats, unsigned int stat)
{
	char *message;

	if(((unsigned int *) stats)[stat] <= 1) return;

	((unsigned int *) stats)[stat]--;

	switch(stat) {
	case STAT_STR:
		message = "weaker";
		break;
	case STAT_DEX:
		message = "less dextrous";
		break;
	case STAT_CON:
		message = "less tough";
		break;
	case STAT_INT:
		message = "less intelligent";
		break;
	case STAT_WIS:
		message = "less wise";
		break;
	case STAT_CHA:
		message = "less charismatic";
		break;
	}

	msg_printf("You feel a little %s.", message);
}



void stats_heal(struct stats *stats)
{
	/*
	  Healing over time algorithm

	  We want people to heal about 1hp every 10 turns,
	  depending on their constitution

	  So, roll a d10, if you get 0 you heal
	  Otherwise, if you pass a con test you get a re-roll
	*/

	if(stats->hp < stats->hpmax) {

		if((!(random() % 10)) ||
		   (test_stat(stats, STAT_CON, 0) &&
		    (!(random() % 10))))

			stats->hp++;
	}
}



unsigned int stats_hurt(struct stats *stats, unsigned int damage)
{
	double reduction;

	/*
	  Ben's hurting people algorithm:

	  Take a base damage value.

	  Generate a random number between 0 and constitution.

	  Reduce damage by a proportion of (random number) / 20

	  Giving a max reduction of 80% (with 16 con, I think)
	*/

	reduction = ((double) (random() % stats->co)) / 20;

	damage *= (1 - reduction);

	if(stats->hp >= damage) stats->hp -= damage;
	else stats->hp = 0;

	return damage;
}



void stats_exercise(struct stats *stats, struct stats_exe *stats_e)
{
	unsigned int i, current;
	int level, threshold;

	for(i = 0; i< 6; i++) {

		/* There's only a chance that the stat will change this turn */
		if(random() % 3) continue;

		current = ((unsigned int *) stats)[i];
		level = ((int *) stats_e)[i];

		threshold = (current * current) + 8;

		if((current < 16) && (level >= threshold)) {
			increment_stat(stats, i);
			((int *) stats_e)[i] = 0;
		}

		if((current > 1) && (level <= -32)) {
			decrement_stat(stats, i);
			((int *) stats_e)[i] = 0;
		}
	}
}
