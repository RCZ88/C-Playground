#include <math.h>
#include <stdio.h>
//
// Created by clementzhao on 21/09/2026.
//


float conv_temp(float celcius, float *reamur, float *fah) {
    *reamur = 4.f/5.f * celcius;
    *fah = 9.f/5.f *celcius + 32;
}

float calc_bmi(float weight, float height) {
    return weight/ (height * height);
}


char *getCategory(float bmi) {
    if (bmi >= 30) {
        return "Obese";
    }
    if (bmi >= 25 && bmi <= 29.9) {
        return "Overweight";
    }
    if (bmi >= 18.5 && bmi <= 24.9) {
        return "Normal";
    }
    return "Underweight";
}
int main() {
    // a
     // int a, b;
     // scanf("%d %d", &a, &b);
     // printf("%d\n", a+b);
     // printf("%d\n", a-b);
     // printf("%d\n", a*b);
     // printf("%d\n", a/b);
     // printf("%d\n", a%b);


    // B
    // float c, d;
    // scanf("%d %d", &c, &d);
    // float percentage = d/c * 100;
    // printf("%.4f%%\n", percentage);

    // C
    // long double x;
    // long double y;
    //
    // scanf("%Lf %Lf", &x, &y);
    //
    // const int monthCount = 3;
    // long double current = x;
    // for (int i =0; i<3; i++) {
    //     current *= (100+ y)/100;
    // }
    // printf("%.2Lf\n", current);


    // D
    // int Pd, M, Pu;
    //
    //
    // scanf("%d %d %d", &Pd, &M, &Pu);
    // float damage = 0.2 * Pd + 0.3 * M + 0.5 * Pu;
    // printf("%.2f\n", damage);

    // E

    // long games;
    // scanf("%ld", &games);
    //
    // long out = pow(2, games) -1;
    // printf("%ld\n", out);


    //F
    // int buttonClicked;
    // scanf("%d", &buttonClicked);
    // int bonus = 0;
    // const int increment = 50;
    // const int reward = 100;
    // long total = 0;
    // for (int i = 0; i<buttonClicked; i++) {
    //     total += reward + bonus;
    //     bonus += increment;
    // }
    // printf("%ld\n", total);

    // G
    // long f [3];
    // long g [3];
    // for (int i = 0; i < 3; i++) {
    //     scanf("%ld + %ld =", &f[i], &g[i]);
    // }
    // for (int i = 0; i < 3; i++) {
    //     printf("%ld\n", f[i]+g[i]);
    // }

    // h
     // long initial, current;
     // scanf("%ld%*c%ld%*c", &initial, &current);
     //
     // float percentage = (float)(initial - current) / (float) initial * 100.0f;
     //
     // printf("%.2f%%\n", percentage);


    //i
    // int div [4][4] = {
    //     {1, 2, 3 ,4},
    //     {2 ,3, 4, 3},
    //     {3, 4, 3, 2},
    //     {4, 3, 2, 1}
    // };
    //
    // int inputs [3][4];
    // for (int i = 0; i<3; i++) {
    //     scanf("%d %d %d %d" , &inputs[i][0], &inputs[i][1], &inputs[i][2], &inputs[i][3]);
    // }
    //
    //
    // for (int k = 0; k<3; k++) {
    //     double outputTotal = 0;
    //     for (int i = 0; i < 4; i++) {
    //         for (int j = 0; j < 4; j++) {
    //             for (int l = 0; l < 4; l++) {
    //                 if (div[i][j] == l) {
    //                     outputTotal += inputs[k][l] / div[i][j];
    //                 }
    //             }
    //         }
    //     }
    //     printf("%lf\n", outputTotal);
    // }

    // int inputs [3][4];
    // for (int i = 0; i<3; i++) {
    //     scanf("%d %d %d %d" , &inputs[i][0], &inputs[i][1], &inputs[i][2], &inputs[i][3]);
    // }
    //
    // const int multi [4] = {2, 2, 2, 1};
    // for (int i = 0; i<3; i++) {
    //     float total = 0;
    //     for (int j = 0; j<4; j++) {
    //         total += inputs[i][j] * multi [j];
    //     }
    //     printf("%.2f\n", total);
    // }
    //
    //
    //
    // // int inputs [3][4];
    // for (int i = 0; i<3; i++) {
    //     scanf("%d %d %d %d" , &inputs[i][0], &inputs[i][1], &inputs[i][2], &inputs[i][3]);
    // }
    //
    // const int multi [4] = {2, 2, 2, 1};
    // for (int i = 0; i<3; i++) {
    //     float total = 0;
    //     for (int j = 0; j<4; j++) {
    //         total += inputs[i][j] * multi [j];
    //     }
    //     printf("%.2f\n", total);
    // }
    //
    //

    float inputHeight, inputWeight;
    printf("Input Height (meter): ");
    scanf("%f", &inputHeight);
    printf("Input Weight (kg): ");
    scanf("%f", &inputWeight);
    float bmi = calc_bmi(inputHeight, inputWeight);
    printf("\nYour BMI: %f", bmi);
    char* category = getCategory(bmi);
    printf("\nYOU ARE FUCKING: %s\n", category);


    float inputTemp;
    printf("Input Temp in Celcius: ");
    scanf("%f", &inputTemp);
    float reamur;
    float fah;
    conv_temp(inputTemp, &reamur, &fah);
    printf("%f Celsius in:\n- Reamer: %f\n- Fahrenheit: %f\n", inputTemp, reamur, fah);


    return 0;
}


