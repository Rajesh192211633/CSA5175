#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26

int main() {
    // Hill cipher key matrix
    int key[2][2] = {{9, 4}, {5, 7}};
    
    // Message to encrypt
    char message[] = "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCK";
    
    int len = strlen(message);
    int encrypted[len];
    
    // Encrypting the message
    for (int i = 0; i < len; i += 2) {
        int m1 = message[i] - 'A';        // First letter of the pair
        int m2 = message[i+1] - 'A';      // Second letter of the pair

        // Matrix multiplication and mod 26
        encrypted[i] = (key[0][0] * m1 + key[0][1] * m2) % SIZE;
        encrypted[i+1] = (key[1][0] * m1 + key[1][1] * m2) % SIZE;
        
        // Convert numbers back to letters
        encrypted[i] += 'A';
        encrypted[i+1] += 'A';
    }
    
    // Print encrypted message
    printf("Encrypted message: ");
    for (int i = 0; i < len; i++) {
        printf("%c", encrypted[i]);
    }
    printf("\n");

    // Decrypting the message (using the inverse of the matrix)
    int determinant = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    determinant = (determinant % SIZE + SIZE) % SIZE; // Ensure positive mod 26
    int inv_det = 0;

    // Find modular inverse of the determinant
    for (int i = 0; i < SIZE; i++) {
        if ((determinant * i) % SIZE == 1) {
            inv_det = i;
            break;
        }
    }

    // Find inverse matrix
    int inv_key[2][2] = {
        {(key[1][1] * inv_det) % SIZE, (-key[0][1] * inv_det) % SIZE},
        {(-key[1][0] * inv_det) % SIZE, (key[0][0] * inv_det) % SIZE}
    };

    // Decrypt the message using the inverse matrix
    int decrypted[len];
    for (int i = 0; i < len; i += 2) {
        int e1 = encrypted[i] - 'A';
        int e2 = encrypted[i+1] - 'A';

        decrypted[i] = (inv_key[0][0] * e1 + inv_key[0][1] * e2) % SIZE;
        decrypted[i+1] = (inv_key[1][0] * e1 + inv_key[1][1] * e2) % SIZE;
        
        decrypted[i] += 'A';
        decrypted[i+1] += 'A';
    }
    
    // Print decrypted message
    printf("Decrypted message: ");
    for (int i = 0; i < len; i++) {
        printf("%c", decrypted[i]);
    }
    printf("\n");

    return 0;
}

