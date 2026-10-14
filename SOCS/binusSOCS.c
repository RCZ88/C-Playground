//
// Created by cleme on 24/08/2026.
//
#include <stdio.h>

int main () {
    //A
    //printf("Hello world!\n");

    //B
    /*int a;
    int b;
    scanf("%d %d",&a,&b);
    printf("%d\n", a+b);*/

    //C
    /*char name[100];
    scanf("%s", name);
    printf("Hello %s!\n", name);*/

    //D
    // int num;
    // scanf("%d", &num);
    // if (num % 2 == 0) {
    //     printf("EVEN\n");
    // }else {
    //     printf("ODD\n");
    // }

    //E
    /*int count;
    int end;
    scanf("%d %d", &count, &end);
    for (int i = count; i < count+end; i++) {
        printf("%d\n", i);
    }*/

    //DAMAGE
    int Pd, M, Pu;


    scanf("%d %d %d", &Pd, &M, &Pu);
    float damage = 0.2 * Pd + 0.3 * M + 0.5 * Pu;
    printf("%.2f\n", damage);
    return 0;
}