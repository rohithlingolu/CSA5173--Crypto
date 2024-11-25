#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8

void xor_strings(uint8_t *result, uint8_t *a, uint8_t *b) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        result[i] = a[i] ^ b[i];
    }
}

void sdes_encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext) {
    memcpy(ciphertext, plaintext, BLOCK_SIZE);
}

void cbc_mac(uint8_t *message, size_t length, uint8_t *key, uint8_t *mac) {
    uint8_t iv[BLOCK_SIZE] = {0};
    uint8_t block[BLOCK_SIZE];
    uint8_t xor_result[BLOCK_SIZE];

    memcpy(mac, iv, BLOCK_SIZE);

    for (size_t i = 0; i < length; i++) {
        memcpy(block, message + i * BLOCK_SIZE, BLOCK_SIZE);
        xor_strings(xor_result, mac, block);
        sdes_encrypt(xor_result, key, mac);
    }
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0b011111101};
    uint8_t message[BLOCK_SIZE] = {0b00000001, 0b00000010, 0b00000000};
    size_t length = sizeof(message) / BLOCK_SIZE;
    uint8_t mac[BLOCK_SIZE];

    cbc_mac(message, length, key, mac);

    printf("CBC MAC: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%d", mac[i]);
    }
    printf("\n");

    return 0;
}

