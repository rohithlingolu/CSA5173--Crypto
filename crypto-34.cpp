#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#define BLOCK_SIZE 8  
void encrypt_block(uint64_t *block, uint64_t key) {
    *block ^= key; 
}
void pad_message(char *message, int *message_len) {
    int len = *message_len;
    int pad_len = BLOCK_SIZE - (len % BLOCK_SIZE);
    for (int i = 0; i < pad_len; i++) {
        message[len + i] = pad_len;
    }
    *message_len = len + pad_len;
}
void ecb_encrypt(char *plaintext, int *length, uint64_t key, char *ciphertext) {
    int num_blocks = *length / BLOCK_SIZE;
    for (int i = 0; i < num_blocks; i++) {
        uint64_t block = 0;
        memcpy(&block, &plaintext[i * BLOCK_SIZE], BLOCK_SIZE);
        encrypt_block(&block, key);
        memcpy(&ciphertext[i * BLOCK_SIZE], &block, BLOCK_SIZE);
    }
}
void cbc_encrypt(char *plaintext, int *length, uint64_t key, uint64_t iv, char *ciphertext) {
    int num_blocks = *length / BLOCK_SIZE;
    uint64_t previous_block = iv; 
    for (int i = 0; i < num_blocks; i++) {
        uint64_t block = 0;
        memcpy(&block, &plaintext[i * BLOCK_SIZE], BLOCK_SIZE);
        block ^= previous_block;
        encrypt_block(&block, key);
        memcpy(&ciphertext[i * BLOCK_SIZE], &block, BLOCK_SIZE);
        previous_block = block;
    }
}
void cfb_encrypt(char *plaintext, int *length, uint64_t key, uint64_t iv, char *ciphertext) {
    int num_blocks = *length / BLOCK_SIZE;
    uint64_t previous_block = iv;  
    for (int i = 0; i < num_blocks; i++) {
        uint64_t block = 0;
        memcpy(&block, &plaintext[i * BLOCK_SIZE], BLOCK_SIZE);
        encrypt_block(&previous_block, key);
        block ^= previous_block;
        memcpy(&ciphertext[i * BLOCK_SIZE], &block, BLOCK_SIZE);
        previous_block = block; 
    }
}
int main() {
    char message[] = "Hello, this is a test message."; 
    uint64_t key = 0x1234567890abcdef;  
    uint64_t iv = 0xabcdef1234567890;   
    int length = strlen(message);
    pad_message(message, &length);
    printf("Original message: %s\n", message);
    printf("Padded message length: %d\n", length);
    char ciphertext[length];
    ecb_encrypt(message, &length, key, ciphertext);
    printf("Encrypted (ECB mode):\n");
    for (int i = 0; i < length; i++) {
        printf("%02x", (unsigned char)ciphertext[i]);
    }
    printf("\n");
    cbc_encrypt(message, &length, key, iv, ciphertext);
    printf("Encrypted (CBC mode):\n");
    for (int i = 0; i < length; i++) {
        printf("%02x", (unsigned char)ciphertext[i]);
    }
    printf("\n");
    cfb_encrypt(message, &length, key, iv, ciphertext);
    printf("Encrypted (CFB mode):\n");
    for (int i = 0; i < length; i++) {
        printf("%02x", (unsigned char)ciphertext[i]);
    }
    printf("\n");
    return 0;
}
