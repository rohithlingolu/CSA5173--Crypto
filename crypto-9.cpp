#include <stdio.h>
#include <string.h>
#include <ctype.h>
char playfairSquare[5][5];
void createPlayfairSquare(const char *keyword) {
    int used[26] = {0}; 
    int index = 0;
    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (ch == 'J') ch = 'I';
        if (!used[ch - 'A']) {
            playfairSquare[index / 5][index % 5] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; 
        if (!used[ch - 'A']) {
            playfairSquare[index / 5][index % 5] = ch;
            index++;
        }
    }
}
void findPosition(char ch, int *row, int *col) {
    if (ch == 'J') ch = 'I'; 
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
void decryptPair(char a, char b, char *plainA, char *plainB) {
    int row1, col1, row2, col2;
    findPosition(a, &row1, &col1);
    findPosition(b, &row2, &col2);
    if (row1 == row2) { 
        *plainA = playfairSquare[row1][(col1 + 4) % 5];
        *plainB = playfairSquare[row2][(col2 + 4) % 5];
    } else if (col1 == col2) { 
        *plainA = playfairSquare[(row1 + 4) % 5][col1];
        *plainB = playfairSquare[(row2 + 4) % 5][col2];
    } else { 
        *plainA = playfairSquare[row1][col2];
        *plainB = playfairSquare[row2][col1];
    }
}
void decrypt(const char *ciphertext, char *plaintext) {
    int len = strlen(ciphertext);
    int index = 0;
    for (int i = 0; i < len; i += 2) {
        char a = toupper(ciphertext[i]);
        char b = toupper(ciphertext[i + 1]);
        if (isalpha(a) && isalpha(b)) {
            decryptPair(a, b, &plaintext[index], &plaintext[index + 1]);
            index += 2;
        }
    }
    plaintext[index] = '\0'; 
}
int main() {
    const char keyword[] = "NAVY";
    createPlayfairSquare(keyword);
    printf("Playfair Square:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", playfairSquare[i][j]);
        }
        printf("\n");
    }
    const char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPO";
    char plaintext[100];
    decrypt(ciphertext, plaintext);
    printf("\nDecrypted Text:\n%s\n", plaintext);
    return 0;
}
