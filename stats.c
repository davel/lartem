#include <stdlib.h>

#include "stats.h"


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

	return ((random() % 20) < val);
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
