#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26
#define TOP_PLAINTEXTS 10
char englishFreq[ALPHABET_SIZE] = {'E', 'T', 'A', 'O', 'I', 'N', 'S', 'H', 'R', 'D', 'L', 'C', 'U', 'M', 'W', 'F', 'G', 'Y', 'P', 'B', 'V', 'K', 'J', 'X', 'Q', 'Z'};
void calculateFrequency(char *text, int *freq) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            freq[text[i] - 'A']++;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            freq[text[i] - 'a']++;
        }
    }
}
void sortFrequency(int *freq, char *letters) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        letters[i] = i + 'A';
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (freq[i] < freq[j]) {
                int tempFreq = freq[i];
                freq[i] = freq[j];
                freq[j] = tempFreq;
                char tempLetter = letters[i];
                letters[i] = letters[j];
                letters[j] = tempLetter;
            }
        }
    }
}
void decryptWithMapping(char *ciphertext, char *mapping, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = mapping[ciphertext[i] - 'A'];
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = mapping[ciphertext[i] - 'a'] + ('a' - 'A');
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
}
void generateMappings(char *sortedCipher, char *sortedEnglish, char mappings[TOP_PLAINTEXTS][ALPHABET_SIZE]) {
    for (int i = 0; i < TOP_PLAINTEXTS; i++) {
        for (int j = 0; j < ALPHABET_SIZE; j++) {
            mappings[i][sortedCipher[j] - 'A'] = sortedEnglish[(j + i) % ALPHABET_SIZE];
        }
    }
}
int main() {
    char ciphertext[1024], plaintext[1024];
    int freq[ALPHABET_SIZE] = {0};
    char sortedCipher[ALPHABET_SIZE], mappings[TOP_PLAINTEXTS][ALPHABET_SIZE];
    printf("Enter ciphertext: ");
    fgets(ciphertext, 1024, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    calculateFrequency(ciphertext, freq);
    sortFrequency(freq, sortedCipher);
    generateMappings(sortedCipher, englishFreq, mappings);
    printf("Top %d possible plaintexts:\n", TOP_PLAINTEXTS);
    for (int i = 0; i < TOP_PLAINTEXTS; i++) {
        decryptWithMapping(ciphertext, mappings[i], plaintext);
        plaintext[strlen(ciphertext)] = '\0';
        printf("%d: %s\n", i + 1, plaintext);
    }
    return 0;
}
