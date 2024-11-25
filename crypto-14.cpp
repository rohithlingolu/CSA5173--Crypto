#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(const char *plaintext, const int key[], int keyLength, char *ciphertext) {
    int i, shift;
    int n = strlen(plaintext);
    for (i = 0; i < n; i++) {
        if (isalpha(plaintext[i])) {
            shift = key[i % keyLength] % 26;
            if (islower(plaintext[i])) {
                ciphertext[i] = ((plaintext[i] - 'a' + shift) % 26) + 'a';
            } else {
                ciphertext[i] = ((plaintext[i] - 'A' + shift) % 26) + 'A';
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[n] = '\0';
}
void decrypt(const char *ciphertext, const int key[], int keyLength, char *plaintext) {
    int i, shift;
    int n = strlen(ciphertext);
    for (i = 0; i < n; i++) {
        if (isalpha(ciphertext[i])) {
            shift = key[i % keyLength] % 26;
            if (islower(ciphertext[i])) {
                plaintext[i] = ((ciphertext[i] - 'a' - shift + 26) % 26) + 'a';
            } else {
                plaintext[i] = ((ciphertext[i] - 'A' - shift + 26) % 26) + 'A';
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[n] = '\0';
}
void findKey(const char *ciphertext, const char *targetPlaintext, int key[], int keyLength) {
    int i, shift;
    int n = strlen(ciphertext);
    for (i = 0; i < n; i++) {
        if (isalpha(ciphertext[i]) && isalpha(targetPlaintext[i])) {
            if (islower(ciphertext[i])) {
                shift = (ciphertext[i] - 'a') - (targetPlaintext[i] - 'a');
            } else {
                shift = (ciphertext[i] - 'A') - (targetPlaintext[i] - 'A');
            }
            if (shift < 0) shift += 26;
            key[i % keyLength] = shift % 26;
        }
    }
}
int main() {
    const char plaintext[] = "send more money";
    const int keyStream[] = {9, 0, 1, 7, 2, 3, 15, 21, 14, 11, 11, 28, 9};
    int keyLength = sizeof(keyStream) / sizeof(keyStream[0]);
    char ciphertext[100], decrypted[100];
    const char targetPlaintext[] = "cash not needed";
    int foundKey[100] = {0};
    encrypt(plaintext, keyStream, keyLength, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    findKey(ciphertext, targetPlaintext, foundKey, keyLength);
    decrypt(ciphertext, foundKey, keyLength, decrypted);
    printf("Decrypted Text with Found Key: %s\n", decrypted);
    printf("Found Key: ");
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            printf("%d ", foundKey[i % keyLength]);
        }
    }
    printf("\n");
    return 0;
}
