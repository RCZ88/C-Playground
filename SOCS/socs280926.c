//
// Created by clementzhao on 28/09/2026.
//

// A.

#include <stdbool.h>
#include <stdio.h>


int gcd(int a, int b) {
    int larger = a > b ? a : b;
    int smaller = a > b ? b : a;

    if (smaller == 0) return larger;

    int remainder = larger % smaller;
    while (remainder != 0) {
        larger = smaller;
        smaller = remainder;
        remainder = larger % smaller;
    }
    return smaller;
}
int main(int argc, char *argv[]) {
    //a
    /*char letters[3];

    scanf("%c %c %c", &letters[0], &letters[1], &letters[2]);

    int outIndex[3] = {1,2,3};
    for (int i = 0; i<2; i++) {
        for (int j = i+1; j<3; j++) {
            if (letters[j] < letters[i]) {
                // printf("SWAP %c WITH %c\n", letters[i], letters[j]);
                char temp = letters[i];
                letters[i] = letters[j];
                letters[j] = temp;
                // printf("%c %c %c\n", letters[0], letters[1], letters[2]);

                int tempIndex = outIndex[i];
                outIndex[i] = outIndex[j];
                outIndex[j] = tempIndex;
            }
        }
    }
    // printf("%c %c %c\n", letters[0], letters[1], letters[2]);
    printf("%d %d %d\n", outIndex[0], outIndex[1], outIndex[2]);*/

    //b
    /*int t;
    scanf("%d", &t);
    unsigned int n[t];
    unsigned int x[t];

    unsigned int y[t];
    for (int i = 0 ;i < t; i++) {
        scanf("%d %d", &n[i], &x[i]);
        if (x[i] == 1) {
            // printf("COND 0\n");
            y[i] = 0;
            continue;
        }
        bool condition = n[i] % 2 == 0 ? x[i] == n[i] : x[i] == n[i] || x[i] == n[i]-1 ;
        if (condition) {
            // printf("COND 1\n");
            y[i] = 0;
            continue;
        }

        unsigned int dived = x[i]/2;
        unsigned int max = n[i]/2;
        unsigned int fromRight = max - dived;

        if (dived < fromRight && fromRight > 0) {
            y[i] = dived;
            continue;
        }
        y[i] = fromRight;
    }

    for (int i = 0; i<t; i++) {
        printf("Case #%d: %d\n", i+1, y[i]);
    }
    */

    //c
    /*int t;
    scanf("%d", &t);
    int n[t];

    for (int i = 0; i < t; i++) {
        scanf("%d", &n[i]);
    }

    for (int i = 0; i < t; i++) {
        if (n[i] == 1) {
            printf("*\n\n");
            continue;
        }
        int size = n[i];
        char x[size][size];

        for (int j = 0; j < size; j++) {
            for (int k = 0; k < size; k++) {
                x[j][k] = ' ';
            }
        }

        int vIndex = 0;
        for (int j = 0; j < n[i]; j++) {
            x[0][j] = '*';
            x[vIndex][0] = '*';

            x[n[i] - 1][j] = '*';
            x[vIndex][n[i] - 1] = '*';

            vIndex++;
        }

        int leftIndex = 1;
        int rightIndex = n[i] - 2;

        int yIndex = 1;

        for (int j = 0; j < n[i] - 2; j++) {
            x[yIndex][leftIndex] = '*';
            leftIndex++;

            x[yIndex][rightIndex] = '*';
            rightIndex--;

            yIndex++;
        }

        for (int j = 0; j < n[i]; j++) {
            for (int k = 0; k < n[i]; k++) {
                printf("%c", x[j][k]);
            }
            printf("\n");
        }
        printf("\n");   // fix: blank line after each test case
    }
    */

    //d

    /*int t;
    scanf("%d", &t);
    float cb[t];
    for (int i = 0; i < t; i++) {
        float A, B, C;
        scanf("%f %f %f", &A, &B, &C);

        float cashback = B/100.f * A;
        if (cashback > C) {
            cb[i] = C;
            continue;
        }
        cb[i] = cashback;
    }
    for (int i =0; i < t; i++) {
        printf("Case #%d: %.0f\n", i+1, cb[i]);
    }*/

    //e
    /*int t;
    scanf("%d", &t);

    int ashiap[] = {'a', 's', 'h', 'i', 'a', 'p'};
    int rep[t][6];
    for (int i = 0; i < t; i++) {
        scanf("%d %d %d %d %d %d", &rep[i][0], &rep[i][1], &rep[i][2], &rep[i][3], &rep[i][4], &rep[i][5]);
    }

    for (int i  =0 ; i<t; i++) {
        printf("Case #%d: ", i+1);
        for (int j = 0; j<6; j++) {
            for (int k = 0; k<rep[i][j]; k++) {
                printf("%c", ashiap[j]);
            }
        }
        printf("\n");
    }*/

    //f
    /*int t;
    scanf("%d", &t);
    int sizes[t];
    for (int i = 0; i < t; i++) {
        scanf("%d", &sizes[i]);
    }
    for (int i = 0; i < t; i++) {
        int size = sizes[i];
        int len = 2 * size -1;
        for (int j = 0; j<size; j++) {
            int space = size-j-1;
            int fill = len-space*2;
            for (int k = 0; k<space; k++) {
                printf(" ");
            }
            for (int k =0 ; k<fill; k++) {
                printf("*");
            }
            printf("\n");
        }
    }*/


    //g
    int x, y, k;
    scanf("%d %d %d", &x, &y, &k);
    if (k<x) {
        printf("-1\n");
        return 0;
    }
    if (k>y) {
        printf("-1\n");
        return 0;
    }
    if (k - x != y - k) {
        printf("-1\n");
        return 0;
    }
    printf("%d\n", k-x);

    //h
    /*int t;
    scanf("%d", &t);
    int a[t];
    int b[t];

    for (int i = 0; i<t; i++) {
        scanf("%d %d", &a[i], &b[i]);
    }


    for (int i = 0; i<t; i++) {
        int remainder = a[i];
        int count = 0;
        while (remainder != 0) {
            if (remainder < b[i]) {
                count += remainder;
                break;
            }
            remainder = remainder - b[i] + 1;
            count += b[i];
        }
        printf("Case #%d: %d\n", i+1, count);
    }*/

    //i
    /*int t;
    scanf("%d", &t);
    int gcds [t];
    for (int i = 0 ; i<t ; i++) {
        int n;
        scanf("%d", &n);
        int nums[n];
        for (int j = 0 ; j<n ; j++) {
            scanf("%d", &nums[j]);
        }
        int gcdRes = nums[0];
        for (int j = 0; j<n-1 ; j++) {
            gcdRes = gcd(gcdRes, nums[j+1]);

        }
        gcds[i] = gcdRes;


    }
    for (int i = 0; i<t; i++) {
        printf("Case #%d: %d\n", i+1, gcds[i]);
    }*/
}
