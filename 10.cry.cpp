#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

void findPosition(char letter, int *row, int *col) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (matrix[r][c] == letter) {
                *row = r;
                *col = c;
                return;
            }
        }
    }
}

void preprocessText(char *input, char *output) {
    int len = strlen(input);
    int j = 0;

    for (int i = 0; i < len; i++) {
        char ch = toupper(input[i]);

        if (ch >= 'A' && ch <= 'Z') {
            if (ch == 'J') ch = 'I'; 

            if (j > 0 && output[j - 1] == ch && j % 2 == 1) {
                output[j++] = 'X';
            }

            output[j++] = ch;
        }
    }

    if (j % 2 == 1) {
        output[j++] = 'X';
    }

    output[j] = '\0';
}

void encryptText(char *plaintext, char *ciphertext) {
    int len = strlen(plaintext);

    for (int i = 0; i < len; i += 2) {
        char a = plaintext[i];
        char b = plaintext[i + 1];

        int row1, col1, row2, col2;
        findPosition(a, &row1, &col1);
        findPosition(b, &row2, &col2);

        if (row1 == row2) { 
            ciphertext[i] = matrix[row1][(col1 + 1) % 5];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) { 
            ciphertext[i] = matrix[(row1 + 1) % 5][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % 5][col2];
        } else { 
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }

    ciphertext[len] = '\0';
}

int main() {
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    char preparedText[100], ciphertext[100];

    preprocessText(plaintext, preparedText);
    printf("Prepared Text: %s\n", preparedText);

    encryptText(preparedText, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
