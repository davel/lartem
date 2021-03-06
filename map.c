#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "display.h"
#include "monst.h"
#include "util.h"


#define MAX_ROOM_WIDTH 10
#define MAX_ROOM_VOLUME (MAX_ROOM_WIDTH*4)

const char tile_chars[] = {
	'.',    /* TILE_EMPTY */
	'-',    /* TILE_WALL_HORIZ */
	'|',    /* TILE_WALL_VERT */
	'+',    /* TILE_DOOR_LOCKED */
	'+',    /* TILE_DOOR_CLOSED */
	'-',    /* TILE_DOOR_OPEN */
	'.',    /* TILE_DOOR_BORKED */
	'<',    /* TILE_STAIR_UP */
	'>',	/* TILE_STAIR_DOWN */
	'*'	/* TILE_UNREACHABLE */
};

unsigned int tile_cols[] = {
	COL_GREY,   /* TILE_EMPTY */
	COL_ORANGE, /* TILE_WALL_HORIZ */
	COL_ORANGE, /* TILE_WALL_VERT */
	COL_BROWN,  /* TILE_DOOR_LOCKED */
	COL_BROWN,  /* TILE_DOOR_CLOSED */
	COL_BROWN,  /* TILE_DOOR_OPEN */
	COL_GREY,   /* TILE_DOOR_BORKED */
	COL_WHITE,  /* TILE_STAIR_UP */
	COL_WHITE,  /* TILE_STAIR_DOWN */
	COL_RED,    /* TILE_UNREACHABLE */
};



void create_room(map m, int xx, int yy, int width, int height);
void create_corridor(map m, int xcorr1, int ycorr1, int xcorr2, int ycorr2);
int evaluate_room(map m);


map generate_map()
{
	map m;
	unsigned int x, y;
	int i = 0;

	int xcorr1, xcorr2, ycorr1, ycorr2;

	m = calloc(MAP_X * MAP_Y, sizeof(struct map_square));

	for (x = 0; x<MAP_X; x++) for (y=0; y<MAP_Y; y++) {
		m[MAP_OFFSET(x, y)].tile = TILE_UNREACHABLE;
		m[MAP_OFFSET(x, y)].monster = NULL;
	}

	while (evaluate_room(m)<(MAP_X*MAP_Y/2)) {
		int x, y, w, h, h_max;

		x = ourrand(0, MAP_X-5); /* Smallest room is 4x4, not 3x3, hehe, don't make it 3x3 df, without thinking */
		y = ourrand(0, MAP_Y-5); /* heh */

		w = ourrand(4, limit(MAP_X-x-1, MAX_ROOM_WIDTH));

		h_max = limit(MAP_Y-y-1, MAX_ROOM_VOLUME/w);


		h = ourrand(4, h_max);

		create_room(m, x, y, w, h);

		xcorr2 = ourrand(x+1, x+w-3);
		ycorr2 = ourrand(y+1, y+h-3);

		if (i>0) create_corridor(m, xcorr1, ycorr1, xcorr2, ycorr2); else i=1;

		xcorr1 = xcorr2;
		ycorr1 = ycorr2;
	}

	return m;
}



void map_plot(map m, unsigned int x, unsigned int y)
{
	struct map_square *sq = m + MAP_OFFSET(x, y);

	if(sq->monster) main_plot(x, y,
				  sq->monster->type->colour,
				  sq->monster->type->symbol);
	else

	main_plot(x, y, tile_cols[sq->tile], tile_chars[sq->tile]);
}



void create_room(map m, int xx, int yy, int width, int height) {
	int x, y;

	if (xx<0 || yy<0 || width<1 || height<1) {
		fprintf(stderr, "Bad rectangle! %d %d %d %d\n", xx, yy, width, height); exit(1);
	}
	if (((xx+width) >= MAP_X) || ((yy+height) >= MAP_Y)) {
		fprintf(stderr, "Too big rectangle! %d %d %d %d\n", xx, yy, width, height); exit(1);
	}

	for (x=xx; x<=(xx+width); x++) {
		for (y=yy; y<=(yy+height); y++) {
			struct map_square s = m[MAP_OFFSET(x,y)];

			s.tile = TILE_EMPTY;
			if (x==xx || x==(xx+width))  s.tile = TILE_WALL_VERT;
			if (y==yy || y==(yy+height)) s.tile = TILE_WALL_HORIZ;

			if (m[MAP_OFFSET(x, y)].tile==TILE_UNREACHABLE) {
				m[MAP_OFFSET(x, y)] = s;
			} else {
				if (m[MAP_OFFSET(x, y)].tile!=TILE_EMPTY) m[MAP_OFFSET(x, y)]=s;
			}
		}
	}
}

void create_corridor(map m, int xcorr1, int ycorr1, int xcorr2, int ycorr2) {
	int i;
	int done_door = 0;
	/* First we go vertical */

	if (xcorr1>=MAP_X || xcorr2>=MAP_X || ycorr1>=MAP_Y || ycorr2>=MAP_Y) {
		fprintf(stderr, "Corridor out of range! %d %d %d %d\n", xcorr1, ycorr1, xcorr2, ycorr2);
		exit(1);
	}

	while (ycorr1!=ycorr2) {
		int q = 0;
		if (ycorr1>ycorr2) ycorr1--; else ycorr1++;

		if (m[MAP_OFFSET(xcorr1-1, ycorr1)].tile==TILE_UNREACHABLE)
			{ m[MAP_OFFSET(xcorr1-1, ycorr1)].tile = TILE_WALL_VERT; q++; }
		if (m[MAP_OFFSET(xcorr1+1, ycorr1)].tile==TILE_UNREACHABLE)
			{ m[MAP_OFFSET(xcorr1+1, ycorr1)].tile = TILE_WALL_VERT; q++; }

		if (m[MAP_OFFSET(xcorr1, ycorr1)].tile!=TILE_DOOR_CLOSED) {
			m[MAP_OFFSET(xcorr1, ycorr1)].tile = (q==2 && done_door==0) ? TILE_DOOR_CLOSED : TILE_EMPTY;
			if (q==2) done_door = 1;
		}

	}

	for (i=-1; i<2; i++) {
		if (m[MAP_OFFSET(xcorr1-i, ycorr1+1)].tile==TILE_UNREACHABLE)
			m[MAP_OFFSET(xcorr1-i, ycorr1+1)].tile = TILE_WALL_HORIZ;
		if (m[MAP_OFFSET(xcorr1-i, ycorr1-1)].tile==TILE_UNREACHABLE)
			m[MAP_OFFSET(xcorr1-i, ycorr1-1)].tile = TILE_WALL_HORIZ;
	}

	while (xcorr1!=xcorr2) {
		int q = 0;
		if (xcorr1>xcorr2) xcorr1--; else xcorr1++;

		if (m[MAP_OFFSET(xcorr1, ycorr1-1)].tile==TILE_UNREACHABLE)
			{ m[MAP_OFFSET(xcorr1, ycorr1-1)].tile = TILE_WALL_HORIZ; q++; }
		if (m[MAP_OFFSET(xcorr1, ycorr1+1)].tile==TILE_UNREACHABLE)
			{ m[MAP_OFFSET(xcorr1, ycorr1+1)].tile = TILE_WALL_HORIZ; q++; }


		if (m[MAP_OFFSET(xcorr1, ycorr1)].tile!=TILE_DOOR_CLOSED) {
			m[MAP_OFFSET(xcorr1, ycorr1)].tile = (q==2 && done_door==0) ? TILE_DOOR_CLOSED : TILE_EMPTY;
			if (q==2) done_door = 1;
		}
	}

}



struct coord find_free_square(map m)
{
	struct coord c;

	/* Okay, so I admit it's possible this code will never terminate. */
	do {
		c.x = random() % MAP_X;
		c.y = random() % MAP_Y;
	} while (!can_move_into_square(m, c.x, c.y));

	return c;
}



int can_move_into_square(map m, unsigned int x, unsigned int y)
{
	struct map_square *sq = m + MAP_OFFSET(x, y);

	return ((sq->tile == TILE_EMPTY ||
		 sq->tile == TILE_DOOR_OPEN || sq->tile == TILE_DOOR_BORKED ||
		 sq->tile == TILE_STAIR_UP || sq->tile == TILE_STAIR_DOWN) &&
		!sq->monster);
}



/* This is only not a macro because I have a superstitious belief that
   one day it may depend on arcane knowledge only available to map code */
int is_map_square(int x, int y)
{
	return (x >= 0 && x < MAP_X && y >= 0 && y < MAP_Y);
}



struct map_square *map_square(map m, int x, int y)
{
	if(!is_map_square(x, y)) return NULL;

	return m + MAP_OFFSET(x, y);
}



void dump_map(map m)
{
	unsigned int x, y;

	for(y = 0; y < MAP_Y; y++)
		for(x = 0; x < MAP_X; x++)
			map_plot(m, x, y);
	display_refresh();
}

int evaluate_room(map m) {
	int x, y;
	int i = 0;

	for (x=0; x<MAP_X; x++)
		for (y=0; y<MAP_Y; y++)
			if (m[MAP_OFFSET(x, y)].tile!=TILE_UNREACHABLE) i++;

	return i;
}
