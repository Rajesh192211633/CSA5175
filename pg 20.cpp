#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DES_BLOCK_SIZE 8

// Placeholder function for DES encryption (replace with actual DES or AES encryption)
void encrypt_block(unsigned char *block, unsigned char *key, unsigned char *output) {
    // Placeholder: this should encrypt the block using a cipher (like DES or AES).
    // For demonstration, it just copies the block to output.
    memcpy(output, block, DES_BLOCK_SIZE);
}

// Function to pad the plaintext to a multiple of DES_BLOCK_SIZE
void pad_data(unsigned char *data, size_t *length) {
    size_t padding_needed = DES_BLOCK_SIZE - (*length % DES_BLOCK_SIZE);
    for (size_t i = *length; i < *length + padding_needed; i++) {
        data[i] = (unsigned char)padding_needed;  // Padding with the value of padding needed
    }
    *length += padding_needed;
}

// ECB encryption function
void ecb_encrypt(unsigned char *data, size_t data_len, unsigned char *key, unsigned char *output) {
    unsigned char block[DES_BLOCK_SIZE];
    unsigned char encrypted_block[DES_BLOCK_SIZE];
    
    // Process each block of plaintext
    for (size_t i = 0; i < data_len; i += DES_BLOCK_SIZE) {
        // Get a block of plaintext
        memcpy(block, data + i, DES_BLOCK_SIZE);
        
        // Encrypt the block
        encrypt_block(block, key, encrypted_block);
        
        // Store the encrypted block
        memcpy(output + i, encrypted_block, DES_BLOCK_SIZE);
    }
}

int main() {
   unsigned char key[DES_BLOCK_SIZE] = {'1', '2', '3', '4', '5', '6', '7', '8'};
 // 8-byte key for encryption
    unsigned char plaintext[] = "This is a test message for ECB mode!";
    size_t plaintext_len = strlen((char *)plaintext);
    
    // Pad the plaintext to a multiple of DES_BLOCK_SIZE
    pad_data(plaintext, &plaintext_len);

    unsigned char ciphertext[128];  // Buffer for ciphertext

    // Perform encryption
    ecb_encrypt(plaintext, plaintext_len, key, ciphertext);
    
    // Print the ciphertext in hexadecimal format
    printf("Ciphertext: ");
    for (size_t i = 0; i < plaintext_len; i++) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

