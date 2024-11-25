#include <stdio.h>
#include <string.h>
#include <ctype.h>
int modInverse(int a) {
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1) {
            return x;
        }
    }
    return -1; 
}
void encrypt(char plaintext[], char ciphertext[], int a, int b) {
    if (modInverse(a) == -1) {
        printf("Encryption not possible with a=%d. It is not coprime with 26.\n", a);
        return;
    }
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a'; 
            ciphertext[i] = (a * (plaintext[i] - base) + b) % 26 + base;
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}
void decrypt(char ciphertext[], char plaintext[], int a, int b) {
    int a_inv = modInverse(a); 
    if (a_inv == -1) {
        printf("Decryption not possible with a=%d. It is not coprime with 26.\n", a);
        return;
    }
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (a_inv * ((ciphertext[i] - base - b + 26) % 26)) % 26 + base;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
int main() {
    char plaintext[100], ciphertext[100], decrypted[100];
    int a, b;
    printf("Enter the value of a: ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
    getchar();
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    encrypt(plaintext, ciphertext, a, b);
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, decrypted, a, b);
    printf("Decrypted text: %s\n", decrypted);
    return 0;
}
