//
// Created by clementzhao on 17/10/2026.
//


#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


typedef enum PokeType {
    ELECTRIC = 0,
    WATER,
    FIRE,
    PSYCHIC,
    FIGHTING,
    SHADOW,
    GRASS,
}Element;

typedef struct Move {
    int id;
    char name[32];
    Element type;
    int power;
    int accuracy;
    int maxUsage;
}Move;

static const int movesVarOffset[] =
{
    offsetof(Move, id),
    offsetof(Move, name),
    offsetof(Move, type),
    offsetof(Move, power),
    offsetof(Move, accuracy),
    offsetof(Move, maxUsage),
};


typedef struct PokemonSpecies {
    int id;
    char name[32];
    int type;
    int baseHp;
    int baseAtk;
    int baseDef;
    int baseSpd;
    int evolveToId;
    int evolveLevel;
    int moveIds[4];
    int moveCount;
}PokemonSpecies;

typedef struct KnownMove {
    int moveId;
    int currentPP;
} KnownMove;

typedef struct Pokemon {
    int speciesId;
    char nickName[32];
    int level;
    int xp;
    int curHp;
    int maxHp;
    int atk;
    int def;
    int spd;
    KnownMove moves[4];
    int moveCount;
}Pokemon;


typedef struct Node {
    Pokemon *data;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct DList {
    Node *head;
    Node *tail;
    int size;
} DList;

typedef struct User {
    char username[32];
    char password[32];

    DList team;
    DList collection;
    DList inventory;

    int money;
    int badges;
}User;



static Move ALL_MOVES[];
static float TYPE_CHART[8][8];
static PokemonSpecies ALL_PS[];


bool isString(const char datBuffer[]) {
    return datBuffer[0] > 'a' && datBuffer[0] <= 'z' || datBuffer[0] >= 'A' && datBuffer[0] <= 'Z';
}

bool isArray(char datBuffer[], char split) {
    char *ptr = datBuffer;
    while (*ptr != split) {
        if (*ptr == ',') {
            return true;
        }
    }
    return false;
}

bool isInt(const char datBuffer[]) {
    return datBuffer[0] > '0' && datBuffer[0] <= '9';
}

// typedef struct dt {
//     bool arr;
//     bool string;
// }dt;

char *skipComment(char *ptr) {
    while (*ptr != '\n') {
        ptr++;
    }
    return ptr+1;
}

int stringToInt(char *string) {
    int num = 0;
    size_t len = strlen(string);
    int expo = 0;
    for (int i = 0; i<len; i++) {
        if (string[i] == ',' || string[i] == '|' || string[i] == '\n') {
            return num;
        }
        expo = (int)len - i - 1;
        num += (string[i] - '0') * (int) pow(10, expo);
    }
    return num;
}

typedef enum WHAT {
    MOVES,
    SPECIES,
}WHAT;
static const int strCheck = 0;
static const int arrCheck = 1;

void loadMove(char *fileName, char split, int varCount, void **toFill, WHAT what) {
    FILE *fo = fopen(fileName, "r");
    if (!fo) {
        return;
    }
    char buffer[16384];
    fgets(buffer, 0, fo);
    char *ptr = buffer;



    int *dts[varCount]; //bitflag
    int i = 0;
    bool isStr = false;
    bool isArr = false;

    while (*ptr != '\n') {
        if (*ptr == '#') {
            ptr = skipComment(ptr);
        }
        if (*ptr == split) {
            int bf =0;
            bf |= isStr << strCheck;
            bf |= isArr << arrCheck;

            dts[i++] = &bf;
            continue;
        }
        if (dts[i] != NULL) {
            continue;
        }
        isArr = isArray(ptr, split);
        isStr = isString(ptr);
        ptr++;
    }

    int itemCount = 0;
    char datBuffer[32];
    int dbI = 0; //data buffer index
    int dtI = 0; //datatype index
    int offsetIndexCount = 0;

    void **ptrToVar = calloc(varCount, sizeof(void *));
    int ptiI = 0;
    int strLen = 0;

    while (*ptr != '\0') {
        if (*ptr == '#') {
            ptr = skipComment(ptr);
        }
        if (*ptr == split) {
            dtI++;
            offsetIndexCount++;
            datBuffer[dbI+1] = '\0';
            switch (*dts[i]) {
                case 0: // !arr !str
                    int num = stringToInt(datBuffer);
                    ptrToVar[ptiI] = &num;
                    break;
                case 1: { // arr !str
                    int size = strlen(datBuffer);
                    int nums[size];
                    int k = 0;
                    for (int j = 0; j<size; j++) {
                        if (datBuffer[j] == ',') {
                            k++;
                            j++;
                        }
                        int n= stringToInt(datBuffer);
                        nums[k] = n;
                    }
                    ptrToVar[ptiI] = &nums[k];
                    break;
                }
                case 2: // !arr str
                    int len = strlen(datBuffer);
                    char *str = calloc(len, sizeof(char));
                    memcpy(str, datBuffer, len);
                    break;
                case 3: {// arr str
                    int size = strlen(datBuffer);
                    char *strs[size];
                    int l = 0;
                    int k = 0;
                    char bfr[32];
                    for (int j = 0; j<size; j++) {
                        if (datBuffer[j] == ',') {
                            bfr[l] = '\0';
                            char *s = calloc(l, sizeof(char));
                            memcpy(s, strs[j], l);
                            k++;
                            j++;
                            l = 0;
                        }
                        bfr[l++] = datBuffer[j];
                    }
                }
            }
            dbI = 0;
            strLen = 0;
        }
        if (*ptr == '\n') {
            switch (what) {
                case MOVES: {
                    Move move = (Move){};
                    void *objPtr = &move;
                    for (int k = 0; k<varCount; k++) {
                        objPtr = &move + movesVarOffset[k];
                        objPtr = ptrToVar[k];
                    }
                    toFill[itemCount++];
                    switch (*dts[i]) {

                    }
                }


                case SPECIES:
                    break;

            }
        }
        datBuffer[dbI++] = *ptr++;
    }

}

bool doesHit(int moveId) {
    return rand() % 100 >= ALL_MOVES[moveId].accuracy;
}

int getDamage(int base, float multi, int roll) {
    return  (int)fmax(1, (int)(base * multi * roll / 100));
}

bool canUseMove(Pokemon pokemon, int moveId) {
    return pokemon.moveCount > pokemon.moves[moveId].currentPP;
}

void *applyDamage(Pokemon *pokemon, int damage) {
    pokemon->curHp -= damage;
}


void pokemonUseMove(Pokemon *attacker, Pokemon *defender, int moveId, int roll) {
    if (!doesHit(moveId)) {
        return;
    }
    if (canUseMove(*attacker, moveId)) {
        Move move = ALL_MOVES[moveId];
        PokemonSpecies ps =  ALL_PS[defender->speciesId];
        int baseDamage = (2*attacker->level + 2) * move.power * attacker->atk/defender->def/50+2;
        float multi = TYPE_CHART[move.type][ps.type];
        int finalDamage = getDamage(baseDamage, multi, roll);
        applyDamage(defender, finalDamage);
    }
}

Pokemon *createPokemon(int speciesId, int level, char name[32]) {
    return &(Pokemon){
        .nickName = *name,
        .speciesId = speciesId,
        .level = level,
    };
}

void restorePokemon(Pokemon *pokemon) {
    pokemon->curHp = pokemon->maxHp;
}

bool samePokemonName(Pokemon p1, Pokemon p2) {
    return p1.nickName == p2.nickName;
}

Node *getNodeOfPokemon(User *user, Pokemon *pokemon) {
    Node *head = user->team.head;
    while (head->next != NULL) {
        if (samePokemonName(*head->data, *pokemon)) {
            return head;
        }
    }
    return NULL;
}

Node *getNodeOfIndex(User player, int index) {
    int i = 0;
    Node *head = player.team.head;
    while (i < index) {
        head = head->next;
    }
    return head;
}

void movePokemon(User *user, Pokemon *pokemon, int newPos) {
    if (newPos > 4) {
        return;
    }
    Node *node = getNodeOfIndex(*user, newPos);
    Node *currentPokemonIndex = getNodeOfPokemon(user, pokemon);
    Pokemon **temp = calloc(1, sizeof(Pokemon*));
    if (node->data != NULL) {
        temp[0] = node->data;
    }
    node->data = pokemon;
    if (temp != NULL) {
        currentPokemonIndex->data = temp[0];
    }
}
