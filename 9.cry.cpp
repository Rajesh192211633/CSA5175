#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char matrix[5][5] = {
        {'K', 'E', 'Y', 'W', 'O'},
        {'R', 'D', 'A', 'B', 'C'},
        {'F', 'G', 'H', 'I', 'L'},
        {'M', 'N', 'P', 'Q', 'S'},
        {'T', 'U', 'V', 'X', 'Z'}
    };

    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[100];
    int len = strlen(ciphertext);

    for (int i = 0; i < len; i += 2) {
        char a = ciphertext[i], b = ciphertext[i + 1];
        int row1, col1, row2, col2;

        for (int r = 0; r < 5; r++) {
            for (int c = 0; c < 5; c++) {
                if (matrix[r][c] == a) {
                    row1 = r;
                    col1 = c;
                }
                if (matrix[r][c] == b) {
                    row2 = r;
                    col2 = c;
                }
            }
        }

        if (row1 == row2) { 
            plaintext[i] = matrix[row1][(col1 + 4) % 5];
            plaintext[i + 1] = matrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) { 
            plaintext[i] = matrix[(row1 + 4) % 5][col1];
            plaintext[i + 1] = matrix[(row2 + 4) % 5][col2];
        } else { 
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }

    plaintext[len] = '\0';
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}
