#include <stdio.h>

int main() {
    printf("Increasing order of growth for sufficiently large n:\n\n");

    printf("1. 1                -> O(1)\n");
    printf("2. log(n)           -> O(log n)\n");
    printf("3. sqrt(n)          -> O(sqrt(n))\n");
    printf("4. n                -> O(n)\n");
    printf("5. n log(n)         -> O(n log n)\n");
    printf("6. n^2              -> O(n^2)\n");
    printf("7. n^3              -> O(n^3)\n");
    printf("8. 2^n              -> O(2^n)\n");
    printf("9. n!               -> O(n!)\n");

    return 0;
}