#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "player.h"

#include "ask.h"
#include "role.h"
#include "display.h"
#include "map.h"


void shadow_scan(unsigned int, int, double, double);


struct player player;


int player_init()
{
	int role, i;
	struct passwd *pw; 
	pw = getpwuid(getuid());

	player.name = ask_str("What is your name?", pw->pw_name);

	role = ask_role();
	if(role == -1) return -1;
	else player.role = (unsigned int) role;

	player.floor = 8;

	/* The player is placed into a sensible position in player_set_map() */
	player.x = 0;
	player.y = 0; 

	player.xp = 0;

	for(i = 0; i < 6; i++)
		((unsigned int *) &player.stats)[i] = 4 + (random() % 12);

	player.stats.hpmax = 8 + (random() % 8);
	player.stats.hp = player.stats.hpmax;

	player.turn = 0;

	player_status();

	return 0;
}



void player_status()
{
	unsigned int level, r;
	const char *rank;

	level = player.xp >> 4;
	r = level >> 2;
	if(r > 7) r = 7;

	rank = get_rank(player.role, r);

	stat_printf("%s the %s\nFloor:%u  HP:%u(%u)  Lvl:%u  St:%u Dx:%u Co:%u In:%u Wi:%u Ch:%u  T:%u",
		    player.name, rank,
		    player.floor,
		    player.stats.hp, player.stats.hpmax,
		    level,
		    player.stats.st, player.stats.dx, player.stats.co,
		    player.stats.in, player.stats.wi, player.stats.ch,
		    player.turn);
}


void player_set_map(map m)
{
	player.current_map = m;

	/* Okay, so I admit it's possible this code will never terminate. */
	while (!can_move_into_square(m, player.x, player.y)) {
		player.x = random() % MAP_X;
		player.y = random() % MAP_Y;
	}
}


void player_see()
{
	shadow_scan(0, 1, 1, 0);
	shadow_scan(1, 1, 1, 0);
	shadow_scan(2, 1, 1, 0);
	shadow_scan(3, 1, 1, 0);
	shadow_scan(4, 1, 1, 0);
	shadow_scan(5, 1, 1, 0);
	shadow_scan(6, 1, 1, 0);
	shadow_scan(7, 1, 1, 0);

	/* Finally, draw the player */
	main_plot(player.x, player.y, COL_WHITE, '@');

	display_refresh();
}



void shadow_scan(unsigned int octant,
		 int row,
		 double start_slope,
		 double end_slope)
{
	int col, start_col, end_col;
	unsigned int blocking = 1, opaque;
	int x, y;

	double new_start_slope = start_slope;
	double new_end_slope = end_slope;

/* For watching the algorithm in action

	display_refresh();
	usleep(100000);
*/

	start_col = (int) ((start_slope * row) + 0.5);
	end_col = (int) ((end_slope * row) - 0.5);

	if(end_col > start_col) return;


	for(col = start_col;
	    col >= end_col;
	    col--) {

		x = player.x;
		y = player.y;

		switch(octant) {
		case 0:
			x += row;
			y += col;
			break;
		case 1:
			x += col;
			y += row;
			break;
		case 2:
			x -= col;
			y += row;
			break;
		case 3:
			x -= row;
			y += col;
			break;
		case 4:
			x -= row;
			y -= col;
			break;
		case 5:
			x -= col;
			y -= row;
			break;
		case 6:
			x += col;
			y -= row;
			break;
		case 7:
			x += row;
			y -= col;
			break;
		}

		if(x < 0 || x >= MAP_X || y < 0 || y >= MAP_Y)
			opaque = 1;
		else {
			map_plot(player.current_map, x, y);
			opaque = MAP_TILE_IS_OPAQUE(player.current_map,
						    x, y);
		}


		if(blocking && !opaque) {

			if(col != start_col) {
				new_start_slope =
					(((double) col) + 0.5) /
					(((double) row) + 0.5);

				if(new_start_slope < 0)
					new_start_slope = 0;
				else if(new_start_slope > 1)
					new_start_slope = 1;
			}

			blocking = 0;

		} else if(!blocking && opaque) {

			new_end_slope =
				(((double) col) + 0.5) /
				(((double) row) - 0.5);

			if(new_end_slope < 0) new_end_slope = 0;
			else if(new_end_slope > 1) new_end_slope = 1;

			shadow_scan(octant,
				    row + 1,
				    new_start_slope,
				    new_end_slope);

			blocking = 1;
		}
	}

	if(!blocking) shadow_scan(octant, row + 1,
				  new_start_slope, end_slope);
}



void player_move(int dx, int dy)
{
	int xx, yy;

	xx = player.x + dx;
	yy = player.y + dy;

	if (xx<0 || xx>=MAP_X || yy<0 || yy>=MAP_Y) return;

	// Eventually this'll probably make us attack the monster
	if(player.current_map[MAP_OFFSET(xx, yy)].monster) return;

	if(can_move_into_square(player.current_map, xx, yy)) {
		player.x = xx;
		player.y = yy;
	}
}
