#include <stdio.h>
#include <math.h>

int main() {
    // Factorial of 25 (approximation using logarithms)
    double log25Factorial = 0;
    for (int i = 1; i <= 25; i++) {
        log25Factorial += log2(i);
    }

    // Total possible keys
    double totalKeys = log25Factorial; // in base-2 exponent

    // Effectively unique keys
    double log5Factorial = 0;
    for (int i = 1; i <= 5; i++) {
        log5Factorial += log2(i);
    }
    double uniqueKeys = log25Factorial - 2 * log5Factorial; // Adjust for indistinguishable keys

    // Print results
    printf("Total possible keys: 2^%.1f\n", totalKeys);
    printf("Effectively unique keys: 2^%.1f\n", uniqueKeys);

    return 0;
}

