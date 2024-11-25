#include <stdio.h>
#include <stdint.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    long long p = 23;  
    long long q = 5;   

    long long alice_secret = 6;
    long long bob_secret = 15;

    long long alice_public = mod_exp(q, alice_secret, p);
    long long bob_public = mod_exp(q, bob_secret, p);

    long long alice_shared_key = mod_exp(bob_public, alice_secret, p);
    long long bob_shared_key = mod_exp(alice_public, bob_secret, p);

    printf("Alice's public value: %lld\n", alice_public);
    printf("Bob's public value: %lld\n", bob_public);
    printf("Alice's shared key: %lld\n", alice_shared_key);
    printf("Bob's shared key: %lld\n", bob_shared_key);

    return 0;
}

