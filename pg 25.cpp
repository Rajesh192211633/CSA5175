#include <stdio.h>

int main() {
    int n = 3599;  // Modulus (n = p * q), for example
    int e = 31;    // Public key exponent
    int c = 678;   // Some ciphertext block that has a common factor with n

    // Step 1: Find the greatest common divisor (gcd) between ciphertext block and n
    int a = c, b = n;
    int gcd = 0;
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    gcd = a;

    printf("GCD(c, n) = %d\n", gcd);

    // Step 2: If gcd(c, n) is a factor of n, it could be p or q
    if (gcd != 1 && gcd != n) {
        printf("We found a factor: %d\n", gcd);

        // Step 3: Now we can calculate p and q
        int p = gcd;
        int q = n / p;

        printf("Factorized n = p * q -> p = %d, q = %d\n", p, q);

        // Step 4: Compute Euler's Totient function f(n) = (p - 1)(q - 1)
        int phi_n = (p - 1) * (q - 1);
        printf("Euler's Totient f(n) = %d\n", phi_n);

        // Step 5: Calculate the private key d using the modular inverse of e mod f(n)
        int d = 0, k = 1;
        while ((e * k) % phi_n != 1) {
            k++;
        }
        d = k;

        printf("Private key d = %d\n", d);
    } else {
        printf("No common factor found.\n");
    }

    return 0;
}
