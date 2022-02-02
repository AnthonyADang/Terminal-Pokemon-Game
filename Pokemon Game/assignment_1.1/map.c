#include "map.h"

void generate_map(map_t *m)
{
    create_border(m);
    create_terrain(m);
    create_exits(m);
    create_paths(m);
}

void print_dungeon(map_t *m)
{
    int x,y, chance;

    for(y = 0; y < MAP_Y; y++){
        for(x = 0; x < MAP_X; x++){
            switch(mapxy(x,y)) {
                case ter_debug:
                    break;
                case ter_path:
                    printf("%c", '#');
                    break;
                case ter_boulder:
                    printf("%c", '%');
                    break;
                case ter_grass:
                    printf("%c", ',');
                    break;
                case ter_clearing:
                    printf("%c", '.');
                    break;
                case ter_tree:
                    printf("%c", '"');
                    break;
                case ter_mixed:
                    chance = rand_range(0,5);
                    if(chance == 0){
                        printf("%c", '"');
                    }
                    if(chance == 1 || chance == 2 || chance == 3){
                        printf("%c", '.');
                    }
                    if(chance == 4){
                        printf("%c", '%');
                    }
                    break;
                case ter_center:
                    printf("%c", 'C');
                    break;
                case ter_mart:
                    printf("%c", 'M');
                    break;
                case ter_exit:
                    printf("%c", '#');
                    break;
                case empty:
                    printf("%c", ' ');
                    break;
            }
        }
        printf("\n");
    }
}

void create_border(map_t *m)
{
    int y,x;

    for(y = 0; y < MAP_Y; y++){
        for (x = 0; x < MAP_X; x++){
            if(y == 0 || y == MAP_Y - 1){
                mapxy(x, y) = ter_boulder;
            }
            else if(x == 0 || x == MAP_X - 1){
                mapxy(x, y)= ter_boulder;
            }
            else{
                mapxy(x, y) = empty;
            }
        }
    }
}

bool is_valid(map_t *m, int x, int y)
{
    // Check if cell is already occupied by other terrain
    if(mapxy(x, y) == empty){
        return true;
    }
    return false;
}

void generate_seeds(map_t *m) {
    int i;
    int randX;
    int randY;
    int num_grass, num_clearing, num_mixed;

    num_grass = rand() % 4 + 2;
    num_clearing = rand() % 4 + 2;
    num_mixed = rand() % 4 + 2;

    int num_terrain = m->num_terrain = num_grass + num_clearing + num_mixed;

    for(i = 0; i < num_terrain; i++){
        int randX = rand_range(1,MAP_X - 2);
        int randY = rand_range(1,MAP_Y - 2);
        if(is_valid(m,randX, randY)){
            if(i >= 0 && i < num_grass) {
                mapxy(randX,randY) = ter_grass;
            }
            if(i >=num_grass && i < num_clearing + num_grass) {
                mapxy(randX,randY) = ter_clearing;
            }
            if(i >=(num_clearing + num_grass) && i < num_terrain) {
                mapxy(randX,randY) = ter_mixed;
            }
        }
    }
}

void check_neighbor(map_t *m, int source_x, int source_y)
{
    // Possible moves for terrain growth
    int y_moves[] = {-1, 0, 1, 0};
    int x_moves[] = {0, -1, 0, 1};

    int i, x, y;
    x = source_x;
    y = source_y;

    for(i = 0; i < 4; i++){
        if(mapxy(x, y) == ter_grass){
            if(is_valid(m,x + x_moves[i],y + y_moves[i])){
                m->map[y+ y_moves[i]][x+ x_moves[i]] = ter_grass;
                check_neighbor(m,x + x_moves[i], y + y_moves[i]);
            }
        }
        if(mapxy(x, y) == ter_clearing){
            if(is_valid(m,x + x_moves[i],y + y_moves[i])) {
                m->map[y+ y_moves[i]][x+ x_moves[i]] = ter_clearing;
                check_neighbor(m, x + x_moves[i], y + y_moves[i]);
            }
        }
        if(mapxy(x, y) == ter_mixed){
            if(is_valid(m,x + x_moves[i],y + y_moves[i])) {
                m->map[y+ y_moves[i]][x+ x_moves[i]] = ter_mixed;
                check_neighbor(m, x + x_moves[i], y + y_moves[i]);
            }
        }
    }
}

void create_terrain(map_t *m)
{
    generate_seeds(m);

}

static int clear_map(map_t *m)
{
    uint8_t x, y;
    for(y = 0; y < MAP_Y; y++){
        for(x = 0; x < MAP_X; x++){
            mapxy(x,y) = empty;
            if(y == 0 || y == MAP_Y - 1 || x == 0 || x == MAP_X - 1){
                mapxy(x,y) = ter_boulder;
            }
        }
    }
    return 0;
}

void create_exits(map_t *m)
{
    int min_x = 2;
    int min_y = 2;
    int max_x = MAP_X - 5;
    int max_y = MAP_Y - 5;

    m->exits = malloc(sizeof(location_t) * 4);

    // generate random x value that is between 1-79.
    int rand_x1 = rand_range(min_x,max_x);
    int rand_x2 = rand_range(min_x,max_x);

    // generate random y value that is between 1-19.
    int rand_y1 = rand_range(min_y,max_y);
    int rand_y2 = rand_range(min_y,max_y);

    // Arrays to hold locations of 4 exits
    int exit_y[] = {0, rand_y1, (MAP_Y - 1), rand_y2};
    int exit_x[] = {rand_x1,0,rand_x2, (MAP_X - 1)};
    // Loop and mark exits
    int i;
    for(i = 0; i < 4; i++){
        mapxy(exit_x[i], exit_y[i]) = ter_path;
        m->exits[i].y = exit_y[i];
        m->exits[i].x = exit_x[i];
    }
}
void connect_paths(map_t *m, int end_x, int end_y, int start_x, int start_y)
{
    int x,y;

    if(end_y > start_y){
        for(y = end_y; y > start_y; y--){
            mapxy(start_x, y-1) = ter_path;
        }
    }
    if(end_y < start_y){
        for(y = end_y; y < start_y; y++){
            mapxy(start_x, y+1) = ter_path;
        }
    }
    if(start_x > end_x){
        for(x = start_x; x > end_x; x--){
            mapxy(x-1, start_y) = ter_path;
        }
    }
    if(start_x < end_x){
        for(x = start_x; x < end_x; x++){
            mapxy(x+1, start_y) = ter_path;
        }
    }
}

void create_paths(map_t *m)
{
    int start_x, start_y, next_x, next_y, end_x, end_y;
    // **FIX METHOD** combine paths if there is a nearby one
    // **FIX METHOD** some corners of path are not printing
    // North exit -> South exit
    start_x = m->exits[0].x;
    start_y = m->exits[0].y;;
    end_x = m->exits[2].x;
    end_y = m->exits[2].y;
    next_x = start_x;
    next_y = rand() % MAP_Y + 1;
    connect_paths(m,start_x, start_y, next_x, next_y);
    next_x = end_x;
    start_y = next_y;
    connect_paths(m,start_x, start_y, next_x, next_y);
    start_x = next_x;
    next_y = end_y;
    connect_paths(m,start_x, start_y, next_x, next_y);
    // West exit -> East exit
    start_x = m->exits[1].x;
    start_y = m->exits[1].y;
    end_x = m->exits[3].x;
    end_y = m->exits[3].y;
    next_x = rand() % (MAP_X + 1);
    next_y = start_y;
    connect_paths(m,start_x, start_y, next_x, next_y);
    start_x = next_x;
    next_y = end_y;
    connect_paths(m,start_x, start_y, next_x, next_y);
    start_y = next_y;
    next_x = end_x;
    connect_paths(m,start_x, start_y, next_x, next_y);
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    map_t m;

    clear_map(&m);
    generate_map(&m);
    print_dungeon(&m);

    return 0;
}
