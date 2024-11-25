#include <stdio.h>

void extendedGCD(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return;
    }
    int x1, y1;
    extendedGCD(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
}

int modInverse(int a, int m) {
    int x, y;
    extendedGCD(a, m, &x, &y);
    return (x % m + m) % m;
}

int main() {
    int e = 31;
    int f_n = 3480;
    int d = modInverse(e, f_n);

    printf("The private key d is: %d\n", d);
    return 0;
}

