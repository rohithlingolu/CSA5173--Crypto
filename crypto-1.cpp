#include <stdio.h>
#include <string.h>
#include <ctype.h>
void processText(char text[], int key, int isEncrypt) {
    int i;
    char ch;
    if (!isEncrypt) {
        key = -key;
    }
    for (i = 0; text[i] != '\0'; ++i) {
        ch = text[i];

        if (isalpha(ch)) {
            if (isupper(ch)) {
                ch = (ch - 'A' + key + 26) % 26 + 'A';
            } else if (islower(ch)) {
                ch = (ch - 'a' + key + 26) % 26 + 'a';
            }
        }
        text[i] = ch;
    }
}
int main() {
    char text[100];
    int key, choice;
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 
    do {
        printf("\nChoose an option:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 1 || choice == 2) {
            printf("Enter the key (1-25): ");
            scanf("%d", &key);
            if (key < 1 || key > 25) {
                printf("Invalid key! Please enter a value between 1 and 25.\n");
                continue;
            }
            processText(text, key, choice == 1);
            if (choice == 1) {
                printf("Encrypted text: %s\n", text);
            } else {
                printf("Decrypted text: %s\n", text);
            }
        } else if (choice != 3) {
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
    printf("Program exited.\n");
    return 0;
}

