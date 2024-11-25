#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 5
char matrix[SIZE][SIZE];
void prepareMatrix(char key[]) {
    int used[26] = {0}; 
    int index = 0;
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (isalpha(ch) && !used[ch - 'A']) {
            used[ch - 'A'] = 1;
            matrix[index / SIZE][index % SIZE] = ch;
            index++;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!used[ch - 'A']) {
            used[ch - 'A'] = 1;
            matrix[index / SIZE][index % SIZE] = ch;
            index++;
        }
    }
}
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; 
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encrypt(char plaintext[], char ciphertext[]) {
    int len = strlen(plaintext);
    int index = 0;
    for (int i = 0; i < len; i += 2) {
        char a = toupper(plaintext[i]);
        char b = toupper(plaintext[i + 1]);
        if (b == '\0') b = 'X'; 
        if (a == b) b = 'X';    
        int row1, col1, row2, col2;
        findPosition(a, &row1, &col1);
        findPosition(b, &row2, &col2);
        if (row1 == row2) {
            ciphertext[index++] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[index++] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[index++] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[index++] = matrix[(row2 + 1) % SIZE][col2];
        } else {		
            ciphertext[index++] = matrix[row1][col2];
            ciphertext[index++] = matrix[row2][col1];
        }
    }
    ciphertext[index] = '\0';
}
int main() {
    char key[100], plaintext[100], ciphertext[100];
    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; 
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; 
    prepareMatrix(key);
    encrypt(plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}
