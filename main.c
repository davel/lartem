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
struct coord select_square(map, unsigned int, unsigned int);


struct level levels[100];


int main(int argc, char *argv[])
{
	int k;
	struct coord c;
	unsigned int i;
	unsigned char turn_taken = 1, running = 0;

	seed_rng();

	display_init();

	if(player_init() == -1) return 0;

	level_init(&levels[0], 8);
	player_set_level(&levels[0]);

	while(1) {
		main_clear();
		player_see();
		player_status();

		turn_taken = 0;

		if(!running) {
			do {
				k = display_getch();
			} while(k == ' ');
		}

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
			if(!player_move(c.x, c.y)) running = 0;
			turn_taken = 1;
			break;
		case 'c':
			c = key_to_direction(ask_key("In which direction?"));
			msg_clear();
			player_close(c.x, c.y);
			turn_taken = 1;
			break;
		case 'o':
			c = key_to_direction(ask_key("In which direction?"));
			msg_clear();
			player_open(c.x, c.y);
			turn_taken = 1;
			break;
		case 'k':
			c = key_to_direction(ask_key("In which direction?"));
			msg_clear();
			player_kick(c.x, c.y);
			turn_taken = 1;
			break;
		case 'g':
		case 'G':
			k = ask_key("In which direction?");
			c = key_to_direction(k);
			if((c.x || c.y) && player_move(c.x, c.y)) running = 1;
			turn_taken = 1;
			break;
		case ':':
			player_look();
			break;
		case ';':
			msg_printf("Pick an object...");
			c = player_select_square();
			msg_clear();
			player_remote_look(c.x, c.y);
			break;
		}


		if(turn_taken) {
			if(player_poll()) running = 0;

			for(i = 0; i < levels[0].nmonst; i++)
				if(monster_poll(levels[0].monsters[i]))
					running = 0;
		}
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
