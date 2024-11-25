#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long gcd(long long a, long long b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long p = 61;
    long long q = 53;
    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);
    long long e = 17;

    if (gcd(e, phi_n) != 1) {
        printf("e must be coprime to f(n)\n");
        return 1;
    }

    long long m;
    printf("Enter plaintext block (numeric): ");
    scanf("%lld", &m);

    long long ciphertext = mod_exp(m, e, n);

    printf("Ciphertext: %lld\n", ciphertext);

    return 0;
}

