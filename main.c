#include <stdlib.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "display.h"
#include "player.h"
#include "map.h"

int main(int argc, char *argv[])
{
	map m;
	unsigned long seed;
	int fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd<1) { fprintf(stderr, "No random numbers :-(\n"); exit(1); }
	read(fd, &seed, sizeof(unsigned long));
	close(fd);
	srandom(seed);
	display_init();
	if(player_init() == -1) return 0;

	m = generate_map();
	// dump_map(m);
	// return 0;
	
	player_set_map(m);

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
	}

	return 0;
}
