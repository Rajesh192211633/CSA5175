#include <stdio.h>
#include <string.h>

#define SIZE 26

int main() {
    // Given plaintext and key stream
    char plaintext[] = "send more money";
    int key_stream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9}; // Key stream
    int ciphertext[strlen(plaintext)];
    
    int len = strlen(plaintext);
    
    // Encrypting the message using the key stream
    for (int i = 0; i < len; i++) {
        if (plaintext[i] == ' ') {  // If it's a space, just keep it as space
            ciphertext[i] = ' ';
        } else {
            // Encrypt each character (A=0, B=1, ..., Z=25)
            int shift = key_stream[i];
            ciphertext[i] = (plaintext[i] - 'a' + shift) % SIZE + 'a';  // Encrypt with shift
        }
    }

    // Printing the encrypted message
    printf("Encrypted message: ");
    for (int i = 0; i < len; i++) {
        printf("%c", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

