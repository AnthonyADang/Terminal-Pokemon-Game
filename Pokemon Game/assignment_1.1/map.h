#ifndef map_h
#define map_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

// Max dimensions for map output
#define MAP_X 80
#define MAP_Y 21

//#define mappair(pair) (map->map[pair[dim_y]][pair[dim_x]])
#define mapxy(x,y)(m->map[y][x])
// Returns random int between min and max
#define rand_range(min,max) ((rand() % ((max + 1) - min)) + min)

typedef struct terrain
{
    uint8_t x;
    uint8_t y;
} terrain_t;

typedef struct location
{
    uint8_t x;
    uint8_t y;
} location_t;

typedef enum __attribute__ ((__packed__)) terrain_type
{
    ter_debug,
    ter_boulder,
    ter_tree,
    ter_path,
    ter_grass,
    ter_clearing,
    ter_mixed,
    ter_mart,
    ter_center,
    ter_exit,
    empty
} terrain_type_t;

typedef struct map
{
    terrain_type_t map[MAP_Y][MAP_X];
    location_t *exits;
    uint16_t num_terrain;
} map_t;

bool is_valid(map_t *m, int x, int y);
void create_border(map_t *m);
void create_exits(map_t *m);
void expand_terrain(map_t *m, int x, int y);
void create_terrain(map_t *m);

void create_paths(map_t *m);

#endif