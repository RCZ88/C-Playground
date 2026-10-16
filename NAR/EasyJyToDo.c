//
// Created by clementzhao on 15/10/2026.
//


#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef enum {
    ONGOING = 1,
    PENDING = 2,
    DONE = 3,
}Status;

typedef void (*MenuHandler)(void);
typedef void *(*SearchStringAlgo)(char *);

typedef struct {
    int optionsCount;
    char **statics;
    int *navToMenuIndex;
    MenuHandler *handlers;
}Menu;

typedef struct {
    int date;
    int month;
    int year;
}Deadline;

typedef struct {
    char *name;
    Status status;
    Deadline deadline;
}Job;

static Menu* menus;
static int menuCount;
static int userInputI;
static char *userInputS;
static Menu currentMenu;
static int menuStaticCount;

static Job *jobs;
static int jobCount;
static int mainMenuId = 0;
static Job curJob;

static char *statuses[] = {"ONGOING", "PENDING", "DONE"};
static Status statusArr[] = {ONGOING, PENDING, DONE};

static Menu constructMenu(int optCount, char** optionsString, MenuHandler handler) {
    Menu menu = (Menu){
    .optionsCount = optCount,
    .statics = optionsString,
    .handlers = &handler};
    menus[menuCount++] = menu;
    return menu;
}

static void printStatics() {
    for (int i = 0; i<currentMenu.optionsCount; i++) {
        printf("%d. %s\n", i+1, currentMenu.statics[i]);
    }
}

bool inputInt(uint32_t *assignTo, int bufferSize) {
    char buffer[bufferSize];
    if (fgets(buffer, bufferSize, stdin) != NULL) {
        errno = 0;
        char * endPtr;
        long val = strtol(buffer, &endPtr, 10);
        if (endPtr != buffer && *endPtr == '\0' || *endPtr == '\n') {
            *assignTo = (int)val;
            return true;
        }
        return false;
    }
}

static void checkInput(bool success) {
    if (!success) {
        printf("PLEASE INPUT A NUMBER");
    }
}

static int MAX = 0;
static int MIN = 1;

static void handleInputIntRange(int range[], char* inputPrint) {
    uint32_t tempUserInput = -1;
    printf("%s", inputPrint);
    bool inputSuccess = inputInt(&tempUserInput, userInputI);
    checkInput(inputSuccess);
    while (tempUserInput < range[MIN] || tempUserInput > range[MAX] || !inputSuccess) {
        if (inputSuccess) {
            printf("Input must be between %d - %d", range[MIN], range[MAX]);
            printf("%s", inputPrint);
            inputSuccess = inputInt(&tempUserInput, userInputI);
        }else {
            checkInput(inputSuccess);
        }
    }
}
static void handleInputStringRange(int range[], char* inputPrint) {
    char tempUserInput[1000];
    scanf("%s", tempUserInput);
    while (strlen(tempUserInput) < range[MIN] || strlen(tempUserInput) > range[MAX]) {
        printf("Input Length must be between %d - %d", range[MIN], range[MAX]);
        printf("%s", inputPrint);
        scanf("%s", tempUserInput);
    }
    memcpy(userInputS, tempUserInput, strlen(tempUserInput));
}


static void *handleInputStringFind(char *inputPrint, char *notFoundPrint, SearchStringAlgo searchAlgo, bool failHandlingCustom, MenuHandler handler) {
    char tempUserInput[1000];
    printf("%s", inputPrint);
    scanf("%s", tempUserInput);
    void *j = searchAlgo(tempUserInput);
    bool found = j == NULL;
    if (failHandlingCustom) {
        while (!found) {
            printf("%s", notFoundPrint);
            printf("%s", inputPrint);
            scanf("%s", tempUserInput);
            j = searchAlgo(tempUserInput);
            found = j == NULL;
        }
        return j;
    }
    if (!found) {
        (*handler)();
        return NULL;
    }
    return j;
}

static Job *findJob(char *jobName) {
    for (int i = 0; i<jobCount; i++) {
        if (strcmp(jobs[i].name, jobName) == 0) {
            return &jobs[i];
        }
    }
    return NULL;
}

static void *findJobWrapper(char *jobName) {
    return findJob(jobName);
}

void printJobs(void) {
    printf("Existing Jobs");
    for (int i = 0; i <jobCount; i++) {
        printf("  %d. %s", i+1, jobs[i].name);
    }
}

void navigate() {
    currentMenu = menus[currentMenu.navToMenuIndex[userInputI]];
    (*currentMenu.handlers)();
    menuStaticCount = 0;
}

void navigateTo(int i) {
    currentMenu = menus[i];
    (*currentMenu.handlers)();
    menuStaticCount = 0;
}

typedef enum {
    STRING,
    INTEGER,
}DataType;


void handleMultipleInput(const DataType dts[], int (*ranges)[2], void **varsPointer) {
    for (int i = 0; i<currentMenu.optionsCount; i++) {
        DataType dt = dts[i];
        switch (dt) {
            case STRING:
                handleInputStringRange(ranges[i], currentMenu.statics[i]);
                *(char **)varsPointer[i] = userInputS;
                break;
            case INTEGER:
                handleInputIntRange(ranges[i], currentMenu.statics[i]);
                *(int *)varsPointer[i] = userInputI;
                break;
        }
    }
}

void printStates() {
    for (int i = 0; i<3; i++) {
        printf("%s", statuses[i]);
    }
}

void removeJob(char *jobName) {
    Job *job = findJob(jobName);
    for (int i = 0; i<jobCount; i++) {
        if (&jobs[i] == job) {
            if (i == jobCount-1) {
                jobCount--;
                break;
            }
            for (int j = i+1; j<jobCount; j++) {
                jobs[j-1] = jobs[j];
            }
            jobCount--;
            break;
        }
    }
}

char *deadlineToString(Deadline deadline) {
    char *months [12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "Decenber"};
    char dateString[100];
    snprintf(dateString, sizeof(dateString), "%d %s %d", deadline.date, months[deadline.month-1], deadline.year);
    return dateString;
}

void printJob(Job job) {
    printf("\nDeadline: %s\nTask: %s\nStatus: %s\n", deadlineToString(job.deadline), job.name, statuses[job.status-1]);
}

void handleMainMenu(void) {
    printStatics();
    handleInputIntRange((int[]){1, 5}, "Choose ->");
    navigate();
}


void handleAddJob(void) {
    int arr[][2] = {
        {3, 100},
        {1, 2},
        {1, 31},
        {1, 12},
        {2000, 2100}
    };
    Job job = (Job){
    .name = "",
    .status = ONGOING,
    .deadline = (Deadline){
    .date = -1,
    .month = -1,
    .year = -1,}};


    void **pointers = calloc(3, sizeof(void*));
    void *pos = &job.name;
    pointers[1] = pos;
    pos = &job.status;
    pointers[2] = pos;
    pos = &job.deadline;
    pointers[3] = pos;

    handleMultipleInput(
        (DataType[]){STRING, INTEGER, INTEGER, INTEGER, INTEGER},
        arr,
        pointers)
    ;
    jobs[jobCount] = job;
    printf("JOB SUCCESSFULLY RECORDED!");
    navigateTo(mainMenuId);
}


void navToMainMenu(void) {
    return navigateTo(mainMenuId);
}

void handleUpdateJob(void) {
    printJobs();
    curJob =  *(Job *)handleInputStringFind(currentMenu.statics[0], currentMenu.statics[1], findJobWrapper, false, NULL);
    printStates();
    handleInputIntRange((int[]) {1, 3}, currentMenu.statics[2]);
    if (statusArr[userInputI - 1] == DONE) {
        removeJob(curJob.name);
        printf("Job Removed!");
        navToMainMenu();
        return;
    }
    curJob.status = statusArr[userInputI - 1];
    printf("Job Status Updated to %s", statuses[userInputI - 1]);
    navigateTo(mainMenuId);
}

char *getStatic(void) {
    return currentMenu.statics[menuStaticCount++];
}

void printStatic(void) {
    printf("%s", getStatic());
}

char *getStaticAtIndex(int staticId) {
    return currentMenu.statics[staticId];
}

void handleSearchJob(void) {
    printStatic();
    handleInputStringFind(getStatic(), "Job Not Found!", findJobWrapper, true, navToMainMenu);
}


int main(int argc, char *argv[]) {
    menus = calloc(6, sizeof(Menu));
    jobs = calloc(100, sizeof(Job));

    char *mainMenuOptions[] = {"Add Job", "Update Status", "Search Job Name", "View All Jobs", "Exit"};
    constructMenu(5, mainMenuOptions, handleMainMenu);

    char *createJobStatics[] = {
        "Job Name (3-100 characters) = ",
        "Select Status: \n1. ONGOING\n2. PENDING\nChoose =>",
        "Deadline date (1-31) = ", "Deadline month (1-12)", "Deadline year (2000-2100)",
        "JOB SUCCESS RECORDED"
    };

    constructMenu(5, createJobStatics, handleAddJob);

    char *updateStatus[] = {
        "Which Job do you want to update the status of?\n-> ",
        "Job not found! Try again\n",
        "CHOOSE=>\n",
    };
    constructMenu(2, updateStatus, handleUpdateJob);

    char *searchJobMenuStatics[] = {
        "Which job do you Want to Find?\n"
        "=>",
        "Job not Found!"
        "Press 'Q' to return to main menu. .",
    };
    constructMenu(1, searchJobMenuStatics, handleSearchJob);
}

//push mid, sorted list, insert on the correct spot, ascending
