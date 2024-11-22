#include <iostream>
#include <cstring>

#define AES_BLOCK_SIZE 16

// Example S-box for AES (just a part of it for simplicity)
static unsigned char sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, 0xca
};

// Simplified AES encryption (just Substitution for illustration)
void aes_encrypt(unsigned char *input, unsigned char *output, unsigned char *key) {
    for (int i = 0; i < AES_BLOCK_SIZE; i++) {
        output[i] = sbox[input[i] ^ key[i]];  // Substitution (basic, incomplete)
    }
}

int main() {
    unsigned char key[AES_BLOCK_SIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x97, 0x75, 0x46, 0x41, 0x54, 0x20};  // Example key
    unsigned char iv[AES_BLOCK_SIZE] = {0x00};  // Example IV
    unsigned char plaintext[] = "This is a plaintext message that needs padding.";
    int len = strlen((char *)plaintext);

    // Padding the plaintext to make the length a multiple of AES_BLOCK_SIZE
    int padding_len = AES_BLOCK_SIZE - (len % AES_BLOCK_SIZE);
    plaintext[len] = 0x80;  // Pad with a "1" bit (0x80 byte)
    memset(plaintext + len + 1, 0, padding_len - 1);
    len += padding_len;

    unsigned char ecb_ciphertext[len];
    unsigned char cbc_ciphertext[len];
    unsigned char cfb_ciphertext[len];
    unsigned char previous_block[AES_BLOCK_SIZE] = {0};

    // ECB Mode: Encrypt each block independently
    for (int i = 0; i < len; i += AES_BLOCK_SIZE) {
        aes_encrypt(plaintext + i, ecb_ciphertext + i, key);
    }
    
    // CBC Mode: XOR each block with previous ciphertext (or IV for first block)
    for (int i = 0; i < len; i += AES_BLOCK_SIZE) {
        // XOR with previous ciphertext (or IV for the first block)
        for (int j = 0; j < AES_BLOCK_SIZE; j++) {
            plaintext[i + j] ^= previous_block[j];
        }
        aes_encrypt(plaintext + i, cbc_ciphertext + i, key);
        memcpy(previous_block, cbc_ciphertext + i, AES_BLOCK_SIZE);
    }

    // CFB Mode: Encrypt previous ciphertext block and XOR with plaintext byte
    memcpy(previous_block, iv, AES_BLOCK_SIZE);
    for (int i = 0; i < len; i++) {
        unsigned char encrypted_block[AES_BLOCK_SIZE];
        aes_encrypt(previous_block, encrypted_block, key);
        cfb_ciphertext[i] = plaintext[i] ^ encrypted_block[0];
        memmove(previous_block, previous_block + 1, AES_BLOCK_SIZE - 1);
        previous_block[AES_BLOCK_SIZE - 1] = cfb_ciphertext[i];
    }

    // Print the results
    std::cout << "ECB Encrypted: ";
    for (int i = 0; i < len; i++) {
        printf("%02x", ecb_ciphertext[i]);
    }
    std::cout << std::endl;

    std::cout << "CBC Encrypted: ";
    for (int i = 0; i < len; i++) {
        printf("%02x", cbc_ciphertext[i]);
    }
    std::cout << std::endl;

    std::cout << "CFB Encrypted: ";
    for (int i = 0; i < len; i++) {
        printf("%02x", cfb_ciphertext[i]);
    }
    std::cout << std::endl;

    return 0;
}
