#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8

void sdes_encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *ciphertext) {
    memcpy(ciphertext, plaintext, BLOCK_SIZE);
}

void sdes_decrypt(unsigned char *ciphertext, unsigned char *key, unsigned char *plaintext) {
    memcpy(plaintext, ciphertext, BLOCK_SIZE);
}

void xor_strings(unsigned char *result, unsigned char *a, unsigned char *b) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = a[i] ^ b[i];
    }
}

int main() {
    unsigned char iv[BLOCK_SIZE] = {1, 0, 1, 0, 1, 0, 1, 0};
    unsigned char key[BLOCK_SIZE] = {0, 1, 1, 1, 1, 1, 1, 1};
    unsigned char plaintext[BLOCK_SIZE] = {0, 0, 0, 0, 0, 0, 1, 0};
    unsigned char ciphertext[BLOCK_SIZE];
    unsigned char decrypted[BLOCK_SIZE];
    unsigned char xor_result[BLOCK_SIZE];

    xor_strings(xor_result, iv, plaintext);
    sdes_encrypt(xor_result, key, ciphertext);

    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%d", ciphertext[i]);
    }
    printf("\n");

    sdes_decrypt(ciphertext, key, decrypted);
    xor_strings(decrypted, decrypted, iv);

    printf("Decrypted Plaintext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%d", decrypted[i]);
    }
    printf("\n");

    return 0;
}

