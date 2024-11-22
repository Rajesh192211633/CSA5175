#include <stdio.h>
#include <string.h>

int main() {
    unsigned char key[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}; // 10-bit key
    unsigned char iv[8] = {1, 0, 1, 0, 1, 0, 1, 0}; // 8-bit IV (1010 1010)
    unsigned char plaintext[8] = {0, 1, 2, 3, 0, 0, 0, 0}; // 8-bit plaintext (0000 0001 0010 0011)
    unsigned char ciphertext[8], previous_block[8];
    
    unsigned char P10[10] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    unsigned char P4[4] = {2, 4, 3, 1};
    unsigned char IP[8] = {2, 6, 3, 1, 4, 8, 5, 7};
    unsigned char IP_INV[8] = {4, 1, 3, 5, 7, 2, 8, 6};
    unsigned char EP[8] = {4, 1, 3, 2, 4, 1, 3, 2};
    unsigned char S0[4][4] = {{1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 2, 0}};
    unsigned char S1[4][4] = {{0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 2}, {2, 1, 0, 3}};
    
    // Copy IV into previous block
    memcpy(previous_block, iv, 8);

    // Initial Permutation of plaintext
    unsigned char permute_output[8];
    for (int i = 0; i < 8; i++) {
        permute_output[i] = plaintext[IP[i] - 1];
    }

    unsigned char left[4], right[4];
    for (int i = 0; i < 4; i++) {
        left[i] = permute_output[i];
        right[i] = permute_output[i + 4];
    }

    // XOR right with previous block (IV for the first block)
    for (int i = 0; i < 4; i++) {
        right[i] ^= previous_block[i];
    }

    // Key generation: P10 and split into left and right keys
    unsigned char temp[10], left_key[5], right_key[5], shifted_key[10];
    for (int i = 0; i < 10; i++) {
        temp[i] = key[P10[i] - 1];
    }

    for (int i = 0; i < 5; i++) {
        left_key[i] = temp[i];
        right_key[i] = temp[i + 5];
    }

    // Left shift the keys
    shifted_key[0] = left_key[1]; shifted_key[1] = left_key[2]; shifted_key[2] = left_key[3];
    shifted_key[3] = left_key[4]; shifted_key[4] = right_key[0]; shifted_key[5] = right_key[1];
    shifted_key[6] = right_key[2]; shifted_key[7] = right_key[3]; shifted_key[8] = right_key[4];

    // F function and XOR with left part
    unsigned char temp_key[4], f_output[4];
    for (int i = 0; i < 4; i++) {
        temp_key[i] = shifted_key[P4[i] - 1];
    }

    for (int i = 0; i < 4; i++) {
        f_output[i] = left[i] ^ temp_key[i];
    }

    // Combine left and right parts, apply inverse permutation
    unsigned char final_output[8];
    for (int i = 0; i < 4; i++) {
        final_output[i] = f_output[i];
        final_output[i + 4] = right[i];
    }

    // Apply IP_INV to final output
    for (int i = 0; i < 8; i++) {
        ciphertext[i] = final_output[IP_INV[i] - 1];
    }

    // Print the resulting ciphertext
    printf("Ciphertext: ");
    for (int i = 0; i < 8; i++) {
        printf("%x", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
