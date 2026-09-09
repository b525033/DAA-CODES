#include <stdio.h>

int main() {
    int n;
    long long totalCoins, minimumMoves;

    printf("Enter the number of rows in the coin triangle: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input! Number of rows must be positive.\n");
        return 1;
    }

    
    totalCoins = (long long)n * (n + 1) / 2;

    
    minimumMoves = (totalCoins + 1) / 3;

    printf("\nNumber of rows = %d\n", n);
    printf("Total number of coins = %lld\n", totalCoins);
    printf("Minimum number of moves required = %lld\n",
           minimumMoves);

    return 0;
}