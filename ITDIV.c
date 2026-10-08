#include <stdio.h>
//
// Created by cleme on 03/09/2026.
//

void fibonacci(int loop, int a, int b, int* f) {
    int sum=0;
    for (int i = 0; i<loop; i++) {
        sum  = a+b;
        b= a;
        a=sum;
        printf("%d\n", sum);
    }
    *f = sum;

}
int main(int argc, char *argv[]) {
    int fibo = 0;
    fibonacci(5, 1, 1, &fibo);

    int x = 1;
    int y = 2;
    int z = 3;
    int o = x++ * --y ^z/6+4; //pow(--y, z/6+4);
    printf("%d\n", o);
    int price[5], discount[5];

    int realPrice[5] = {200000, 180000, 125000, 80000, 40000};



    for(int i=0; i<5 ; i++){

        if (realPrice[i] >= 200000)

            discount[i] = 0.25 * realPrice[i];

        else if (realPrice[i] < 200000 && realPrice[i] >=100000)

            discount[i] = 0.20 * realPrice[i];

        else if (realPrice[i] < 100000 && realPrice[i] >=50000)

            discount[i] = 0.1 * realPrice[i];

        else if (realPrice[i] < 50000 && realPrice[i] >= 10000)

            discount[i]  = 0.05 * realPrice[i];

        else

            discount[i]  = 0;



        price[i] = realPrice[i] - discount[i];

        printf("%d\n", price[i]);
    }




    int i =0;
    for(int j=0; j<10 ; j++){

        for(int k=10; k>0 ; k--){

            if(j%2==0 && k%2==0){

                i++;

            }

        }

    }
    printf("%d\n", i);
}

