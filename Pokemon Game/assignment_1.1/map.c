#include "map.h"

void generate_map(map_t *m)
{
    create_border(m);
    generate_terrain_seeds(m);
    create_all_terrain(m);
    create_exits(m);
    create_paths(m);
    create_mart(m);
    create_center(m);
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

void generate_terrain_seeds(map_t *m) {
    int i;
    int randX, randY;
    int randWidth, randHeight;
    int num_grass, num_clearing, num_mixed;

    num_grass = m->num_grass = rand() % 4 + 2;
    num_clearing = m->num_clearing = rand() % 4 + 2;
    num_mixed = m->num_mixed= rand() % 4 + 2;

    int num_terrain = m->num_terrain = num_grass + num_clearing + num_mixed;

    for (i = 0; i < num_grass; i++) {
        randX = rand_range(1, MAP_X - 2);
        randY = rand_range(1, MAP_Y - 2);
        randWidth = rand_range(REGION_MIN_X, REGION_MAX_X);;
        randHeight = rand_range(REGION_MIN_Y, REGION_MAX_Y);;
        switch (i) {
            case 0:
                mapxy(randX, randY) = ter_grass;
                m->grass1.x = randX;
                m->grass1.y = randY;
                m->grass1.width = randWidth;
                m->grass1.height = randHeight;
                break;
            case 1:
                mapxy(randX, randY) = ter_grass;
                m->grass2.x = randX;
                m->grass2.y = randY;
                m->grass2.width = randWidth;
                m->grass2.height = randHeight;
                break;
            case 2:
                mapxy(randX, randY) = ter_grass;
                m->grass3.x = randX;
                m->grass3.y = randY;
                m->grass3.width = randWidth;
                m->grass3.height = randHeight;
                break;
            case 3:
                mapxy(randX, randY) = ter_grass;
                m->grass4.x = randX;
                m->grass4.y = randY;
                m->grass4.width = randWidth;
                m->grass4.height = randHeight;
                break;
            case 4:
                mapxy(randX, randY) = ter_grass;
                m->grass5.x = randX;
                m->grass5.y = randY;
                m->grass5.width = randWidth;
                m->grass5.height = randHeight;
                break;
        }
    }
    for (i = 0; i < num_clearing; i++) {
        randX = rand_range(1, MAP_X - 2);
        randY = rand_range(1, MAP_Y - 2);
        randWidth = rand_range(REGION_MIN_X, REGION_MAX_X);;
        randHeight = rand_range(REGION_MIN_Y, REGION_MAX_Y);;
        switch (i) {
            case 0:
                mapxy(randX, randY) = ter_clearing;
                m->clearing1.x = randX;
                m->clearing1.y = randY;
                m->clearing1.width = randWidth;
                m->clearing1.height = randHeight;
                break;
            case 1:
                mapxy(randX, randY) = ter_clearing;
                m->clearing2.x = randX;
                m->clearing2.y = randY;
                m->clearing2.width = randWidth;
                m->clearing2.height = randHeight;
                break;
            case 2:
                mapxy(randX, randY) = ter_clearing;
                m->clearing3.x = randX;
                m->clearing3.y = randY;
                m->clearing3.width = randWidth;
                m->clearing3.height = randHeight;
                break;
            case 3:
                mapxy(randX, randY) = ter_clearing;
                m->clearing4.x = randX;
                m->clearing4.y = randY;
                m->clearing4.width = randWidth;
                m->clearing4.height = randHeight;
                break;
            case 4:
                mapxy(randX, randY) = ter_clearing;
                m->clearing5.x = randX;
                m->clearing5.y = randY;
                m->clearing5.width = randWidth;
                m->clearing5.height = randHeight;
                break;
        }
    }
    for (i = 0; i < num_clearing; i++) {
        randX = rand_range(1, MAP_X - 2);
        randY = rand_range(1, MAP_Y - 2);
        randWidth = rand_range(REGION_MIN_X, REGION_MAX_X);;
        randHeight = rand_range(REGION_MIN_Y, REGION_MAX_Y);;
        switch (i) {
            case 0:
                mapxy(randX, randY) = ter_mixed;
                m->mixed1.x = randX;
                m->mixed1.y = randY;
                m->mixed1.width = randWidth;
                m->mixed1.height = randHeight;
                break;
            case 1:
                mapxy(randX, randY) = ter_mixed;
                m->mixed2.x = randX;
                m->mixed2.y = randY;
                m->mixed2.width = randWidth;
                m->mixed2.height = randHeight;
                break;
            case 2:
                mapxy(randX, randY) = ter_mixed;
                m->mixed3.x = randX;
                m->mixed3.y = randY;
                m->mixed3.width = randWidth;
                m->mixed3.height = randHeight;
                break;
            case 3:
                mapxy(randX, randY) = ter_mixed;
                m->mixed4.x = randX;
                m->mixed4.y = randY;
                m->mixed4.width = randWidth;
                m->mixed4.height = randHeight;
                break;
            case 4:
                mapxy(randX, randY) = ter_mixed;
                m->mixed5.x = randX;
                m->mixed5.y = randY;
                m->mixed5.width = randWidth;
                m->mixed5.height = randHeight;
                break;
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
//                check_neighbor(m,x + x_moves[i], y + y_moves[i]);
            }
        }
        if(mapxy(x, y) == ter_clearing){
            if(is_valid(m,x + x_moves[i],y + y_moves[i])) {
                m->map[y+ y_moves[i]][x+ x_moves[i]] = ter_clearing;
//                check_neighbor(m, x + x_moves[i], y + y_moves[i]);
            }
        }
        if(mapxy(x, y) == ter_mixed){
            if(is_valid(m,x + x_moves[i],y + y_moves[i])) {
                m->map[y+ y_moves[i]][x+ x_moves[i]] = ter_mixed;
//                check_neighbor(m, x + x_moves[i], y + y_moves[i]);
            }
        }
    }
}
bool terrain_valid(map_t *m, int start_x, int start_y, int width, int height)
{
    if((start_x + width) >= MAP_X || (start_y + height) >= MAP_Y){return false;}

    int x, y;
    for(y = start_y; y < (start_y + height); y++){
        for(x = start_x; x < (start_x + width); x++){
            if(m->map[y][x] == empty || m->map[y + 1][x] == empty || m->map[y][x + 1] == empty
            || m->map[y - 1][x] == empty || m->map[y][x - 1] == empty){return false;}
        }
    }
    return true;
}

void create_mart(map_t *m) {
    int i, height, width, tries = 0;
    int randX, randY;
    height = 2;
    width = 2;

    for (i = 1; i < 2; i++) {
        tries++;
        randX = rand_range(1, MAP_X);
        randY = rand_range(1, MAP_Y);
        if (!is_valid(m, randX, randY)) {
            i -= 1;
            continue;
        } else {
            // current cell is not a path
            if (mapxy(randX, randY) != ter_path) {
                if (mapxy(randX, randY + 1) == ter_path) {
                    if (mapxy(randX, randY - 1) != ter_path
                        && mapxy(randX - 1, randY - 1) != ter_path
                        && mapxy(randX - 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_mart;
                        mapxy(randX, randY - 1) = ter_mart;
                        mapxy(randX + 1, randY - 1) = ter_mart;
                        mapxy(randX + 1, randY) = ter_mart;
                        break;
                    } else if (mapxy(randX, randY - 1) != ter_path
                               && mapxy(randX - 1, randY - 1) != ter_path
                               && mapxy(randX - 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_mart;
                        mapxy(randX, randY - 1) = ter_mart;
                        mapxy(randX - 1, randY - 1) = ter_mart;
                        mapxy(randX - 1, randY) = ter_mart;
                        break;
                    }
                } else if (mapxy(randX, randY - 1) == ter_path) {
                    if (mapxy(randX, randY + 1) != ter_path
                        && mapxy(randX + 1, randY + 1) != ter_path
                        && mapxy(randX + 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_mart;
                        mapxy(randX, randY + 1) = ter_mart;
                        mapxy(randX + 1, randY + 1) = ter_mart;
                        mapxy(randX + 1, randY) = ter_mart;
                        break;
                    } else if (mapxy(randX, randY + 1) != ter_path
                        && mapxy(randX - 1, randY - 1) != ter_path
                        && mapxy(randX - 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_mart;
                        mapxy(randX, randY + 1) = ter_mart;
                        mapxy(randX - 1, randY - 1) = ter_mart;
                        mapxy(randX - 1, randY) = ter_mart;
                        break;
                    }
                } else if (mapxy(randX + 1, randY) == ter_path) {
                    if (mapxy(randX, randY - 1) != ter_path
                        && mapxy(randX - 1, randY - 1) != ter_path
                        && mapxy(randX - 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_mart;
                        mapxy(randX, randY - 1) = ter_mart;
                        mapxy(randX - 1, randY - 1) = ter_mart;
                        mapxy(randX - 1, randY) = ter_mart;
                        break;
                    } else if (mapxy(randX, randY + 1) != ter_path
                               && mapxy(randX - 1, randY + 1) != ter_path
                               && mapxy(randX - 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_mart;
                        mapxy(randX, randY + 1) = ter_mart;
                        mapxy(randX - 1, randY + 1) = ter_mart;
                        mapxy(randX - 1, randY) = ter_mart;
                        break;
                    }
                } else if (mapxy(randX - 1, randY) == ter_path) {
                    if (mapxy(randX, randY - 1) != ter_path
                        && mapxy(randX + 1, randY - 1) != ter_path
                        && mapxy(randX + 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_mart;
                        mapxy(randX, randY - 1) = ter_mart;
                        mapxy(randX + 1, randY - 1) = ter_mart;
                        mapxy(randX + 1, randY) = ter_mart;
                        break;
                    } else if (mapxy(randX, randY + 1) != ter_path
                               && mapxy(randX + 1, randY) != ter_path
                               && mapxy(randX + 1, randY + 1) != ter_path) {
                        mapxy(randX, randY) = ter_mart;
                        mapxy(randX, randY + 1) = ter_mart;
                        mapxy(randX + 1, randY + 1) = ter_mart;
                        mapxy(randX + 1, randY) = ter_mart;
                        break;
                    }
                } else {
                    i -= 1;
                    continue;
                }
            }
        }
    }
}

void create_center(map_t *m) {
    int i, height, width, tries = 0;
    int randX, randY;
    height = 2;
    width = 2;

    for (i = 1; i < 2; i++) {
        tries++;
        randX = rand_range(1, MAP_X);
        randY = rand_range(1, MAP_Y);
        if (!is_valid(m, randX, randY)) {
            i -= 1;
            continue;
        } else {
            // current cell is not a path
            if (mapxy(randX, randY) != ter_path) {
                if (mapxy(randX, randY + 1) == ter_path) {
                    if (mapxy(randX, randY - 1) != ter_path
                        && mapxy(randX - 1, randY - 1) != ter_path
                        && mapxy(randX - 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_center;
                        mapxy(randX, randY - 1) = ter_center;
                        mapxy(randX + 1, randY - 1) = ter_center;
                        mapxy(randX + 1, randY) = ter_center;
                        break;
                    } else if (mapxy(randX, randY - 1) != ter_path
                               && mapxy(randX - 1, randY - 1) != ter_path
                               && mapxy(randX - 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_center;
                        mapxy(randX, randY - 1) = ter_center;
                        mapxy(randX - 1, randY - 1) = ter_center;
                        mapxy(randX - 1, randY) = ter_center;
                        break;
                    }
                } else if (mapxy(randX, randY - 1) == ter_path) {
                    if (mapxy(randX, randY + 1) != ter_path
                        && mapxy(randX + 1, randY + 1) != ter_path
                        && mapxy(randX + 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_center;
                        mapxy(randX, randY + 1) = ter_center;
                        mapxy(randX + 1, randY + 1) = ter_center;
                        mapxy(randX + 1, randY) = ter_center;
                        break;
                    } else if (mapxy(randX, randY + 1) != ter_path
                               && mapxy(randX - 1, randY - 1) != ter_path
                               && mapxy(randX - 1, randY) != ter_path) {
                        mapxy(randX, randY) = ter_center;
                        mapxy(randX, randY + 1) = ter_center;
                        mapxy(randX - 1, randY - 1) = ter_center;
                        mapxy(randX - 1, randY) = ter_center;
                        break;
                    }
                } else if (mapxy(randX + 1, randY) == ter_path) {

                } else if (mapxy(randX - 1, randY) == ter_path) {

                } else {
                    i -= 1;
                    continue;
                }
            }
        }
    }
}


void create_terrain(map_t *m, int start_x, int start_y, int width, int height)
{
    int y,x, chance;
    for(y = start_y; y < start_y + height; y++){
        for(x = start_x; x < start_x + width; x++){
//            if(terrain_valid(m, start_x, start_y, width, height)){
                if((start_x + width) >= MAP_X || (start_y + height) >= MAP_Y){continue;}
                if(mapxy(x, y) != empty){
                    continue;
                }
                else{
                    switch (mapxy(start_x, start_y)){
                        case ter_grass:
                            mapxy(x, y) = ter_grass;
                            break;
                        case ter_clearing:
                            mapxy(x, y) = ter_clearing;
                            break;
                        case ter_mixed:
                            chance = rand_range(0,5);
                            if(chance == 0){
                                mapxy(x, y) = ter_tree;
                            }
                            if(chance == 1 || chance == 2 || chance == 3){
                                mapxy(x, y) = ter_clearing;
                            }
                            if(chance == 4){
                                mapxy(x, y) = ter_boulder;
                            }
                            break;
                    }
                }
//            }
        }
    }
}
void create_all_terrain(map_t *m)
{
    create_terrain(m,m->grass1.x, m->grass1.y, m->grass1.width,m->grass1.height);
    create_terrain(m,m->grass2.x, m->grass2.y, m->grass2.width,m->grass2.height);
    create_terrain(m,m->clearing1.x, m->clearing1.y, m->clearing1.width,m->clearing1.height);
    create_terrain(m,m->clearing2.x, m->clearing2.y, m->clearing2.width,m->clearing2.height);
    create_terrain(m,m->mixed1.x, m->mixed1.y, m->mixed1.width,m->mixed1.height);
    create_terrain(m,m->mixed2.x, m->mixed2.y, m->mixed2.width,m->mixed2.height);
switch (m->num_grass){
    case 3:
        create_terrain(m,m->grass3.x, m->grass3.y, m->grass3.width,m->grass3.height);
        break;
    case 4:
        create_terrain(m,m->grass3.x, m->grass3.y, m->grass3.width,m->grass3.height);
        create_terrain(m,m->grass4.x, m->grass4.y, m->grass4.width,m->grass4.height);
        break;
    case 5:
        create_terrain(m,m->grass3.x, m->grass3.y, m->grass3.width,m->grass3.height);
        create_terrain(m,m->grass4.x, m->grass4.y, m->grass4.width,m->grass4.height);
        create_terrain(m,m->grass5.x, m->grass5.y, m->grass5.width,m->grass5.height);
        break;
}
    switch (m->num_clearing){
        case 3:
            create_terrain(m,m->clearing3.x, m->clearing3.y, m->clearing3.width,m->clearing3.height);
            break;
        case 4:
            create_terrain(m,m->clearing3.x, m->clearing3.y, m->clearing3.width,m->clearing3.height);
            create_terrain(m,m->clearing4.x, m->clearing4.y, m->clearing4.width,m->clearing4.height);
            break;
        case 5:
            create_terrain(m,m->clearing3.x, m->clearing3.y, m->clearing3.width,m->clearing3.height);
            create_terrain(m,m->clearing4.x, m->clearing4.y, m->clearing4.width,m->clearing4.height);
            create_terrain(m,m->clearing5.x, m->clearing5.y, m->clearing5.width,m->clearing5.height);
            break;
    }
    switch (m->num_mixed){
        case 3:
            create_terrain(m,m->mixed3.x, m->mixed3.y, m->mixed3.width,m->mixed3.height);
            break;
        case 4:
            create_terrain(m,m->mixed3.x, m->mixed3.y, m->mixed3.width,m->mixed3.height);
            create_terrain(m,m->mixed4.x, m->mixed4.y, m->mixed4.width,m->mixed4.height);
            break;
        case 5:
            create_terrain(m,m->mixed3.x, m->mixed3.y, m->mixed3.width,m->mixed3.height);
            create_terrain(m,m->mixed4.x, m->mixed4.y, m->mixed4.width,m->mixed4.height);
            create_terrain(m,m->mixed5.x, m->mixed5.y, m->mixed5.width,m->mixed5.height);
            break;
    }

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
