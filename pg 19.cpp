#include <stdio.h>
#include <string.h>

#define BLOCK_SIZE 8 // Block size for 3DES

// Placeholder function for 3DES encryption of a single block
void encrypt_block(unsigned char *block, unsigned char *key, unsigned char *output) {
    // Dummy 3DES encryption: just XOR with the key for simplicity
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ key[i % 24]; // Simulating 3DES key usage
    }
}

// CBC encryption
void cbc_encrypt(unsigned char *plaintext, unsigned char *key, unsigned char *iv, unsigned char *ciphertext, size_t length) {
    unsigned char previous_block[BLOCK_SIZE];
    memcpy(previous_block, iv, BLOCK_SIZE); // Initialize with IV

    for (size_t i = 0; i < length; i += BLOCK_SIZE) {
        unsigned char block[BLOCK_SIZE];

        // XOR plaintext block with the previous ciphertext block (or IV for the first block)
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] = plaintext[i + j] ^ previous_block[j];
        }

        // Encrypt the XORed block
        encrypt_block(block, key, ciphertext + i);

        // Update the previous block to the current ciphertext block
        memcpy(previous_block, ciphertext + i, BLOCK_SIZE);
    }
}

int main() {
   unsigned char key[24] = {'1', '2', '3', '4', '5', '6', '7', '8', 
                         '9', '0', 'a', 'b', 'c', 'd', 'e', 'f',
                         '1', '2', '3', '4', '5', '6', '7', '8'};
 // 24-byte key for 3DES
    unsigned char iv[8] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
      // 8-byte IV
    unsigned char plaintext[] = "This is CBC mode!";    // Plaintext message

    size_t plaintext_len = strlen((char *)plaintext);
    size_t padded_len = plaintext_len + (BLOCK_SIZE - (plaintext_len % BLOCK_SIZE));
    unsigned char padded_plaintext[128] = {0};
    memcpy(padded_plaintext, plaintext, plaintext_len);

    // Add PKCS7 padding
    unsigned char padding_value = BLOCK_SIZE - (plaintext_len % BLOCK_SIZE);
    memset(padded_plaintext + plaintext_len, padding_value, padding_value);

    unsigned char ciphertext[128] = {0}; // Buffer for ciphertext

    // Encrypt plaintext using CBC mode
    cbc_encrypt(padded_plaintext, key, iv, ciphertext, padded_len);

    // Print the ciphertext in hexadecimal format
    printf("Ciphertext: ");
    for (size_t i = 0; i < padded_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

