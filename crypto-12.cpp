#include <stdio.h>
#include <string.h>
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; 
}
void hillCipherEncrypt(int key[2][2], char *plaintext, char *ciphertext) {
    int i, x, y, n = strlen(plaintext);
    for (i = 0; i < n; i += 2) {
        x = plaintext[i] - 'a';
        y = plaintext[i + 1] - 'a';
        ciphertext[i] = ((key[0][0] * x + key[0][1] * y) % 26) + 'a';
        ciphertext[i + 1] = ((key[1][0] * x + key[1][1] * y) % 26) + 'a';
    }
    ciphertext[n] = '\0';
}
void hillCipherDecrypt(int key[2][2], char *ciphertext, char *plaintext) {
    int i, x, y, n = strlen(ciphertext);
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    if (det < 0) det += 26;
    int detInv = modInverse(det, 26);
    if (detInv == -1) {
        printf("Key matrix is not invertible mod 26.\n");
        return;
    }
    int invKey[2][2];
    invKey[0][0] = (key[1][1] * detInv) % 26;
    invKey[0][1] = (-key[0][1] * detInv + 26) % 26;
    invKey[1][0] = (-key[1][0] * detInv + 26) % 26;
    invKey[1][1] = (key[0][0] * detInv) % 26;
    for (i = 0; i < n; i += 2) {
        x = ciphertext[i] - 'a';
        y = ciphertext[i + 1] - 'a';
        plaintext[i] = ((invKey[0][0] * x + invKey[0][1] * y) % 26) + 'a';
        plaintext[i + 1] = ((invKey[1][0] * x + invKey[1][1] * y) % 26) + 'a';
    }
    plaintext[n] = '\0';
}
int main() {
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    char ciphertext[100], decryptedtext[100];
    int key[2][2] = {{5, 7}, {6, 57}};
    int n = strlen(plaintext);
    if (n % 2 != 0) strcat(plaintext, "x");
    printf("Plaintext: %s\n", plaintext);
    hillCipherEncrypt(key, plaintext, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
    hillCipherDecrypt(key, ciphertext, decryptedtext);
    printf("Decrypted text: %s\n", decryptedtext);
    return 0;
}
