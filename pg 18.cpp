#include <stdio.h>
#include <string.h>

#define KEY_SIZE 56       // Initial key size
#define SUBKEY_SIZE 48    // Subkey size
#define ROUNDS 16         // Number of rounds

int main() {
    char initial_key[KEY_SIZE + 1] = "11110000111100001111000011110000111100001111000011110000"; // 56-bit initial key
    char subkeys[ROUNDS][SUBKEY_SIZE + 1];
    int left_permutation[28] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27};
    int right_permutation[28] = {28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55};
    int shift_schedule[ROUNDS] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    char left_half[28], right_half[28];
    int i, j, shift;

    // Split the initial key into two halves
    strncpy(left_half, initial_key, 28);
    left_half[28] = '\0';
    strncpy(right_half, initial_key + 28, 28);
    right_half[28] = '\0';

    // Generate 16 subkeys
    for (i = 0; i < ROUNDS; i++) {
        shift = shift_schedule[i];

        // Perform left shift for the left half
        char temp[28];
        strncpy(temp, left_half + shift, 28 - shift);
        strncpy(temp + (28 - shift), left_half, shift);
        strncpy(left_half, temp, 28);

        // Perform left shift for the right half
        strncpy(temp, right_half + shift, 28 - shift);
        strncpy(temp + (28 - shift), right_half, shift);
        strncpy(right_half, temp, 28);

        // Combine halves to create the subkey
        for (j = 0; j < 24; j++) {
            subkeys[i][j] = left_half[left_permutation[j]];
            subkeys[i][j + 24] = right_half[right_permutation[j] - 28];
        }
        subkeys[i][SUBKEY_SIZE] = '\0';

        printf("Subkey %d: %s\n", i + 1, subkeys[i]);
    }

    return 0;
}

