#include <stdio.h>

#define SIZE 26

int main() {
    // Known plaintext and ciphertext
    char plaintext[] = "HI"; // Plaintext: "HI"
    char ciphertext[] = "CJ"; // Ciphertext: "CJ"

    // Convert plaintext and ciphertext to numbers (A=0, B=1, ..., Z=25)
    int p1 = plaintext[0] - 'A', p2 = plaintext[1] - 'A';
    int c1 = ciphertext[0] - 'A', c2 = ciphertext[1] - 'A';

    // Construct the plaintext and ciphertext matrices
    int P[2][2] = { {p1, p2}, {p1, p2} };  // 2x2 matrix
    int C[2][2] = { {c1, c2}, {c1, c2} };  // 2x2 matrix

    // Calculate the determinant of P (mod 26)
    int det = (P[0][0] * P[1][1] - P[0][1] * P[1][0]) % SIZE;
    if (det < 0) det += SIZE;

    // Find the modular inverse of the determinant
    int inv_det = -1;
    for (int i = 0; i < SIZE; i++) {
        if ((det * i) % SIZE == 1) {
            inv_det = i;
            break;
        }
    }

    // If inverse of determinant does not exist, exit
    if (inv_det == -1) {
        printf("Inverse of determinant does not exist.\n");
        return 1;
    }

    // Inverse matrix of P (mod 26)
    int invP[2][2] = {
        { P[1][1] * inv_det % SIZE, -P[0][1] * inv_det % SIZE },
        { -P[1][0] * inv_det % SIZE, P[0][0] * inv_det % SIZE }
    };

    // Make sure all negative values are converted to positive modulo 26
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (invP[i][j] < 0) invP[i][j] += SIZE;
        }
    }

    // Now calculate the key matrix using the inverse of the plaintext matrix
    int key[2][2] = {
        { (C[0][0] * invP[0][0] + C[0][1] * invP[1][0]) % SIZE, (C[0][0] * invP[0][1] + C[0][1] * invP[1][1]) % SIZE },
        { (C[1][0] * invP[0][0] + C[1][1] * invP[1][0]) % SIZE, (C[1][0] * invP[0][1] + C[1][1] * invP[1][1]) % SIZE }
    };

    // Print the key matrix
    printf("Recovered Key Matrix:\n");
    printf("%d %d\n", key[0][0], key[0][1]);
    printf("%d %d\n", key[1][0], key[1][1]);

    return 0;
}

