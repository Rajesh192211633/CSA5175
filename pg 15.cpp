#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 26
#define TOP_N 10

// English letter frequency (approximate)
double english_freq[SIZE] = {0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.020, 0.061, 0.070, 0.002, 
                              0.012, 0.067, 0.022, 0.060, 0.067, 0.028, 0.072, 0.010, 0.024, 0.061, 
                              0.091, 0.028, 0.020, 0.002, 0.020, 0.001};

// Decrypt the ciphertext by shifting each character by 'key'
void decrypt(char *ciphertext, int key, char *plaintext) {
    int i = 0;
    while (ciphertext[i] != '\0') {
        if (isalpha(ciphertext[i])) {
            plaintext[i] = ((ciphertext[i] - 'a' - key + SIZE) % SIZE) + 'a';
        } else {
            plaintext[i] = ciphertext[i]; // Keep non-alphabet characters unchanged
        }
        i++;
    }
    plaintext[i] = '\0';
}

int main() {
    char ciphertext[] = "khoor zruog"; // Example ciphertext: "hello world" shifted by 3
    char plaintext[100];
    double scores[SIZE];
    char possible_plaintexts[SIZE][100];
    
    printf("Ciphertext: %s\n", ciphertext);

    // Try all possible shifts from 0 to 25
    for (int key = 0; key < SIZE; key++) {
        int freq[SIZE] = {0};
        int length = 0;
        double score = 0.0;
        
        // Decrypt the ciphertext with the current key
        decrypt(ciphertext, key, plaintext);

        // Count frequency of each letter in the plaintext
        for (int i = 0; plaintext[i] != '\0'; i++) {
            if (isalpha(plaintext[i])) {
                freq[tolower(plaintext[i]) - 'a']++;
                length++;
            }
        }

        // Calculate the score based on the frequency distribution
        for (int i = 0; i < SIZE; i++) {
            score += (double)freq[i] / length * english_freq[i];
        }

        // Save score and corresponding plaintext
        scores[key] = score;
        strcpy(possible_plaintexts[key], plaintext);
    }

    // Sort based on score (descending order)
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = i + 1; j < SIZE; j++) {
            if (scores[i] < scores[j]) {
                // Swap scores
                double temp_score = scores[i];
                scores[i] = scores[j];
                scores[j] = temp_score;

                // Swap corresponding plaintexts
                char temp_plaintext[100];
                strcpy(temp_plaintext, possible_plaintexts[i]);
                strcpy(possible_plaintexts[i], possible_plaintexts[j]);
                strcpy(possible_plaintexts[j], temp_plaintext);
            }
        }
    }

    // Show the top N possible plaintexts
    int top_n = 3; // Set the number of top plaintexts to display
    printf("\nTop %d possible plaintexts based on letter frequency analysis:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        printf("Shift: %d, Plaintext: %s, Score: %.4f\n", i, possible_plaintexts[i], scores[i]);
    }

    return 0;
}

