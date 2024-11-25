#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 8

uint8_t keys[10][BLOCK_SIZE];
uint8_t initial_permutation[8] = {2, 6, 3, 1, 4, 8, 5, 7};
uint8_t inverse_initial_permutation[8] = {4, 1, 3, 5, 7, 2, 8, 6};

void generate_keys(uint8_t key[BLOCK_SIZE]);
void sdes_encrypt(uint8_t plaintext[BLOCK_SIZE], uint8_t ciphertext[BLOCK_SIZE]);
void sdes_decrypt(uint8_t ciphertext[BLOCK_SIZE], uint8_t plaintext[BLOCK_SIZE]);
void counter_mode_encrypt(uint8_t *plaintext, size_t length, uint8_t *key, uint8_t *counter);
void counter_mode_decrypt(uint8_t *ciphertext, size_t length, uint8_t *key, uint8_t *counter);
void print_binary(uint8_t *data, size_t length);

int main() {
    uint8_t key[BLOCK_SIZE] = {0b011111101};
    uint8_t plaintext[] = {0b00000001, 0b00000010, 0b00000000};
    uint8_t counter[BLOCK_SIZE] = {0b00000000};
    size_t length = sizeof(plaintext) / sizeof(plaintext[0]);
    uint8_t ciphertext[length];

    counter_mode_encrypt(plaintext, length, key, counter);
    printf("Ciphertext: ");
    print_binary(ciphertext, length);

    counter_mode_decrypt(ciphertext, length, key, counter);
    printf("Decrypted text: ");
    print_binary(plaintext, length);

    return 0;
}

void generate_keys(uint8_t key[BLOCK_SIZE]) {}

void sdes_encrypt(uint8_t plaintext[BLOCK_SIZE], uint8_t ciphertext[BLOCK_SIZE]) {}

void sdes_decrypt(uint8_t ciphertext[BLOCK_SIZE], uint8_t plaintext[BLOCK_SIZE]) {}

void counter_mode_encrypt(uint8_t *plaintext, size_t length, uint8_t *key, uint8_t *counter) {
    uint8_t keystream[BLOCK_SIZE];

    for (size_t i = 0; i < length; i++) {
        sdes_encrypt(counter, keystream);
        plaintext[i] ^= keystream[i % BLOCK_SIZE];
        for (int j = BLOCK_SIZE - 1; j >= 0; j--) {
            if (++counter[j] != 0) break;
        }
    }
}

void counter_mode_decrypt(uint8_t *ciphertext, size_t length, uint8_t *key, uint8_t *counter) {
    counter_mode_encrypt(ciphertext, length, key, counter);
}

void print_binary(uint8_t *data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        for (int j = BLOCK_SIZE - 1; j >= 0; j--) {
            printf("%d", (data[i] >> j) & 1);
        }
        printf(" ");
    }
    printf("\n");
}

