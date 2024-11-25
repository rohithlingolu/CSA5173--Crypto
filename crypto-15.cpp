#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define ALPHABET_SIZE 26
const double ENGLISH_LETTER_FREQUENCY[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 
    6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 
    0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 
    1.974, 0.074
};
double scoreText(const char *text) {
    int letterCounts[ALPHABET_SIZE] = {0};
    int totalLetters = 0;
    double score = 0.0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            letterCounts[tolower(text[i]) - 'a']++;
            totalLetters++;
        }
    }
    if (totalLetters == 0) return -1.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double frequency = (double)letterCounts[i] / totalLetters * 100;
        score += abs(frequency - ENGLISH_LETTER_FREQUENCY[i]);
    }
    return score;
}
void decryptAdditiveCipher(const char *ciphertext, int key, char *plaintext) {
    int n = strlen(ciphertext);
    for (int i = 0; i < n; i++) {
        if (isalpha(ciphertext[i])) {
            if (islower(ciphertext[i])) {
                plaintext[i] = ((ciphertext[i] - 'a' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
            } else {
                plaintext[i] = ((ciphertext[i] - 'A' - key + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[n] = '\0';
}
typedef struct {
    int key;
    double score;
    char plaintext[1000];
} Candidate;
int compareCandidates(const void *a, const void *b) {
    double diff = ((Candidate *)a)->score - ((Candidate *)b)->score;
    return diff > 0 ? 1 : (diff < 0 ? -1 : 0);
}
void letterFrequencyAttack(const char *ciphertext, int topResults) {
    Candidate candidates[ALPHABET_SIZE];
    char plaintext[1000];
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decryptAdditiveCipher(ciphertext, key, plaintext);
        candidates[key].key = key;
        candidates[key].score = scoreText(plaintext);
        strcpy(candidates[key].plaintext, plaintext);
    }
    qsort(candidates, ALPHABET_SIZE, sizeof(Candidate), compareCandidates);
    for (int i = 0; i < topResults && i < ALPHABET_SIZE; i++) {
        printf("Key: %d, Score: %.2f, Plaintext: %s\n", candidates[i].key, candidates[i].score, candidates[i].plaintext);
    }
}
int main() {
    char ciphertext[1000];
    int topResults;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';
    printf("Enter the number of top results to display: ");
    scanf("%d", &topResults);
    letterFrequencyAttack(ciphertext, topResults);
    return 0;
}
