#include "map.h"

void assign_border(map_t *map)
{
    int y,x;

    for(y = 0; y < max_Y; y++){
        for (x = 0; x < max_X; x++){
            if(y == 0 || y == max_Y-1){
                map->map[y][x] = ROCK;
            }
            else if(x == 0 || x == max_X-1){
                map->map[y][x] = ROCK;
            }
            else{
                map->map[y][x] = CLEARING;
            }
        }
    }
}

void print_dungeon(map_t *map)
{
    int x,y;

    for(y = 0; y < max_Y; y++){
        for(x = 0; x < max_X; x++){
            printf("%c",map->map[y][x]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    map_t map;
    assign_border(&map);
    print_dungeon(&map);
}
