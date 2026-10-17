//
// Created by clementzhao on 17/10/2026.
//

#include <ncurses.h>
#include <stdlib.h>
#include <math.h>


typedef struct {
    int height;
    int width;
}Dimensions;

typedef struct {
    int x;
    int y;
}Position;


typedef enum {
    EAST = 0,
    WEST = 1,
    NORTH = 2,
    SOUTH = 3,
}Direction;

typedef enum {
    EASY = 0,
    MEDIUM = 1,
    HARD = 2,
    DAREDEVIL = 3,
}Difficulty;


typedef struct Snake{
    Position cord;
    Direction facing;
    struct Snake *tailSnake;
    struct Snake *front;
    struct Snake *back;
}Snake;

typedef struct {
    Dimensions dim;
    Snake *snake;
    int snakeLength;
    const char *headRep;
    const char *bodyRep;
    Difficulty difficulty;
    char ***matrix;
    int point;
    Position applePosition;
    Snake latestTailSnake;
}Game;


const static int delayPerDifficulty[4] = {600, 400, 350, 200};
typedef void (*Move)(Snake *snake);

void moveLeft(Snake *snake) {
    snake->cord.x--;
    snake->front->facing = EAST;
}
void moveRight(Snake *snake) {
    snake->cord.x++;
    snake->front->facing = WEST;
}
void moveUp(Snake *snake) {
    snake->cord.y--;
    snake->front->facing = NORTH;
}
void moveDown(Snake *snake) {
    snake->cord.y++;
    snake->front->facing = SOUTH;
}

static char **heads;
static Move* moves;

Dimensions dimensions(int height, int width) {
    return (Dimensions){
        .height=height,
        .width=width,
    };
}
Position cord(int x, int y) {
    return (Position){
    .x=x,
    .y=y,};
}

int randBetween(int min, int max) {
    return min + rand() % (max - min + 1);
}



Snake *initSnake(Position startPos, Direction startDir) {
    Snake *snake = calloc(1, sizeof(Snake));
    *snake = (Snake){
        .cord = startPos,
        .facing = startDir,
        .back = NULL,
        .front = NULL
    };
    return snake;
}

Game *initGame(Dimensions dim, Difficulty difficulty, Position startPos, Direction startDir, const char *bodyRep) {
    Game *game = calloc(1, sizeof(Game));
    Snake *snake = initSnake(startPos, startDir);
    *game = (Game){
        .dim = dim,
        .snake = snake,
        .bodyRep = bodyRep,
        .snakeLength = 1,
    };

    char *corners[] = {"╔", " ╗", "╚", "╝"};
    char *edges[] = {"║", "═"};
    game->matrix = calloc(1, sizeof(char **));
    char ****gameMatrix = &game->matrix;
    for (int i = 0; i<dim.height; i++) {
        game->matrix[i] = calloc(dim.width, sizeof(char *));
    }

    *gameMatrix[0][0] = corners[0];
    *gameMatrix[0][game->dim.width-1] = corners[1];
    *gameMatrix[game->dim.height-1][0] = corners[2];
    *gameMatrix[game->dim.height-1][game->dim.width-1] = corners[3];

    for (int i = 1; i<dim.height-1; i++) {
        *gameMatrix[i][0] = edges[0];
        *gameMatrix[i][dim.height-2] = edges[0];
    }
    for (int i  = 1; i<dim.width-1; i++) {
        *gameMatrix[0][i] = edges[1];
        *gameMatrix[dim.width-2][i] = edges[1];
    }
    for (int i = 1; i<dim.height-1; i++) {
        for (int j = 1; j<dim.width-1; j++) {
            *gameMatrix[i][j] = " ";
        }
    }
    game->difficulty = difficulty;
    return game;
}


void growLength(Game *game) {
    game->snake->back = initSnake(game->latestTailSnake.cord, game->latestTailSnake.facing);
    game->snake->tailSnake = game->snake->back;
    game->matrix[game->snake->back->cord.y][game->snake->back->cord.x] = game->bodyRep;
}

void updateMatrix(Game *game) {
    game->latestTailSnake = *game->snake->tailSnake;
    game->matrix[game->latestTailSnake.cord.y][game->latestTailSnake.cord.x] = " ";
    game->matrix[game->snake->cord.y][game->snake->cord.x] = game->headRep;
}

void updateSnake(int control, Game *game) {
    Snake *snake = game->snake;
    switch (control) {
        case 'W':
            game->headRep = heads[NORTH];
            moves[NORTH](snake);
            break;
        case 'A':
            game->headRep = heads[SOUTH];
            moves[EAST](snake);
            break;
        case 'S':
            game->headRep = heads[SOUTH];
            moves[SOUTH](snake);
            break;
        case 'D':
            game->headRep = heads[SOUTH];
            moves[WEST](snake);
            break;
        default:
            ;
    }
    Snake *snakePtr = snake;
    Snake *tempSnake;
    do {
        tempSnake = snake->back;
        snakePtr->back->cord = snakePtr->cord;
        snakePtr->cord = tempSnake->cord;


        snakePtr->back->facing = snakePtr->facing;
        snakePtr->facing = tempSnake->facing;
        snakePtr = snakePtr->back;
    }while (snakePtr->back != NULL);
    updateMatrix(game);
}

void spawnFruit(Game *game) {
    int x = randBetween(1, game->dim.width);
    int y = randBetween(1, game->dim.height);
    game->applePosition = cord(x, y);
    game->matrix[y][x] = "A";
}

float posDistance(Position a, Position b) {
    return (float) sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}


void handleFruitCollision(Game *game) {
    if (posDistance(game->snake->cord, game->applePosition) == 0) {
        game->point++;
        spawnFruit(game);
    }
}

void renderMap(Game game) {
    erase();

    for (int y = 0; y < game.dim.height; y++) {
        for (int x = 0; x < game.dim.width; x++) {
            mvaddstr(y, x, game.matrix[y][x]);
        }
    }

    refresh();
}
static bool running = true;

void handleWallCollision(Game *game) {
    Snake snake = *game->snake;
    int x = snake.cord.x;
    int y = snake.cord.y;
    if (y <=0 || y >= game->dim.height || x <=0 || x >= game->dim.width) {
        running = false;
        erase();

        mvprintw(5, 10, "GAME OVER");
        mvprintw(7, 10, "Press any key to exit");

        refresh();

        while (getch() == ERR) {
            napms(10);
        }

        endwin();
    }
}

int main(int argc, char *argv[]) {
    moves = calloc(4, sizeof(Move*));
    Move ms[4] = {&moveLeft, &moveRight, &moveUp, &moveDown};
    heads = calloc(4, sizeof(char*));
    char *hs[4] = {"<", ">", "^", "v"};

    for (int i = 0; i<4; i++) {
        moves[i] = ms[i];
        heads[i] = hs[i];
    }

    Dimensions dim = dimensions(15, 30);
    Game *game = initGame(dim, DAREDEVIL, cord (dim.width/2,dim.height/2), NORTH, "*");

    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);

    while (running) {
        int key = getch();
        if (key != ERR) {
            updateSnake((char)key, game);
            handleFruitCollision(game);
            renderMap(*game);
        }
        napms(delayPerDifficulty[game->difficulty]);
    }
}
