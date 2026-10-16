//
// Created by clementzhao on 16/10/2026.
//
#include <math.h>
#include <ncurses.h>
#include <stddef.h>

static int gravityConst = -1;

typedef struct {
    int x;
    int y;
}Cords;

typedef struct {
    int width;
    int height;
}Size;

typedef struct {
    Cords cords;
    Size size;
}Platform;

typedef struct {
    Cords cords;
    int speed;
}Projectile;

typedef struct {
    int score;
    int hp;
    Cords cords;
    int speed;
    int jumpHeight;
    bool landed;
    int jumpStreakCount;
}Player;

typedef enum {
    HEAL = 'H',
    COIN = 'C',
    PLATFORM = '='
}CharRep;



typedef struct {
    int heal;
    int points;
    Cords cords;
    CharRep type;
}Env;

typedef enum {
    ONE_DIRECTION = 1,
    TWO_DIRECTION = 2,
    STILL = 0
}Movement;

typedef struct {
    Movement movement;
    int moveRange;
    Cords moveDirection;
    Cords curLocation;
    Cords originalLocation;
    int movSpeed;
    int hp;
    int dmg;
}Entity;


typedef struct {
    Size size;
    Cords playerStartLoc;
    Platform **platforms;
    int platformCount;
    Env **envs;
    int envsCount;
    Entity **entities;
    int entitiesCount;
    char **screen;
    bool **occupied;
}Map;


static Player *currentPlayer;
static Map *currentMap;

Cords cord(int x, int y) {
    return (Cords){
        .x = x,
        .y = y
    };
}

void updateScreenMatrix(Map *map, Player player) {
    for (int i = 0; i<map->platformCount; i++) {
        Size platformSize = map->platforms[i]->size;
        Cords platformCords = map->platforms[i]->cords;
        for (int y = platformCords.y; y < platformSize.height; y++) {
            for (int x = platformCords.x; x < platformSize.width; x++) {
                if (map->occupied[y][x]) {
                    printf("COLLISION DETECTED!");
                    return;
                }
                map->screen[y][x] = PLATFORM;
                map->occupied[y][x] = true;
            }
        }
    }

    for (int i = 0; i<map->envsCount; i++) {
        Env *env = map->envs[i];
        int y = env->cords.y;
        int x = env->cords.x;
        if (map->screen[y][x]) {
            printf("COLLISION DETECTED!");
            return;
        }
        map->screen[y][x] = env->type;
        map->occupied[y][x] = true;
    }
    map->screen[player.cords.y][player.cords.x] = '@';
}

Map initMap(int size, Platform **platforms, Env **envs) {

}


Env initEnv(Cords cords, CharRep type) {
    return (Env){
    .cords = cords,
    .type = type};
}

Env initHeal(Cords cords, int healAmount) {
    Env ret = initEnv(cords, HEAL);
    ret.heal = healAmount;
    return ret;
}

Env initCoin(Cords cords, int point) {
    Env ret = initEnv(cords, COIN);
    ret.points = point;
    return ret;
}

Entity initEnemy(Cords cords, int damage, int hp) {

}

int calcDistance(Cords a , Cords b) {
    return  (int)sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void reverseDirection(Entity *entity) {
    entity->moveDirection = cord(entity->moveDirection.x * -1, entity->moveDirection.y & -1);
}
void entityMove(Entity *entity) {
    entity->curLocation = cord(entity->curLocation.x + entity->moveDirection.x * entity->movSpeed, entity->curLocation.y + entity->moveDirection.y * entity->movSpeed);
}

void handleEntityMovement(Map *map) {
    for (int i = 0; i<map->entitiesCount; i++) {
        Entity *entity = map->entities[i];
        int distanceFromInitial = calcDistance(entity->curLocation , entity->originalLocation);
        if (distanceFromInitial == 0 || distanceFromInitial == entity->moveRange) {
            reverseDirection(entity);
            continue;
        }
        entityMove(entity);
    }
}


bool isTouching(Player player, Map map, CharRep touchingWhat, Cords *checkRelativeToUser, int amtToCheck) {
    for (int i = 0; i<amtToCheck; i++) {
        if (map.screen[player.cords.y + checkRelativeToUser[i].y][player.cords.x - checkRelativeToUser[i].x] == touchingWhat) {
            return true;
        }
    }
    return false;
}

void gravity(Player *player) {
    while (!isTouching(*player, *currentMap, PLATFORM, (Cords[]) {cord(0, -1)}, 1)) {
        player->cords.y += gravityConst;
    }
    player->landed = true;
    player->jumpStreakCount = 0;
}



void movePlayer(char input, Player *player) {
    switch (input) {
        case 'a':
            player->cords.x += player->speed;
        case 'd':
            player->cords.x -= player->speed;
        case ' ':
            if (player->landed || player->jumpStreakCount < 2) {
                player->cords.y += player->jumpHeight;
                player->jumpStreakCount++;
            }
        default:
            ;
    }
}

void renderMap(char **map) {
    erase();

    for (int y = 0; y < currentMap->size.height; y++) {
        for (int x = 0; x < currentMap->size.width; x++) {
            mvaddch(y, x, map[y][x]);
        }
    }

    refresh();
}




int main(int argc, char *argv[]) {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    Player player = (Player){
        .score = 0,
        .hp = 3,
        .speed = 1,
        .cords = cord(0,0),
        .jumpHeight = 1
    };

    nodelay(stdscr, TRUE);
    bool running = true;


    while (running) {
        char input =  getch();
        movePlayer(input, &player);
        renderMap(currentMap->screen);
    }

    endwin();
    return 0;
}
