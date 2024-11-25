#include <stdio.h>
#include <math.h>
double log2_factorial(int n) {
    if (n <= 1) return 0.0;
    double pi = 3.141592653589793;
    return 0.5 * log2(2 * pi * n) + n * log2(n / M_E);
}
int main() {
    int n = 26;
    double log2_total_keys = log2_factorial(n); 
    printf("Total possible keys for Playfair cipher: ~2^%.2f\n", log2_total_keys);
    double log2_effective_keys = log2_total_keys - 8.0;
    printf("Effectively unique keys for Playfair cipher: ~2^%.2f\n", log2_effective_keys);
    return 0;
}

