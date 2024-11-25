#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define BLOCK_SIZE_128 16 
#define BLOCK_SIZE_64 8  
#define R_B_128 0x87      
#define R_B_64  0x1B      
void leftShift(uint8_t *block, int block_size) {
    int i;
    uint8_t carry = 0;
    for (i = block_size - 1; i >= 0; i--) {
        uint8_t new_carry = block[i] >> 7;
        block[i] = (block[i] << 1) | carry;
        carry = new_carry;
    }
}
void xorBlocks(uint8_t *block1, uint8_t *block2, uint8_t *result, int block_size) {
    for (int i = 0; i < block_size; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}
int MSB_of(uint8_t *block, int block_size) {
    return (block[0] & 0x80) != 0; 
}
void generateCMACSubkeys(int block_size, uint8_t *subkey1, uint8_t *subkey2) {
    uint8_t zero_block[BLOCK_SIZE_128] = {0}; 
    uint8_t R_b[BLOCK_SIZE_128];
    uint8_t encrypted_block[BLOCK_SIZE_128];
    memcpy(encrypted_block, zero_block, block_size);
    leftShift(encrypted_block, block_size);
    memcpy(subkey1, encrypted_block, block_size);
    if (MSB_of(subkey1, block_size)) {
        if (block_size == BLOCK_SIZE_128) {
            R_b[0] = R_B_128;
        } else {
            R_b[0] = R_B_64;
        }
        xorBlocks(subkey1, R_b, subkey1, block_size);
    }
    leftShift(subkey1, block_size);
    memcpy(subkey2, subkey1, block_size);
    if (MSB_of(subkey2, block_size)) {
        xorBlocks(subkey2, R_b, subkey2, block_size);
    }
}
int main() {
    uint8_t subkey1[BLOCK_SIZE_128], subkey2[BLOCK_SIZE_128];
    int block_size = BLOCK_SIZE_128;
    generateCMACSubkeys(block_size, subkey1, subkey2);
    printf("Subkey1: ");
    for (int i = 0; i < block_size; i++) {
        printf("%02X", subkey1[i]);
    }
    printf("\n");
    printf("Subkey2: ");
    for (int i = 0; i < block_size; i++) {
        printf("%02X", subkey2[i]);
    }
    printf("\n");
    return 0;
}
