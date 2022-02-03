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
// Max terrain region size
#define REGION_MAX_X 20
#define REGION_MAX_Y 10
// Min terrain region size
#define REGION_MIN_X 10
#define REGION_MIN_Y 8

//#define mappair(pair) (map->map[pair[dim_y]][pair[dim_x]])
#define mapxy(x,y)(m->map[y][x])
// Returns random int between min and max
#define rand_range(min,max) ((rand() % ((max + 1) - min)) + min)

typedef struct terrain
{
    uint8_t x;
    uint8_t y;
    uint8_t height;
    uint8_t width;
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
    terrain_t grass1;
    terrain_t grass2;
    terrain_t grass3;
    terrain_t grass4;
    terrain_t grass5;
    terrain_t clearing1;
    terrain_t clearing2;
    terrain_t clearing3;
    terrain_t clearing4;
    terrain_t clearing5;
    terrain_t mixed1;
    terrain_t mixed2;
    terrain_t mixed3;
    terrain_t mixed4;
    terrain_t mixed5;
    terrain_t mart;
    terrain_t center;
    uint16_t num_grass;
    uint16_t num_clearing;
    uint16_t num_mixed;
    uint16_t num_terrain;
} map_t;

bool is_valid(map_t *m, int x, int y);
bool terrain_valid(map_t *m, int start_x, int start_y, int width, int height);
void create_border(map_t *m);
void create_exits(map_t *m);
void generate_terrain_seeds(map_t *m);
void create_terrain(map_t *m, int start_x, int start_y, int width, int height);
void create_all_terrain(map_t *m);
void create_paths(map_t *m);
void create_mart(map_t *map);
void create_center(map_t *map);


#endif