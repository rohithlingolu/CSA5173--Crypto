#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 8

void xor_blocks(unsigned char *a, unsigned char *b, unsigned char *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] ^ b[i];
    }
}

void encrypt_block(unsigned char *block, unsigned char *key, unsigned char *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i];
    }
}

void ecb_encrypt(unsigned char *plaintext, unsigned char *key, int size) {
    unsigned char encrypted_block[BLOCK_SIZE];
    printf("\nECB Mode Encryption:\n");
    for (int i = 0; i < size; i += BLOCK_SIZE) {
        encrypt_block(plaintext + i, key, encrypted_block);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%02X ", encrypted_block[j]);
        }
        printf("\n");
    }
}

void cbc_encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *iv, int size) {
    unsigned char block[BLOCK_SIZE], encrypted_block[BLOCK_SIZE];
    printf("\nCBC Mode Encryption:\n");
    memcpy(block, iv, BLOCK_SIZE);
    for (int i = 0; i < size; i += BLOCK_SIZE) {
        xor_blocks(block, plaintext + i, block, BLOCK_SIZE);
        encrypt_block(block, key, encrypted_block);
        memcpy(block, encrypted_block, BLOCK_SIZE);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%02X ", encrypted_block[j]);
        }
        printf("\n");
    }
}

void cfb_encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *iv, int size) {
    unsigned char block[BLOCK_SIZE], encrypted_block[BLOCK_SIZE];
    printf("\nCFB Mode Encryption:\n");
    memcpy(block, iv, BLOCK_SIZE);
    for (int i = 0; i < size; i += BLOCK_SIZE) {
        encrypt_block(block, key, encrypted_block);
        xor_blocks(encrypted_block, plaintext + i, block, BLOCK_SIZE);
        for (int j = 0; j < BLOCK_SIZE; j++) {
            printf("%02X ", block[j]);
        }
        printf("\n");
    }
}

void pad_message(unsigned char *message, int *size) {
    int padding_length = BLOCK_SIZE - (*size % BLOCK_SIZE);
    message[*size] = 0x80;
    for (int i = 1; i < padding_length; i++) {
        message[*size + i] = 0x00;
    }
    *size += padding_length;
}

int main() {
    unsigned char plaintext[128], key[BLOCK_SIZE], iv[BLOCK_SIZE];
    int plaintext_length;

    for (int i = 0; i < BLOCK_SIZE; i++) {
        key[i] = (unsigned char)(i + 1);
        iv[i] = (unsigned char)(BLOCK_SIZE - i);
    }

    printf("Enter plaintext (multiple of 8 characters recommended): ");
    fgets((char *)plaintext, sizeof(plaintext), stdin);
    plaintext_length = strlen((char *)plaintext);

    if (plaintext[plaintext_length - 1] == '\n') {
        plaintext[--plaintext_length] = '\0';
    }

    pad_message(plaintext, &plaintext_length);

    printf("\nPadded plaintext:\n");
    for (int i = 0; i < plaintext_length; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    ecb_encrypt(plaintext, key, plaintext_length);
    cbc_encrypt(plaintext, key, iv, plaintext_length);
    cfb_encrypt(plaintext, key, iv, plaintext_length);

    return 0;
}
