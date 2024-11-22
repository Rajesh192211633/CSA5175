#include <stdio.h>
#include <string.h>

#define MAX_TEXT 1000

int main() {
    char ciphertext[MAX_TEXT], plaintext[MAX_TEXT], freq_order[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
    int freq[26] = {0}, used[26] = {0}, top_n, i, j, max_idx;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    printf("How many top plaintexts do you want? ");
    scanf("%d", &top_n);

    for (i = 0; ciphertext[i]; i++) {
        char ch = ciphertext[i];
        if (ch >= 'A' && ch <= 'Z') freq[ch - 'A']++;
        else if (ch >= 'a' && ch <= 'z') freq[ch - 'a']++;
    }

    char sorted[26];
    for (i = 0; i < 26; i++) {
        max_idx = -1;
        for (j = 0; j < 26; j++) {
            if (!used[j] && (max_idx == -1 || freq[j] > freq[max_idx])) {
                max_idx = j;
            }
        }
        if (max_idx != -1) {
            sorted[i] = max_idx + 'A';
            used[max_idx] = 1;
        }
    }

    for (int n = 0; n < top_n; n++) {
        char mapping[26];
        for (i = 0; i < 26; i++) {
            if (i + n < 26) mapping[sorted[i] - 'A'] = freq_order[i + n];
            else mapping[sorted[i] - 'A'] = '?';
        }

        for (i = 0; ciphertext[i]; i++) {
            char ch = ciphertext[i];
            if (ch >= 'A' && ch <= 'Z') plaintext[i] = mapping[ch - 'A'];
            else if (ch >= 'a' && ch <= 'z') plaintext[i] = mapping[ch - 'a'] + 32;
            else plaintext[i] = ch;
        }
        plaintext[strlen(ciphertext)] = '\0';

        printf("Plaintext %d: %s\n", n + 1, plaintext);
    }

    return 0;
}

