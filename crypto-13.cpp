#include <stdio.h>
#include <stdlib.h>
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}
int determinantMod26(int matrix[2][2]) {
    int det = (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % 26;
    if (det < 0) det += 26;
    return det;
}
void inverseMatrixMod26(int matrix[2][2], int invMatrix[2][2]) {
    int det = determinantMod26(matrix);
    int detInv = modInverse(det, 26);
    if (detInv == -1) {
        printf("Matrix is not invertible modulo 26.\n");
        exit(1);
    }
    invMatrix[0][0] = (matrix[1][1] * detInv) % 26;
    invMatrix[0][1] = (-matrix[0][1] * detInv + 26) % 26;
    invMatrix[1][0] = (-matrix[1][0] * detInv + 26) % 26;
    invMatrix[1][1] = (matrix[0][0] * detInv) % 26;
}
void multiplyMatricesMod26(int mat1[2][2], int mat2[2][2], int result[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < 2; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
            result[i][j] %= 26;
        }
    }
}
int main() {
    int plaintext[2][2] = {{7, 4}, {11, 19}};
    int ciphertext[2][2] = {{19, 0}, {12, 7}};
    int invPlaintext[2][2];
    inverseMatrixMod26(plaintext, invPlaintext);
    int keyMatrix[2][2];
    multiplyMatricesMod26(ciphertext, invPlaintext, keyMatrix);
    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", keyMatrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
