#include <stdio.h>
#include <string.h>
#include <ctype.h>
void analyzeFrequency(const char *ciphertext, int freq[256]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {
            freq[(unsigned char)ciphertext[i]]++;
        }
    }
} 
void displayFrequency(int freq[256]) {
    printf("Character Frequency Analysis:\n");
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0 && isprint(i)) {
            printf("'%c': %d\n", i, freq[i]);
        }
    }
}
void decryptMessage(const char *ciphertext, const char *key, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {
            char c = ciphertext[i];
            plaintext[i] = key[c] ? key[c] : c;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
int main() {
    const char ciphertext[] =
        "53‡‡†305))6*:4826)41.)41);806*;48+860))85;;]8*::$8+83 "
        "(88)5*4:46(;88*96?;8)(;485);5+2:(;4956*2(5*4)88 4069285);"
        ")6+8)4‡‡:1($9:48081;8:811;48485;4)485+528806*81 ($9;48;"
        "(88;4(†234;48)4;161;:188;12;";
    int freq[256] = {0};
    analyzeFrequency(ciphertext, freq);
    displayFrequency(freq);
    char key[256] = {0};
    for (int i = 0; i < 256; i++) {
        key[i] = i;
    }
    key['8'] = 'e'; 
    key['4'] = 't'; 
    key['5'] = 'h'; 
    char plaintext[1000] = {0};
    decryptMessage(ciphertext, key, plaintext);
    printf("\nPartially Decrypted Text:\n%s\n", plaintext);
    printf("\nContinue refining the key to complete decryption.\n");
    return 0;
}
