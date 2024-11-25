#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define BLOCK_SIZE 8
void encryptBlock(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i];
    }
}
void decryptBlock(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i];
    }
}
void ECB_Encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        encryptBlock(plaintext + i, key, ciphertext + i);
    }
}
void ECB_Decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext, int length) {
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        decryptBlock(ciphertext + i, key, plaintext + i);
    }
}
void CBC_Encrypt(uint8_t *plaintext, uint8_t *key, uint8_t *ciphertext, uint8_t *iv, int length) {
    uint8_t temp[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            temp[j] ^= plaintext[i + j];
        }
        encryptBlock(temp, key, ciphertext + i);
        memcpy(temp, ciphertext + i, BLOCK_SIZE);
    }
}
void CBC_Decrypt(uint8_t *ciphertext, uint8_t *key, uint8_t *plaintext, uint8_t *iv, int length) {
    uint8_t temp[BLOCK_SIZE], prevCipher[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);
    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(prevCipher, ciphertext + i, BLOCK_SIZE);
        decryptBlock(ciphertext + i, key, plaintext + i);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] ^= temp[j];
        }
        memcpy(temp, prevCipher, BLOCK_SIZE);
    }
}
int main() {
    uint8_t plaintext[] = "This is a test of error propagation.";
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t ciphertext[64], decrypted[64];
    printf("Original plaintext: %s\n", plaintext);
    ECB_Encrypt(plaintext, key, ciphertext, strlen((char *)plaintext));
    printf("ECB Encrypted: %s\n", ciphertext);
    ECB_Decrypt(ciphertext, key, decrypted, strlen((char *)plaintext));
    printf("ECB Decrypted: %s\n", decrypted);
    CBC_Encrypt(plaintext, key, ciphertext, iv, strlen((char *)plaintext));
    printf("CBC Encrypted: %s\n", ciphertext);
    CBC_Decrypt(ciphertext, key, decrypted, iv, strlen((char *)plaintext));
    printf("CBC Decrypted: %s\n", decrypted);
    return 0;
}
