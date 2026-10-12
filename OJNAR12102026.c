//
// Created by clementzhao on 12/10/2026.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



/*
* 1. Check Base Cases:
    • If \(n \le 1\), it is not prime.
    • If \(n \le 3\), it is prime (2 and 3).
    • If \(n\) is divisible by 2 or 3, it is not prime.
2. Set up the Loop: Start a variable i at 5.
3. Test Factors: Check if n is divisible by i or i + 2 (this tests 5 and 7, then 11 and 13, then 17 and 19, etc.).
4. Increment: Increase i by 6 in each turn of the loop.
5. Stop Condition: Stop the loop as soon as i * i > n (which is the same as \(i > \sqrt{n}\)).
6. Result: If no factors divide \(n\) perfectly, the number is prime.
 */
bool isPrime(int n) {
    //using the 6k +- 1 method
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    int i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i+2) == 0) {
            return false;

        }
        i+=6;
    }
    return true;
}


void primePairSum() {
    int n;
    scanf("%d", &n);
    bool empty = true;
    for (int i = 2; i <= n/2; i++) {
        bool pp = isPrime(i);
        if (!pp) continue;
        bool pq = isPrime(n-i);
        if (!pq) continue;

        empty = false;
        printf("%d %d\n", i, n-i);
    }
    if (empty) printf("Tidak ada pasangan prima.\n");
}

void permissionManagement() {
    int i, g, r, q;
    scanf("%d\n%d\n%d\n%d", &i, &g, &r, &q);
    i |= g;
    i &= ~r;
    bool same = (i & q) == q;
    printf("%d\n", i);
    if (same) {
        printf("Granted\n");
        return;
    }
    printf("Not Granted\n");

}

void howManyStudents() {
    int min, max;
    scanf("%d %d", &min, &max);
    int mi = max+1, ma = min-1;
    int count = 0;
    for (int i = min; i <= max; i++) {
        if (i % 8 == 3 && i % 6 == 5 && i%5 == i%8 && i%7 ==0) {
            count++;
            if (i <= mi) {
                mi = i;
            }
            if (i >= ma) {
                ma = i;
            }
        }
    }
    if (count == 0) {
        printf("Tidak ada solusi\n");
        return;
    }
    printf("Jumlah solusi : %d\nNilai terkecil: %d\nNilai terbesar: %d\n", count, mi, ma);
}


int sumDigits(int nums[], int count) {
    int sum = 0;
    for (int i = 0; i <count; i++) {
        sum+=nums[i];
    }
    return sum;
}

int reduceToSingleDigit(int n) {
    int div = n;
    int digits[10];
    int j = 0;
    int sum = 10;
    while (sum > 9) {
        j = 0;
        while (div != 0) {
            digits[j++] = div % 10;
            div /= 10;
        }
        sum = sumDigits(digits, j);
        div = sum;
        // printf("%d, ", sum);
    }
    // printf("\n");
    return sum;
}


void batteryEnergyCalibration() {
    int n;
    scanf("%d", &n);
    int sumBattery = 0;
    for (int i = 0; i < n; i++) {
        int e;
        scanf("%d", &e);
        sumBattery += reduceToSingleDigit(e);
    }
    if (sumBattery > 9) {
        sumBattery = reduceToSingleDigit(sumBattery);
    }

    printf("%d\n", sumBattery);
}

void sumOfMultiplesOf3() {
    int n;
    scanf("%d", &n);
    if (n <= 3) {
        printf("Tidak ada kelipatan 3\n");
        return;
    }
    int sum = 0;
    for (int i = 3; i<n; i+=3) {
        sum += i;
        printf("%d%s", i, i>= n-3 ? " = " : " + ");
    }
    printf("%d\n", sum);
}


int main() {
    // primePairSum();
    permissionManagement();
    // howManyStudents();
    // batteryEnergyCalibration();
    // sumOfMultiplesOf3();
}


