//
// Created by clementzhao on 05/10/2026.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverseStr(char*strs) {
    size_t len = strlen(strs);
    char *rev = calloc(len+1, sizeof(char));
    int k = 0;

    for (int j = len - 1; j >= 0; j--) {
        rev[k++] = strs[j]; // Clean array indexing
    }
    rev[k] = '\0';
    return rev;
}

int main(int argc, char *argv[]) {

    //a


    /*
    int n;
    scanf("%d", &n);
    char strs[n][10000];

    for (int i = 0; i < n; i++) {
        scanf("%s", strs[i]);
    }

    for (int i = 0; i < n; i++) {
        char seen[26] = {0};
        int unique = 0;
        size_t len = strlen(strs[i]);
        for (int j = 0; j < len; j++) {
            if (seen[strs[i][j] - 'a'] == strs[i][j]) {
                continue;
            }
            seen[strs[i][j] - 'a'] = strs[i][j];
            unique++;
        }
        if (unique % 2 == 0) {
            printf("Case #%d: Yay\n", i+1);
            continue;
        }
        printf("Case #%d: Ewwwww\n", i+1);
    }*/

    /*int n;
    scanf("%d", &n);
    char strs[n][100];
    for (int i = 0; i < n; i++) {
        scanf("%s", strs[i]);
    }
    for (int i = 0; i<n; i++) {
        char curChar = strs[i][0];
        char set[26];
        int count = 0;
        int charIndex = 0;
        while (curChar != '\0') {
            bool found = false;
            for (int j = 0; j<count ; j++) {
                if (set[j] == curChar) {
                    found = true;
                    curChar = strs[i][++charIndex];
                    break;
                }
            }
            if (found) continue;
            set[count++] = curChar;
            curChar = strs[i][++charIndex];
        }
        if (count % 2 == 0) {
            printf("Case #%d: Yay\n", i + 1);
            continue;
        }
        printf("Case #%d: Ewwwww\n", i + 1);

    }*/

    //b

    /*int n;
    scanf("%d", &n);
    char words[n][500];
    for (int i = 0; i < n; i++) {
        scanf("%s", words[i]);
    }

    for (int i = 0; i < n ; i++) {
        size_t count = strlen(words[i]);
        int ltrIndex = 0;
        bool done = false;
        for (int j = count-1; j >= 0; j--) {
            if (words[i][j] != words[i][ltrIndex++]) {
                printf("Case #%d: Nah, it's not a palindrome\n", i+1);
                done = true;
                break;
            }
        }
        if (done)continue;
        printf("Case #%d: Yay, it's a palindrome\n", i+1);
    }*/

    //c
    /*int n;
    scanf("%d", &n);

    char str[n][100];
    for (int i = 0; i < n; i++) {
        scanf("%s", str[i]);
    }
    int nearestCords[] = {'A', 'I', 'U', 'E', 'O'};


    for (int i = 0; i < n; i++) {
        char curChar = str[i][0];
        int curCharInt = (unsigned char)curChar;
        char message[100];
        int key[100];
        int count = 0;
        while (curChar != '\0') {
            if (curChar == '\0') break;
            curChar = str[i][count];
            curCharInt = (unsigned char)curChar;
            // printf("curCharInt: %d", curCharInt);
            int minDis = 26;
            char minChar = curChar;
            int dis = 0;
            int dis1 = 0;
            int dis2 = 0;
            for (int j = 0; j < 5; j++) {
                int curCord = nearestCords[j];
                int nextCurCord = nearestCords[j] + 26;

                // printf("nc: %d", curCord);

                dis1 = abs(curCharInt-curCord);
                dis2 = abs(curCharInt-nextCurCord);
                // printf("d1: %d", dis1);
                // printf("d2: %d\n", dis2);
                dis = dis1 < dis2 ? dis1 : dis2;
                if (dis < minDis) {
                    minDis = dis;
                    minChar = (char) nearestCords[j];
                }
            }
            // printf("'%c' -> SHORTEST: %d\n", curChar, minDis);

            key[count] = minDis;
            message[count] = minChar;
            count++;
        }
        printf("Case #%d:\n%s\n", i+1, message);
        for (int  j = 0;  j<count-1;  j++) {
            printf("%d", key[j]);
        }
        printf("\n");
    }*/

    //d - reverse string

    /*int n ;
    scanf("%d", &n);

    char strs[n][1000];
    for (int i = 0; i<n; i++) {
        scanf("%s", strs[i]);
    }

    for (int i = 0; i<n ;i++) {
        size_t len = strlen(strs[i]);
        char rev[len + 1];
        int k = 0;

        for (int j = len - 1; j >= 0; j--) {
            rev[k++] = strs[i][j]; // Clean array indexing
        }
        rev[k] = '\0';
        printf("Case #%d : %s\n", i+1, rev);
    }*/

    //e
    /*int n;
    scanf("%d", &n);
    char numberString [n][1001];
    int indexes[n][1001][2];
    int qs[n];
    for (int i =0; i < n; i++) {
        scanf("%d", &qs[i]);
        scanf("%s", numberString[i]);
        for (int j = 0; j < qs[i]; j++) {
            scanf("%d", &indexes[i][j][0]);
            scanf("%d", &indexes[i][j][1]);
        }
    }
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<qs[i]; j++) {
            int  start = indexes[i][j][0];
            int  end = indexes[i][j][1];
            int len = end-start+1;
            char temp[len+1];
            memcpy(temp, &numberString[i][start-1], len);
            temp[len] = '\0';
            int count = 0;
            for (int k = end-1; k>=start-1; k--) {
                numberString[i][k] = temp[count++];
            }
        }
        printf("Case #%d: %s\n", i+1, numberString[i]);

        /*char *ns = calloc(strlen(numberString[i])+1, sizeof(char));
        memcpy(ns, numberString[i], strlen(numberString[i]));

        for (int j = 0; j < qs[i]; j++) {
            int start = indexes[i][j][0]-1;
            int end = indexes[i][j][1]-1;
            int len = end-start+1;
            char *chunk = calloc(len+1, sizeof(char));
            memcpy(chunk, &ns[start], len);
            char *reversed = reverseStr(chunk);
            memcpy(&ns[start], reversed, len);
        }
        printf("Case #%d: %s\n", i+1, ns);#1#
    }*/

    //f
    /*int n;
    scanf("%d", &n);

    char strs[n][105];
    char swapMap[n][105][2];
    int ms[n];
    for (int i = 0; i<n; i++) {
        scanf("%s", strs[i]);
        scanf("%d", &ms[i]);
        for (int j = 0; j<ms[i]; j++) {
            scanf(" %c %c", &swapMap[i][j][0], &swapMap[i][j][1]);
        }
    }

    for (int i = 0 ;i <n; i++) {
        if (ms[i] == 0) {
            printf("Case #%d: %s\n", i+1, strs[i]);
            continue;
        }
        for (int j = 0; j<ms[i]; j++) {
            char toFind = swapMap[i][j][0];
            char replacement = swapMap[i][j][1];
            size_t len = strlen(strs[i]);
            for (int k = 0; k < len; k++) {
                if (strs[i][k] == toFind) {
                    strs[i][k] = replacement;
                }
            }
        }
        printf("Case #%d: %s\n", i+1, strs[i]);
    }*/

    //g
    /*
    int n;
    scanf("%d", &n);

    int lengths[n];
    char *strings[n];
    for (int i =0; i<n; i++) {
        scanf("%d", &lengths[i]);
        strings[i] = calloc(lengths[i] + 1, sizeof(char));
        scanf(" %[^\n]", strings[i]);
    }
    for (int i = 0; i<n; i++) {
        char *str = calloc(lengths[i]+1, sizeof(char));
        int strIndex = 0;
        for (int j = 0; j<lengths[i]; j++) {
            if ((int) strings[i][j] < (int)'a' || (int) strings[i][j] > (int) 'z') {
                continue;
            }
            str[strIndex++] = strings[i][j];
        }
        str[strIndex] = '\0';
        printf("Case #%d: %s\n", i+1, str);
    }
    */

    //h
    /*int t;
    scanf("%d", &t);
    int n[t];
    int k[t];
    char *strs[t];
    for (int i = 0; i < t; i++) {
        scanf("%d %d", &n[i], &k[i]);
        strs[i] = calloc(n[i]+1, sizeof(char));
        scanf("%s", strs[i]);
    }

    int base = 'a';
    char *encrypted[t];
    for (int i = 0; i < t; i++) {
        int len = n[i];

        encrypted[i] = calloc(len+1, sizeof(char));
        for (int j = 0; j < len; j++) {
            int num = strs[i][j] - base;
            num+= k[i];
            if (num > 25) {
                int multiplication = num/26;
                num -=  26 * multiplication;
            }
            char c = (char)(num + 'a');
            encrypted[i][j] = c;
        }
        encrypted[i][len] = '\0';
        printf("Case #%d: %s\n", i+1, encrypted[i]);
    }*/

    //problem I
    /*
    int n;
    scanf("%d", &n);
    char strs[n][10000];

    for (int i = 0; i < n; i++) {
        scanf("%s", strs[i]);
    }

    for (int i = 0; i < n; i++) {
        char seen[26] = {0};
        int unique = 0;
        size_t len = strlen(strs[i]);
        for (int j = 0; j < len; j++) {
            if (seen[strs[i][j] - 'a'] == strs[i][j]) {
                continue;
            }
            seen[strs[i][j] - 'a'] = strs[i][j];
            unique++;
        }
        if (unique % 2 == 0) {
            printf("Case #%d: Breakable\n", i+1);
            continue;
        }
        printf("Case #%d: Unbreakable\n", i+1);
    }
    */


    //problem A
    int T;
    scanf("%d", &T);
    int N[T];
    int A[T][200];
    for (int t = 0; t < T; t++) {
        scanf("%d", &N[t]);
        for (int i = 0; i < N[t]; i++) {
            scanf("%d", &A[t][i]);
        }
    }
    bool seen[200] = {false};
    for (int  t = 0; t < T; t++) {
        int count = 0;
        for (int i = 0; i < N[t]; i++) {
            int curTarget = A[t][i];
            // printf("cur target = %d", curTarget);
            if (seen[curTarget]) {
                // printf(", seen\n");
                continue;
            }
            seen[A[t][i]] = true;

            bool secSeen[200] = {false};
            bool found = false;
            for (int j = 0; j < N[t]; j++) {
                int curPointer1 = A[t][j];
                // printf("cur pt1 = %d\n", curPointer1);
                if (curPointer1 >= curTarget || secSeen[curPointer1]) {
                    continue;
                }
                secSeen[curPointer1] = true;
                for (int k = 0; k < N[t]; k++) {
                    int curPointer2 = A[t][k];
                    if (curPointer1 == curPointer2) {
                        continue;
                    }
                    // printf("cur pt2 = %d\n", curPointer2);
                    if (curPointer1 + curPointer2 == curTarget) {
                        // printf("found! (%d + %d = %d), count = %d\n", curPointer1, curPointer2, curTarget, count+1);
                        found = true;
                        break;
                    }
                }
                if (found) break;
            }
            if (found) count++;
        }
        printf("Case #%d: %d\n", t+1, count);
    }

    //b - WORKED
    /*int n;
    scanf("%d", &n);

    char numbers[n][2][8];
    for (int i = 0; i<n; i++) {
        scanf(" %s %s", numbers[i][0], numbers[i][1]);
    }
    for (int i = 0; i<n; i++) {
        size_t len1 = strlen(numbers[i][0]);
        size_t len2 = strlen(numbers[i][1]);
        size_t len = len2 > len1 ? len2 : len1;
        if (len2 > len1) {
            size_t diff = len2 - len1;

            memmove(numbers[i][0] + diff,
                    numbers[i][0],
                    len1 + 1);

            for (size_t j = 0; j < diff; j++) {
                numbers[i][0][j] = '0';
            }

            len1 = len2;
        }else if (len1 > len2) {
            size_t diff = len1 - len2;

            memmove(numbers[i][1]+diff,
                numbers[i][1],
                len2+1);
            for (size_t j = 0; j < diff; j++) {
                numbers[i][1][j] = '0';
            }
        }

        int numberString[len];
        printf("Case #%d: ", i+1);
        for (int j = 0; j<len; j++) {
            int first = numbers[i][0][j] - '0';
            int second = numbers[i][1][j] - '0';
            numberString[j] = first + second;
            if (numberString[j] > 9) {
                numberString[j] -=10;
            }
            if (numberString[j] == 0 && j != len-1) {
                continue;
            }
            printf("%d", numberString[j]);
        }
        printf("\n");
    }*/

    //b
    /*int n;
    scanf("%d", &n);

    char numbers[n][2][8];
    for (int i = 0; i<n; i++) {
        scanf(" %s %s", numbers[i][0], numbers[i][1]);
    }

    for (int i = 0; i<n; i++) {
        int l1 = strlen(numbers[i][0])-1;
        int l2 = strlen(numbers[i][1])-1;//for index
        int l = (l2 > l1 ? l2 : l1) + 1;
        int index = l-1;
        int nums[l];
        printf("Case #%d: ", i+1);
        for (int j = 0; j<l; j++) {
            int n1 = l1 >= 0 ? numbers[i][0][l1--] - '0' : 0;
            int n2 = l2 >= 0 ? numbers[i][1][l2--] - '0' : 0;

            nums[index--] = (n1 + n2) % 10;
        }
        bool started = false;
        for (int j = 0; j<l; j++) {
            if (nums[j] == 0 && j != l-1 && !started) {
                continue;
            }
            started = true;
            printf("%d", nums[j]);
        }
        printf("\n");
    }*/

    //PROBLEM C - Get Some Results
    /*int T;
    scanf("%d", &T);
    int N [T];
    long matrix[T][3][50][50];

    for (int i  = 0; i < T; i++) {
        scanf("%d", &N[i]);
        for (int l = 0; l<3; l++) {
            for (int j = 0; j < N[i]; j++) {
                for (int k =0; k <N[i]; k++) {
                    scanf("%ld", &matrix[i][l][j][k]);
                }
            }
        }
    }

    for (int i = 0; i < T; i++) {
        int size = N[i];
        long result[size][size];
        long multiplied[size][size];
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                multiplied[j][k] = matrix[i][0][j][k];
            }
        }
        for (int j = 1; j <3; j++) {
            long nextM[size][size];
            for (int k = 0; k < size; k++) {
                for (int l = 0; l < size; l++) {
                    nextM[k][l] = matrix[i][j][k][l];
                }
            }

            for (int k = 0; k < size; k++) {
                for (int l = 0; l < size; l++) {
                    long sum = 0;
                    for (int m = 0; m < size; m++) {
                        sum += multiplied[k][m] * nextM[m][l];
                    }
                    // printf("%d ", sum);
                    result[k][l] = sum;
                }
            }
            for (int k = 0; k < size; k++) {
                for (int l = 0; l < size; l++) {
                    multiplied[k][l] = result[k][l];
                }
            }
        }
        printf("Case #%d:\n", i+1);
        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                if (k != 0)printf(" ");
                printf("%ld", multiplied[j][k]);
            }
            printf("\n");
        }
    }*/

    //problem D - Array
    /*int N ;
    scanf("%d", &N);
    int arr[N];
    int orientation[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &orientation[i]);
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &arr[orientation[i]]);
    }


    for (int i = 0; i < N; i++) {
        printf("%d", arr[i]);
        if (i != N-1) printf(" ");
    }
    printf("\n");*/

    //problem E - Colsum
    /*int T;
    scanf("%d", &T);
    int N[T];

    for (int i = 0; i < T; i++) {
        int n = N[i];
        scanf("%d", &n);
        int box[n][n];
        int sum[n];
        for (int k = 0; k < n; k++) sum[k] = 0;
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                scanf("%d", &box[j][k]);
                sum[k] += box[j][k];
            }
        }
        printf("Case #%d: ", i + 1);
        for (int j = 0; j < n; j++) {
            if (j != 0) printf(" ");
            printf("%d", sum[j]);
        }
        printf("\n");
    }*/

    //G
    /*int n;
    scanf("%d", &n);
    int *teams = calloc(n*n, sizeof(int));
    for (int i = 0; i < n*n; i++) teams[i] = 0;
    int indexes[n*n];
    int count = 0;
    for (int i = 0; i<n; i++) {
        for (int j = 0; j<n; j++) {
            int t;
            scanf("%d", &t);
            if (teams[t] == 0 && t != 0) {
                indexes[count++] = t;
            }
            teams[t]++;

        }
    }
    int teamComplete = count;
    for (int i =0; i<count; i++) {
        if (teams[indexes[i]] != n) {
            teamComplete--;
        }
    }
    printf("%d\n", teamComplete);
    */

    //problem h - hotels
    /*int n;
    scanf("%d", &n);
    int sorted[n];
    for (int i = 0; i < n; i++) sorted[i] = 0;
    for (int i = 0; i < n; i++) {
        int input;
        scanf("%d", &input);
        int prevIndex = i-1;
        while (prevIndex >= 0 && sorted[prevIndex] > input) {
            sorted[prevIndex+1] = sorted[prevIndex];
            prevIndex--;
        }
        sorted[prevIndex+1] = input;
    }


    int unique = 0;
    int currentNum = sorted[0];
    unique++;
    for (int i = 1; i < n; i++) {
        // printf("%d ", sorted[i]);
        if (sorted[i] != currentNum) {
            unique++;
        }
        currentNum = sorted[i];
    }
    printf("%d\n", unique);*/

    /*int n;
    scanf("%d", &n);

    int matrix[n][n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j<n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    if (n == 1) {
        printf("Yay\n");
        return 0;
    }

    for (int i = 0; i<n; i++) {
        bool seen[n+1];
        for (int j =0; j<=n; j++) seen[j] = false;
        for (int j = 0; j<n; j++) {
            if (seen[matrix[i][j]]) {
                printf("Nay\n");
                return 0;
            }
            seen[matrix[i][j]] = true;
        }
    }
    for (int i = 0; i<n; i++) {
        bool seen[n+1];
        for (int j =0; j<=n; j++) seen[j] = false;
        for (int j = 0; j<n; j++) {
            if (seen[matrix[j][i]]) {
                printf("Nay\n");
                return 0;
            }
            seen[matrix[j][i]] = true;
        }
    }
    printf("Yay\n");*/

    /*
    for (int i = 0; i < n; i++) {
        for (int j = 0; j<n; j++) {
            bool unique = true;
            bool found [count];
            bool indexStepped[n][n];
            for (int k = 0; k < count; k++) found[k] = false;
            for (int k = 0; k < n; k++) {
                for (int l = 0; l < n; l++) {
                    indexStepped[k][l] = false;
                }
            }

            for (int k = 0; k<n; k++) {
                if (indexStepped[k][n]) continue;
                indexStepped[k][n] = true;
                if (found[matrix[i][k]]) {
                    unique = false;
                    break;
                }
                found[matrix[i][k]] = true;
                if (found[matrix[k][j]]) {
                    unique = false;
                    break;
                }
                found[matrix[k][j]] = true;
            }
            if (unique) {
                printf("Yay\n");
                return 0;
            }
        }
    }
    printf("Nay!\n");*/

}
