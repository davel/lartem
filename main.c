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
#include "ask.h"
#include "util.h"

void seed_rng();


struct level levels[100];


int main(int argc, char *argv[])
{
	int k;
	struct coord c;
	unsigned int i;

	seed_rng();

	display_init();

	if(player_init() == -1) return 0;

	level_init(&levels[0]);
	player_set_map(levels[0].map);

	while(1) {

		main_clear();
		player_see();

		k = display_getch();

		msg_clear();

		switch(k) {
		case '8':
		case '9':
		case '6':
		case '3':
		case '2':
		case '1':
		case '4':
		case '7':
			c = key_to_direction(k);
			player_move(c.x, c.y);
			break;
		case 'c':
			c = key_to_direction(ask_key("In which direction?"));
			msg_clear();
			player_close(c.x, c.y);
			break;
		case 'o':
			c = key_to_direction(ask_key("In which direction?"));
			msg_clear();
			player_open(c.x, c.y);
			break;
		case 'k':
			c = key_to_direction(ask_key("In which direction?"));
			msg_clear();
			player_kick(c.x, c.y);
			break;
		}


		for(i = 0; i < levels[0].nmonst; i++)
			monster_poll(levels[0].monsters[i]);
	}

	return 0;
}



void seed_rng()
{
	unsigned long seed;
	int fd;

	fd = open("/dev/random", O_RDONLY);

	if (fd < 1) {
		fprintf(stderr, "No random numbers :-(\n");
		exit(1);
	}

	read(fd, &seed, sizeof(unsigned long));

	close(fd);

	srandom(seed);
}
