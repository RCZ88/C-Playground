//
// Created by clementzhao on 13/10/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include "../SALOK.h"

#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"
#define YELLOW "\033[33m"
#define RESET   "\033[0m"

// Key ASCII Codes
#define KEY_ESC 27
#define KEY_ENTER_CR 13 // Carriage Return '\r' (Windows / POSIX Raw)
#define KEY_ENTER_LF 10 // Line Feed '\n' (POSIX Standard)

// -------------------------------------------------------------
// OS Detection & Setup
// -------------------------------------------------------------
#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>

    void init_terminal(void) {
        // Windows _getch() handles raw mode automatically
    }

void restore_terminal(void) {
        // Nothing to clean up on Windows
    }

int get_key(void) {
        return _getch();
    }

#else
#include <termios.h>
#include <unistd.h>

static struct termios oldt, newt;

void init_terminal(void) {
    // Save current terminal attributes
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    // Disable canonical mode (line buffering) and local echo
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
}

void restore_terminal(void) {
    // Restore original terminal attributes
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}

int get_key(void) {
    return getchar();
}
#endif



typedef enum {
    CenterStart,
    CenterEnd,
    SplitStart,
    SplitEnd,
}PrintOrientation;

typedef enum {
    VERTICAL,
    HORIZONTAL,
}StackAlignment;

typedef enum {
    FROM = 0,
    TO = 1,
}FromTo;

typedef struct {
    int height;
    char **str;
    int maxWidth;
}TDString;

typedef struct {
    char keybind;
    char *str;
    int navToMenuId;
    int fromMenuId;
    // Menu navTo;
}Action;

typedef struct {
    int id;
    int staticsCount;
    char **statics;
    Action *validInputs;
    int *navStrStaticIndex;
    int navInputCount;
    int viCount;
    // int exitKeyIndex;
}Menu;

static Menu **menus;
static int menuCount;

//
// typedef struct {
//     char keybind;
//     Menu menu;
// }Navigate;


typedef struct {
    int x;
    int y;
}Cord;

typedef struct {
    int size;
    int number;
    Cord *cords;
    bool *hit;
}Ship;

Menu *menuConstructor() {
    Menu *menu =calloc(1, sizeof(Menu));
    menus[menuCount] = menu;
    menu->id = menuCount++;
    return menu;
}

void initMenu(Menu *menu, const int staticsCount, const int viCount, const char validInputs[], char* viStr[], int menuNavId[], const int navCount, const int navStrStaticIndex[]) {
    // Menu *menu =

    menu->staticsCount = staticsCount;
    menu->viCount = viCount;
    menu->navInputCount = navCount;
    menu->navStrStaticIndex = calloc(navCount, sizeof(int));
    menu->validInputs = callocc(menu->viCount, sizeof(char), __LINE__).heap;
    for (int i = 0; i<viCount; i++) {
        menu->navStrStaticIndex[i] = navStrStaticIndex[i];
        menu->validInputs[i] = (Action){
            .keybind = validInputs[i],
            .fromMenuId = menu->id,
            .navToMenuId = menuNavId[i] == -1 ? menu->id : menuNavId[i], //navigate to the index of
            .str = viStr[i]};
    }
    // return menu;
}

void addStatic(Menu *menu, ...) {
    va_list strings;
    va_start(strings, menu);
    for (int i = 0; i < count; i++) {
        strcpy(menu->statics[menu->staticsCount], va_arg(strings, char*));
        menu->staticsCount++;
    }
    va_end(strings);
}

static char *centerize(int maxLen, char *str) {
    if (maxLen % 2 == 0) {
        maxLen++;
    }
    size_t len = strlen(str);
    char *strCopy = callocc(len+1, sizeof(char), __LINE__).heap;
    strcpy(strCopy, str);
    if (len % 2 == 0) {
        strCopy[len] = ' ';
        len++;
    }
    size_t space = maxLen/2 - len/2;
    char *centered = callocc(maxLen, sizeof(char), __LINE__).heap;
    char *s = " ";
    for (int i = 0; i < space; i++) strcat(centered, s);
    strcat(centered, str);
    for (size_t i = space; i < maxLen; i++) strcat(centered, s);
    return centered;
}

static TDString concatStringX(const int count, int spacing, const TDString *strings) {
    int maxHeight = 0;
    size_t maxWidth =0;

    for (int i = 0; i < count; i++) {
        int height = strings[i].height;
        char **str = strings[i].str;
        if (height >maxHeight) maxHeight = height;
        for (int j = 0; j<height; j++) {
            size_t strLen = strlen(str[i]);
            if (strLen > maxWidth) maxWidth = strLen;
        }
    }
    size_t widthTotal = count * maxWidth + (count-1) * spacing;
    char **concat = callocc(maxHeight, sizeof(char *), __LINE__).heap;
    char *space = callocc(spacing, sizeof(char), __LINE__).heap;
    for (int i = 0; i<spacing; i++) {
        space[i]  = ' ';
    }
    for (int i = 0; i<maxHeight; i++) {
        concat[i] = callocc(widthTotal, sizeof(char), __LINE__).heap;
        size_t curOffset = 0;
        for (int j = 0; j<count; j++) {
            char **str = strings[j].str;
            memcpy(&concat[i][curOffset], str[i], strlen(str[i]));
            curOffset += strlen(str[i]);
            if (j == count-1) {
                break;
            }
            memcpy(&concat[i][curOffset], space, strlen(space));
            curOffset += strlen(space);
        }
    }

    return  (TDString){
    .height = maxHeight,
        .str = concat,
        .maxWidth = (int)maxWidth
    };
}


typedef struct {
    Ship *ships;
    int shipCount;
    int drownedShip;
    TDString boardString;
    Cord *attacks;
    Cord *bombs;
}Board;

char **initBoard(const int size) {
    char **numLet = callocc(size, sizeof(char *), __LINE__).heap;
    for (int i = 0; i < size-1; i++) {
        numLet[i] = callocc(size, sizeof(char), __LINE__).heap;
        numLet[0][i+1] = (char) (i+1 + '0');
        numLet[i+1][0] = (char) (i + 'A');
        if (i == 0) {
            continue;
        }
        for (int j = 1; j < size; j++) {
            numLet[i][j] = '.';
        }
    }
    return numLet;
}

void printBoard(char **board, const int size, const char toColor, char *color, char *noColor) {
    for (int i = 0; i<=size; i++) {
        for (int j = 0; j<=size; j++) {
            char c = board[i][j];
            if (i == 0 || j == 0) {
                printf("%c", c);
                continue;
            }
            if (c == '.') {
                printf(BLUE"."RESET);
            }else if (c == 'X') {
                printf(RED"X"RESET);
            }else if (c == '@') {
                printf(YELLOW"@"RESET);
            }else {
                if (c == toColor) {
                    printf("%s%c"RESET, color, toColor);
                    continue;
                }
                printf("%s%c"RESET, noColor, toColor);
            }
        }
    }
}

TDString borderize(const TDString *strings, int count,  StackAlignment sa, int padding, int margin, bool centered) {
    size_t maxLength = strings[0].maxWidth;
    size_t totalHeight = 0;
    size_t totalLength;
    for (int i = 0; i<count; i++) {
        totalHeight += strings[i].height + 2 * padding + 1;
        if (strings[i].maxWidth > maxLength) maxLength = strings[i].maxWidth;
    }
    totalHeight++;
    totalLength = maxLength + 2*padding + 2;

    int lineIndexes[count+1];
    int sumLI = 0;
    lineIndexes[0] = 0;
    bool isThereLine[totalHeight];
    for (int i = 0; i<totalHeight; i++)isThereLine[i] = false;
    for (int i = 1; i<count; i++) {
        sumLI += strings[i].height;
        lineIndexes[i] = sumLI;
        isThereLine[sumLI] = true;
    }
    char **bordered = callocc(totalHeight, sizeof(char*), __LINE__).heap;
    switch (sa) {
        case VERTICAL:
            for (int i = 0; i < totalHeight; i++) {
                bordered[i] = callocc(totalLength, sizeof(char), __LINE__).heap;
                bordered[i][0] = isThereLine[i] ? '+' : '|';
            }
            for (int i = 0; i<count+1; i++){
                for (int j = 1; j<totalLength-1; j++) {
                    bordered[i][j] = '=';
                }
            }

            for (int i = 0; i<count; i++) {
                for (int k = lineIndexes[i]+1; k<strings[i].height; k++) {
                    if (k <= margin || totalLength-1-k <= margin) {
                        bordered[i][k] = ' ';
                        continue;
                    }
                    int j = k - lineIndexes[i] + 1;
                    char *str = strings[i].str[j];
                    strcpy(bordered[k], str);
                }
            }
            break;
        case HORIZONTAL:

            break;
    }
    return (TDString){
    .height = (int)totalHeight,
        .maxWidth = (int)totalLength,
    .str = bordered};
}


bool isValidInput(char input, Menu menu) {
    for (int i = 0; i<menu.viCount; i++) {
        if (input == menu.validInputs[i].keybind) {
            return true;
        }
    }
    return false;
}
static const Action NO_ACTION = (Action){.keybind = ' ', .fromMenuId = -1};
static Action CUR_IN = NO_ACTION;
static Menu CUR_MENU;
static const char *TITLE =
"  ____              _       _        ___              _     _   \n"
" |  _ \\ _ __ ___   / \\   __| |_ __  / _ \\ _   _  __ _| |__ | |_ \n"
" | | | | '__/ _ \\ / _ \\ / _` | '_ \\| | | | | | |/ _` | '_ \\| __|\n"
" | |_| | | |  __// ___ \\ (_| | | | | |_| | |_| | (_| | | | | |_ \n"
" |____/|_|  \\___/_/   \\_\\__,_|_| |_|\\___/ \\__,_|\\__, |_| |_|\\__|\n"
"                                                |___/            \n";

Action getControlOf(char key) {
    return (Action){.keybind = key, .fromMenuId = CUR_MENU.id};
}

Action handleCorrectInput(Menu menu){
    char out = '\r';
    int inKey = get_key();
    switch (inKey) {
        case KEY_ESC:
            out =  '\x1b';
            break;
        case !KEY_ENTER_CR && !KEY_ENTER_LF: // translates to a || b
            break;
        default:
            if (inKey < 32 || inKey > 126) {
                printf("Illegal Input!");
                out = handleCorrectInput(menu).keybind;
            }
            out = inKey;
            break;
    }
    if (!isValidInput(out, menu)) {
        printf("Invalid input! (%c) is not an option!", out);
        out = handleCorrectInput(menu).keybind;
    }
    return getControlOf(out);
}

bool equateControl(Action a, Action b) {
    if (a.keybind == b.keybind && a.fromMenuId == b.fromMenuId) {
        return true;
    }
    return false;
}

typedef struct {
    int mainMenuId;
}GameData;

GameData initGame() {
    menus = callocc(10, sizeof(Menu*), __LINE__).heap;

    Menu *mainMenu = menuConstructor();
    Menu *rearrange = menuConstructor();

    initMenu(mainMenu, 4, 3,
        (char[]){'1', '2', '3'},
        (char*[]){"Play", "How to Play", "Exit"},
        (int[]){rearrange->id, },
        3, (int[]){0, 1, 2});
    addStatic(mainMenu,
        TITLE,
        "1. Play",
        "2. How to Play",
        "3. Exit");

    initMenu(rearrange, 2, 13,
        (char[]){'\x1b',  'W', 'A', 'S', 'D', 'R', '\r', '0', '1', '2', '3', '4', '5'},
        (char*[]){"Main menu", "Up", "Left", "Down", "Right", "Rotate", "Confirm Placement", "Conclude Arrangement", "Select Ship"},
        (int[]){mainMenu->id, },
        1, (int[]) {0, 6});
    addStatic(rearrange,
        "Rearrange your Ships!");
    return (GameData){
        mainMenu->id,
    };
}

typedef enum {
    DOT = '.',
    BRACKETS = '['
}ControlOutputStyle;


TDString getControlsString(ControlOutputStyle style, StackAlignment alignment) {
    char **controls = callocc(CUR_MENU.viCount, sizeof(char *), __LINE__).heap;

    Action *actions = CUR_MENU.validInputs;
    switch (alignment) {
        case VERTICAL:
            for (int i = 0; i<CUR_MENU.viCount; i++) {
                controls[i] = callocc(10, sizeof(char), __LINE__).heap;
                char *ctrl = callocc(80, sizeof(char), __LINE__).heap;
                char str[1];
                str[0] = actions->keybind;
                char *name = actions->str;
                char *mod;
                switch (style) {
                    case DOT:
                        strcat(ctrl, str);
                        mod =". ";
                        strcat(ctrl, mod);
                        strcpy(controls[i], ctrl);
                        strcpy(controls[i], name);
                        break;
                    case BRACKETS:
                        mod = "[";
                        strcat(ctrl, mod);
                        strcat(ctrl, str);
                        mod = "]";
                        strcat(ctrl, mod);
                        strcpy(controls[i], ctrl);
                        strcpy(controls[i], name);
                        break;
                }
            }
            break;
        case HORIZONTAL:
            break;
    }
}

Menu getMenu(int id) {
    return *menus[id];
}

// typedef enum {
//     ROTATE = 'R',
//     UP = 'W',
//     DOWN = 'S',
//     LEFT = 'A',
//     RIGHT = 'D',
// }SetupShip;
//
// typedef union{
//     bool exit;
//     int navToMenuId;
//     int e;

// }Action;



int main(int argc, char *argv[]) {
    init_terminal();

    GameData gameData = initGame();


    const Action exitControl = (Action){
        .fromMenuId = gameData.mainMenuId,
        .keybind = 3};


    CUR_MENU = getMenu(gameData.mainMenuId);
    while (equateControl(CUR_IN, exitControl)) {
        CUR_IN = handleCorrectInput(CUR_MENU);

    }

    printf("%s", TITLE);


}
