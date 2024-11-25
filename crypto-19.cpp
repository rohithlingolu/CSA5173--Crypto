#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define BLOCK_SIZE 8
void DES_Encrypt(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i];
    }
}
void DES_Decrypt(uint8_t *block, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i];
    }
}
void TripleDES_Encrypt(uint8_t *block, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *output) {
    uint8_t temp1[BLOCK_SIZE], temp2[BLOCK_SIZE];
    DES_Encrypt(block, key1, temp1);
    DES_Decrypt(temp1, key2, temp2);
    DES_Encrypt(temp2, key3, output);
}
void TripleDES_Decrypt(uint8_t *block, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *output) {
    uint8_t temp1[BLOCK_SIZE], temp2[BLOCK_SIZE];
    DES_Decrypt(block, key3, temp1);
    DES_Encrypt(temp1, key2, temp2);
    DES_Decrypt(temp2, key1, output);
}
void CBC_Encrypt(uint8_t *plaintext, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *ciphertext, uint8_t *iv, int length) {
    uint8_t temp[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            temp[j] ^= plaintext[i + j];
        }
        TripleDES_Encrypt(temp, key1, key2, key3, ciphertext + i);
        memcpy(temp, ciphertext + i, BLOCK_SIZE);
    }
}
void CBC_Decrypt(uint8_t *ciphertext, uint8_t *key1, uint8_t *key2, uint8_t *key3, uint8_t *plaintext, uint8_t *iv, int length) {
    uint8_t temp[BLOCK_SIZE], prevCipher[BLOCK_SIZE];
    memcpy(temp, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(prevCipher, ciphertext + i, BLOCK_SIZE);
        TripleDES_Decrypt(ciphertext + i, key1, key2, key3, plaintext + i);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            plaintext[i + j] ^= temp[j];
        }
        memcpy(temp, prevCipher, BLOCK_SIZE);
    }
}
int main() {
    uint8_t plaintext[] = "This is a test for CBC with 3DES.";
    uint8_t key1[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    uint8_t key2[BLOCK_SIZE] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18};
    uint8_t key3[BLOCK_SIZE] = {0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    uint8_t ciphertext[64], decrypted[64];
    printf("Original plaintext: %s\n", plaintext);
    CBC_Encrypt(plaintext, key1, key2, key3, ciphertext, iv, strlen((char *)plaintext));
    printf("CBC Encrypted: %s\n", ciphertext);
    CBC_Decrypt(ciphertext, key1, key2, key3, decrypted, iv, strlen((char *)plaintext));
    printf("CBC Decrypted: %s\n", decrypted);
    return 0;
}
