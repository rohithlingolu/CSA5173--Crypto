#include <stdio.h>
#include <string.h>
#include <ctype.h>
void generateCipherSequence(const char *keyword, char *cipher) {
    int used[26] = {0}; 
    int index = 0;
    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]); 
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
            used[ch - 'A'] = 1;
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[index++] = ch;
        }
    }
    cipher[index] = '\0'; 
}
void encrypt(const char *plaintext, const char *cipher, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            ciphertext[i] = cipher[ch - 'A']; 
        } else {
            ciphertext[i] = plaintext[i]; 
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; 
}
void decrypt(const char *ciphertext, const char *cipher, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            for (int j = 0; j < 26; j++) {
                if (cipher[j] == ch) {
                    plaintext[i] = 'A' + j;
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; 
}
int main() {
    const char keyword[] = "CIPHER";
    char cipher[27];
    generateCipherSequence(keyword, cipher);
    printf("Cipher Sequence: %s\n", cipher);
    const char plaintext[] = "This is a test message.";
    char ciphertext[100], decryptedtext[100];
    encrypt(plaintext, cipher, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    decrypt(ciphertext, cipher, decryptedtext);
    printf("Decrypted Text: %s\n", decryptedtext);
    return 0;
}
