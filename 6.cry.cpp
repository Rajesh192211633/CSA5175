#include <stdio.h>
#include <string.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  
}

void decryptAffine(char *ciphertext, char *plaintext, int a, int b) {
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Error: Modular inverse of 'a' does not exist. Please choose a different value for 'a'.\n");
        return;
    }

    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((a_inv * (ciphertext[i] - 'A' - b + 26)) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((a_inv * (ciphertext[i] - 'a' - b + 26)) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i];  
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[] = "BUEF...";  
    char plaintext[100];
    int a = 0, b = 0;
    
   
    
    int p_B = 4;  
    int C_B = 1;  
    int p_U = 19; 
    int C_U = 20; 

    for (a = 1; a < 26; a++) {
        for (b = 0; b < 26; b++) {
            if ((a * p_B + b) % 26 == C_B && (a * p_U + b) % 26 == C_U) {
                printf("Found a = %d, b = %d\n", a, b);
                decryptAffine(ciphertext, plaintext, a, b);
                printf("Decrypted text: %s\n", plaintext);
                return 0;
            }
        }
    }

    printf("Could not find valid a and b\n");
    return 0;
}
