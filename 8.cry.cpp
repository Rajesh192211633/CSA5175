#include <stdio.h>
#include <string.h>

int main() {
    char keyword[] = "CIPHER";
    char plaintext[100], cipher[26];
    int used[26] = {0}, k = 0;

    for (int i = 0; i < strlen(keyword); i++) {
        if (!used[keyword[i] - 'A']) {
            cipher[k++] = keyword[i];
            used[keyword[i] - 'A'] = 1;
        }
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        if (!used[c - 'A']) {
            cipher[k++] = c;
        }
    }

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            plaintext[i] = cipher[plaintext[i] - 'a'];
        } else if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            plaintext[i] = cipher[plaintext[i] - 'A'];
        }
    }

    printf("Encrypted text: %s", plaintext);
    return 0;
}
