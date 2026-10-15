//
// Created by clementzhao on 14/10/2026.
//

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../SALOK_V2.h"

typedef struct{
    char rank;
    int value;
}Card;

typedef struct {
    char *name;
    char *password;
    int wins;
}Player;


static Player *players;
static int numPlayers;



DA_TYPE(Card) initCards() {
    DynamicArr cards = arr(52, sizeof(Card), __LINE__);
    char cardRanks[13];
    for (int i = 1; i <=9; i++) {
        cardRanks[i] = (char) (i + '0');
    }
    cardRanks[10] = 'J';
    cardRanks[11] = 'Q';
    cardRanks[12] = 'K';
    cardRanks[0] = 'A';


    for (int i = 1; i<13; i++) {
        int value = i;
        if (i >= 10) {
            value = 10;
        }
        addItem(&cards, &(Card){
        .rank = cardRanks[i],
        .value = value,
        });
    }
    return cards;
}

int getValueOfAce(int currentTotal) {
    if (currentTotal + 11 > 21) {
        return 1;
    }
    return 11;
}

bool isAce(Card card) {
    return card.rank == 'A';
}

bool isAlphanumeric(const char *password) {
    int i = 0;
    while (password[i++] != '\0') {
        if (!(password[i] >= 'A' && password[i] <= 'Z' || password[i] >= 'a' && password[i] <= 'z' || password[i] >= '0' && password[i] <= '9')) {
            return false;
        }
    }
    return true;
}


int stringToInt(char *string) {
    int num = 0;
    size_t len = strlen(string);
    int expo = 0;
    for (int i = 0; i<len; i++) {
        expo = (int)len - i - 1;
        num += (string[i] - '0') * (int) pow(10, expo);
    }
    return num;
}


DynamicArr splitString(char *str, char splitChar) {
    int initSize =2;
    DynamicArr strs = arr(initSize, sizeof(DynamicArr*), __LINE__);
    int itemCount = 0;

    int strIndex = 0;
    int strLen = 0;
    while (str[strIndex] != '\0') {
        if (str[strIndex] == splitChar) {
            strLen = 0;
            addItem(&strs, getDat(arr(initSize, sizeof(char), __LINE__)));
            memcpy(&getDat(strs)[itemCount++], &str[strIndex++], strLen);

            continue;
        }
        strLen++;
        strIndex++;
        // strs[itemCount][charIndex++] = *str++;
    }
    return strs;
}

void loadPlayersData(char *filePath) {
    FILE *fp = fopen(filePath, "rw");
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    rewind(fp);
    if (size < 0) {
        fclose(fp);
    }
    char *buffer = arr((size_t)size + 1, sizeof(char), __LINE__);
    size_t bytesRead = fread(buffer, 1, (size_t)size, fp);
    buffer[bytesRead] = '\0';

    splitString(buffer, '\n' )
}


Player constructPlayer(char *playerData) {
    DynamicArr name = arr(21, sizeof(char), __LINE__);
    DynamicArr password = arr(21, sizeof(char), __LINE__);

    int wins;
    int i = 0;
    int charICount = 0;
    while (playerData[i] != '#') {
        addItem(&name, &playerData[i]);
        i++;
    }
    i++;
    charICount = 0;
    while (playerData[i] != '#') {
        addItem(&password, &playerData[i]);
        i++;
    }
    charICount = 0;
    char winsString[10];
    i++;
    while (playerData[i] != '\0') {
        winsString[charICount++] = playerData[i];
        i++;
    }
    wins = stringToInt(winsString);

    return (Player){
        .name = *name.heap,
        .password = *password.heap,
        .wins = wins,
    };
}
typedef const void *constant;

int compareName(constant a, constant b) {
    return strcmp(((Player *)a)->name, ((Player *)b)->name);
}
int compareWins(constant a, constant b) {
    return ((Player *)a)->wins - ((Player *)b)->wins;
}

const char* filePath;

void savePlayer(Player player) {
    FILE *file = fopen(filePath, "w");
    fprintf(file, "%s#%s#%d\n", player.name, player.password, player.wins);
    fclose(file);
}

void printLeaderboard() {
    qsort(players, numPlayers, sizeof(Player), compareName);
    printf("LEADERBOARD\n");
    for (int i = 0; i<numPlayers; i++) {
        printf("%d. %s |Wins: %d", i, players[i].name, players[i].wins);
    }
}

typedef struct {
    Player player;
    bool found;
}SPR;

SPR findPlayer(char *playerName) {
    qsort(players, numPlayers, sizeof(Player), compareName);

    int startI = 0;
    int endI = numPlayers;
    int splitIndex = (endI - startI) /2;
    int compare = strcmp(players[splitIndex].name, playerName);

    while (compare != 0 || endI == splitIndex || startI == splitIndex) {
        compare = strcmp(players[splitIndex].name, playerName);
        if (!compare) {
            return (SPR){.player = players[splitIndex],  .found = true};
        }
        if (compare > 0) {
            endI = splitIndex;
        }else if (compare < 0) {
            startI = splitIndex;
        }
        splitIndex = (endI - startI) /2;

    }
    return (SPR){.player = NULL, .found = true};
}




Player registration() {
    DynamicArr name = arr(20, sizeof(char), __LINE__);
    DynamicArr tempName = arr(1000, sizeof(char), __LINE__);
    while (true) {
        printf("Enter a Username (2-20 chars): ");
        scanf("%s", (char*)getDat(tempName));
        if (strlen(getDat(tempName)) > 20 || strlen(getDat(tempName)) < 2) {
            printf("Too long or too short (2-20)");
            continue;
        }
        if (findPlayer(getDat(tempName)).found) {
            printf("Username Exists, Choose a different one!");
            continue;
        }
        strcpy(*name.heap, *tempName.heap);
        deleteArr(tempName);
        break;
    }

    DynamicArr password = arr(20, sizeof(char), __LINE__);
    DynamicArr tempPass = arr(1000, sizeof(char), __LINE__);
    while (true) {
        printf("Enter a Letter Only Password (2-20 chars): ");
        scanf("%s", (char*)getDat(password));
        if (strlen(getDat(tempPass)) > 20 || strlen(getDat(tempName)) < 2) {
            printf("Too long or too short (2-20)");
            continue;
        }
        if (!isAlphanumeric(getDat(tempPass))) {
            printf("Must ONLY contain alphabets!");
            continue;
        }
        strcpy(getDat(password), getDat(tempPass));
        deleteArr(tempPass);
        break;
    }

    Player player = (Player){
        .name = getDat(name),
        .password = getDat(password),
        .wins = 0};
    savePlayer(player);
    return player;
}

Player handleLogin() {
    printf("LOGIN");
    char *playerName = "";
    char *playerPassword = "";
    Player player;
    while (true) {
        scanf("%s", playerName);
        SPR spr = findPlayer(playerName);
        if (!spr.found) {
            printf("Player Not Found!");
            continue;
        }
        player = spr.player;
        break;
    }
    while (true) {
        scanf("%s", playerPassword);
        if (strcmp(playerPassword, player.password) == 0) {
            printf("WELCOME, %s!", playerName);
            break;
        }
        printf("WRONG PASSWORD, TRY AGAIN!");
    }
    return player;
}



void handleGame() {

}

int main() {

}

