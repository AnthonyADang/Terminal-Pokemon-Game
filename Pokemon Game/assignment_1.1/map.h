#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define False 0
#define True 1

#define max_X 80
#define max_Y 21

#define PATH '#'
#define GRASS ','
#define ROCK '%'
#define EXIT 'e'
#define TREE '"'
#define CLEARING ' '

typedef enum __attribute__((__packed__)) terrain_type
{
    ter_debug,
    ter_boulder,
    ter_tree,
    ter_grass,
    ter_clearing,
    ter_path,
    ter_mart,
    ter_center,
} terrain_type_t;

typedef struct exit
{
    uint8_t x;
    uint8_t y;
} exit_t;

typedef struct map
{
    char map[max_Y][max_X];
} map_t;

void assign_border(map_t *map);