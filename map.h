#ifndef MAP_H
#define MAP_H

#define MAP_X 76
#define MAP_Y 20
#define MAP_OFFSET(x, y) (x) + ((y) * MAP_X)


struct monst;


struct map_square {
	enum {
		TILE_EMPTY,
		TILE_WALL_HORIZ,
		TILE_WALL_VERT,
		TILE_DOOR_LOCKED,
		TILE_DOOR_CLOSED,
		TILE_DOOR_OPEN,
		TILE_DOOR_BORKED,
		TILE_STAIR_UP,
		TILE_STAIR_DOWN,
		TILE_UNREACHABLE
	} tile;

	struct monst *monster;
};

#define TILE_IS_OPAQUE(t) (t) == TILE_WALL_HORIZ || (t) == TILE_WALL_VERT || (t) == TILE_DOOR_LOCKED || (t) == TILE_DOOR_CLOSED

#define MAP_TILE_IS_OPAQUE(m, x, y) TILE_IS_OPAQUE(m[MAP_OFFSET(x, y)].tile)


typedef struct map_square *map;

map generate_map();
void map_plot(map, unsigned int, unsigned int);
void dump_map(map);

#endif
