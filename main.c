#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "display.h"
#include "player.h"
#include "level.h"

struct level levels[100];

int main(int argc, char *argv[])
{
	unsigned long seed;
	int fd;

	unsigned int i;


	fd = open("/dev/random", O_RDONLY);
	if (fd<1) { fprintf(stderr, "No random numbers :-(\n"); exit(1); }
	read(fd, &seed, sizeof(unsigned long));
	close(fd);
	srandom(seed);

	display_init();

	if(player_init() == -1) return 0;

	level_init(&levels[0]);
	player_set_map(levels[0].map);

	while(1) {

		main_clear();
		player_see();

		switch(display_getch()) {
		case '8':
			player_move(0, -1);
			break;
		case '9':
			player_move(1, -1);
			break;
		case '6':
			player_move(1, 0);
			break;
		case '3':
			player_move(1, 1);
			break;
		case '2':
			player_move(0, 1);
			break;
		case '1':
			player_move(-1, 1);
			break;
		case '4':
			player_move(-1, 0);
			break;
		case '7':
			player_move(-1, -1);
			break;
		}


		for(i = 0; i < levels[0].nmonst; i++)
			monster_poll(levels[0].monsters[i]);
	}

	return 0;
}
