#include <stdio.h>
#include <stdint.h>
#include <string.h>
static const int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};
static const int FP[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};
static const int S[8][4][16] = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
};
void initial_permutation(uint64_t *data) {
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        if (*data & (1ULL << (64 - IP[i]))) {
            result |= (1ULL << (63 - i));
        }
    }
    *data = result;
}
void final_permutation(uint64_t *data) {
    uint64_t result = 0;
    for (int i = 0; i < 64; i++) {
        if (*data & (1ULL << (64 - FP[i]))) {
            result |= (1ULL << (63 - i));
        }
    }
    *data = result;
}
void des_encrypt(uint64_t *plaintext, uint64_t *key) {
    initial_permutation(plaintext);
    uint32_t left = (uint32_t)(*plaintext >> 32);
    uint32_t right = (uint32_t)(*plaintext);
    for (int round = 0; round < 16; round++) {
        uint32_t temp = left;
        left = right;
        right = temp ^ left; 
    }
    *plaintext = ((uint64_t)left << 32) | right;
    final_permutation(plaintext);
}
void des_decrypt(uint64_t *ciphertext, uint64_t *key) {
    initial_permutation(ciphertext);
    uint32_t left = (uint32_t)(*ciphertext >> 32);
    uint32_t right = (uint32_t)(*ciphertext);
    for (int round = 0; round < 16; round++) {
        uint32_t temp = left;
        left = right;
        right = temp ^ left;
    }
    *ciphertext = ((uint64_t)left << 32) | right;
    final_permutation(ciphertext);
}
int main() {
    uint64_t plaintext = 0x1234567890abcdef; 
    uint64_t key = 0x133457799BBCDFF1;       
    printf("Plaintext: 0x%016llx\n", plaintext);
    printf("Key: 0x%016llx\n", key);
    des_encrypt(&plaintext, &key);
    printf("Encrypted: 0x%016llx\n", plaintext);
    des_decrypt(&plaintext, &key);
    printf("Decrypted: 0x%016llx\n", plaintext);
    return 0;
}
