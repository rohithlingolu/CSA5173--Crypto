#include <stdio.h>
#include <string.h>
#include <ctype.h>
char playfairSquare[5][5] = {
    {'M', 'F', 'H', 'I', 'J'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (playfairSquare[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void encryptPair(char a, char b, char *cipherA, char *cipherB) {
    int row1, col1, row2, col2;
    findPosition(a, &row1, &col1);
    findPosition(b, &row2, &col2);
    if (row1 == row2) {  
        *cipherA = playfairSquare[row1][(col1 + 1) % 5];
        *cipherB = playfairSquare[row2][(col2 + 1) % 5];
    } else if (col1 == col2) {  
        *cipherA = playfairSquare[(row1 + 1) % 5][col1];
        *cipherB = playfairSquare[(row2 + 1) % 5][col2];
    } else { 
        *cipherA = playfairSquare[row1][col2];
        *cipherB = playfairSquare[row2][col1];
    }
}
void preparePlaintext(char *plaintext, char *preparedText) {
    int j = 0;
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            preparedText[j++] = ch;
        }
    }
    if (j % 2 != 0) {
        preparedText[j++] = 'X';
    }
    preparedText[j] = '\0';
}
int main() {
    char plaintext[] = "Must see you over Cadogan West.";
    char preparedText[100];
    char ciphertext[100];
    preparePlaintext(plaintext, preparedText);
    int j = 0;
    for (int i = 0; preparedText[i] != '\0'; i += 2) {
        char a = preparedText[i];
        char b = preparedText[i + 1];
        encryptPair(a, b, &ciphertext[j], &ciphertext[j + 1]);
        j += 2;
    }
    ciphertext[j] = '\0';
    printf("Encrypted Text: %s\n", ciphertext);
    return 0;
}
