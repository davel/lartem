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
	  Simple algorithm for now:

	  If you pass 3 constitution tests, you get an hp
	*/

	if(stats->hp < stats->hpmax) {
		if(test_stat(stats, STAT_CON, 0) &&
		   test_stat(stats, STAT_CON, 0) &&
		   test_stat(stats, STAT_CON, 0))
			stats->hp++;
	}
}

