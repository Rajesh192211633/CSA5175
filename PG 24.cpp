#include <stdio.h>

int main() {
    int n = 3599;      // Public modulus
    int e = 31;        // Public exponent
    int p = 59, q = 61; // These are found by trial and error (p * q = 3599)
    int phi_n, d;
    int a = e, m = (p - 1) * (q - 1); // m = f(n) = (p - 1)(q - 1)
    int x1 = 1, x2 = 0, x3 = m, y1 = 0, y2 = 1, y3 = a;
    int q1, t1, t2, t3;

    // Step 1: Calculate f(n)
    phi_n = (p - 1) * (q - 1);  // f(n)

    // Step 2: Extended Euclidean algorithm to find modular inverse of e mod f(n)
    while (y3 != 1) {
        q1 = x3 / y3;
        t1 = x1 - q1 * y1;
        t2 = x2 - q1 * y2;
        t3 = x3 - q1 * y3;

        x1 = y1;
        x2 = y2;
        x3 = y3;

        y1 = t1;
        y2 = t2;
        y3 = t3;
    }

    // Step 3: If y3 is 1, then the inverse exists, and d = y2 mod f(n)
    if (y2 < 0) {
        d = y2 + phi_n;
    } else {
        d = y2;
    }

    // Step 4: Print the private key d
    printf("The private key d is: %d\n", d);

    return 0;
}
