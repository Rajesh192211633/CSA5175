#include <stdio.h>
#include <string.h>


void calculateFrequency(const char *ciphertext, int *freq) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 32 && ciphertext[i] <= 126) { 
            freq[ciphertext[i] - 32]++;
        }
    }
}

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                        "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*;"
                        "4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
                        "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    int freq[95] = {0}; 

    calculateFrequency(ciphertext, freq);

    printf("Character frequency analysis:\n");
    for (int i = 0; i < 95; i++) {
        if (freq[i] > 0) {
            printf("'%c': %d\n", i + 32, freq[i]);
        }
    }

    char mapping[95] = {0}; 
    mapping['‡' - 32] = 'e'; 
    mapping['†' - 32] = 't'; 
    mapping['(' - 32] = 'h'; 

    char plaintext[strlen(ciphertext) + 1];
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 32 && ciphertext[i] <= 126 && mapping[ciphertext[i] - 32] != 0) {
            plaintext[i] = mapping[ciphertext[i] - 32];
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[strlen(ciphertext)] = '\0';

    
    printf("\nDecrypted text (partially):\n%s\n", plaintext);

    return 0;
}
