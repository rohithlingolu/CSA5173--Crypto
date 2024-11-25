#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}
char decryptChar(char c, int a_inv, int b) {
    if (c >= 'A' && c <= 'Z') { 
        int decrypted = (a_inv * ((c - 'A') - b + 26)) % 26;
        return decrypted + 'A';
    }
    return c; 
}
int main() {
    // Ciphertext
    char ciphertext[] = "BUBUBU";
    int c1 = 'B' - 'A'; 
    int c2 = 'U' - 'A'; 
    int p1 = 'E' - 'A'; 
    int p2 = 'T' - 'A'; 
    int a, b;
    for (a = 1; a < 26; a++) {
        if (gcd(a, 26) == 1) { 
            b = (c1 - p1 * a + 26) % 26;
            if ((p2 * a + b) % 26 == c2) { 
                break;
            }
        }
    }
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("No modular inverse found for a=%d\n", a);
        return 1;
    }
    printf("Decrypted text: ");
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        printf("%c", decryptChar(ciphertext[i], a_inv, b));
    }
    printf("\n");
    return 0;
}
