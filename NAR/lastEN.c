//
// Created by clementzhao on 17/10/2026.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

static const int arrCapacity = 1234;
static Node **bucket;

typedef struct Time {
    int hour;
    int minute;
}Time;


typedef struct Date {
    int date;
    int month;
    int year;
}Date;


typedef struct timeStamp {
    Time time;
    Date date;
}TimeStamp;

typedef struct Scrobble {
    char *title;
    char *artist;
    TimeStamp timeStamp;
}Scrobble;

typedef struct User {
    char *name;
    char *password;
    Scrobble *scrobbles;
    int scrobbleCount;
    Node **track_table;
    Node **artist_table;
}User;

char *getStringOfTimeStamp(TimeStamp timeStamp) {
    char buffer[30];
    sprintf(buffer, "%d-%d-%d %d-%d", timeStamp.date.date, timeStamp.date.month, timeStamp.date.year, timeStamp.time.hour, timeStamp.time.minute);
    return buffer;
}

TimeStamp timeStamp(int d, int month, int y, int h, int min) {
    return (TimeStamp){
        .date = (Date){.date = d, .month = month, .year = y},
        .time = (Time){.hour = h, .minute = min}
    };
}

unsigned long hash_djb2(const unsigned char *s) {
    unsigned long hash = 5381;
    int c;
    while ((c = *s++)) {
        hash = (hash << 5) + hash + c;
    }
    return hash % arrCapacity;
}

User *initUser(const char *name, const char *password) {
    User *user = malloc(sizeof(User));
    *user = (User){
    .name = name,
    .password = password,};

    user->artist_table = calloc(arrCapacity, sizeof(Node *));

}
Scrobble *initScrobble(char *title, char *artist, TimeStamp timeStamp) {
    return &(Scrobble){
    .title = title,
    .artist = artist,
    .timeStamp = timeStamp,};
}

void addScrobble(User *user, Scrobble scrobble) {
    user->scrobbles[user->scrobbleCount] = scrobble;
    unsigned long artistHash = hash_djb2((unsigned char *)scrobble.artist);
    if (bucket[artistHash] == NULL) {
        user->artist_table[artistHash] = initNode(scrobble.artist, NULL, NULL);
        bucket[artistHash] = user->artist_table[artistHash];
    }else {
        insertTail(&user->scrobbleCount, user->artist_table[artistHash]);
    }
    unsigned long trackHash = hash_djb2((unsigned char *) scrobble.title);
    if (bucket[trackHash] == NULL) {
        user->track_table[trackHash] = initNode(&user->scrobbleCount, NULL, NULL);
        bucket[trackHash] = user->track_table[trackHash];
    }else {
        insertTail(&user->scrobbleCount, user->track_table[trackHash]);
    }
}


Scrobble *findScrobbleByTrack(User user, const char *title) {
    unsigned long trackHash = hash_djb2((unsigned char *)title);
    if (bucket[trackHash] == NULL) {
        return NULL;
    }
    Node *node = user.track_table[trackHash];
    while (node->next != NULL) {
        if (strcmp(node->val, title) == 0) {
            return &user.scrobbles[*(int *)node->val];
        }
    }
    return NULL;
}

Scrobble *findScrobbleByArtist(User user, const char *artist) {
    unsigned long artistHash = hash_djb2((unsigned char *)artist);
    if (bucket[artistHash] == NULL) {
        return NULL;
    }
    Node *node = user.track_table[artistHash];
    while (node->next != NULL) {
        if (strcmp(node->val, artist) == 0) {
            return &user.scrobbles[*(int *)node->val];
        }
    }
    return NULL;
}

void initBucket() {
    bucket = calloc(arrCapacity, sizeof(Node *));
}



int main(int argc, char *argv[]) {
    // char *str = "I love Nathalie Ang";
    // unsigned long hashed = hash_djb2((unsigned char *)str);
    // printf("%ld", hashed);
    //
    initBucket();
}
