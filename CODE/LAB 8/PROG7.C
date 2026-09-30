#include <stdio.h>
#include <stdlib.h>

void rodCutting(int n, int price[]) {
    int *dp = (int *)malloc((n + 1) * sizeof(int));
    int *first = (int *)malloc((n + 1) * sizeof(int));

    dp[0] = 0;
    first[0] = 0;

    
    for (int i = 1; i <= n; i++) {
        dp[i] = -1;

        for (int j = 1; j <= i; j++) {
            int revenue = price[j] + dp[i - j];

            if (revenue > dp[i]) {
                dp[i] = revenue;
                first[i] = j;
            }
        }
    }

   
    printf("\nMaximum Revenue = %d\n", dp[n]);

    printf("Optimal Pieces = ");

    int length = n;
    while (length > 0) {
        printf("%d", first[length]);
        length -= first[length];

        if (length > 0)
            printf(" + ");
    }

    printf("\n");

    
    printf("\nDP Table:\n");
    printf("Length : ");
    for (int i = 0; i <= n; i++)
        printf("%4d", i);

    printf("\nRevenue: ");
    for (int i = 0; i <= n; i++)
        printf("%4d", dp[i]);

    printf("\n");

    free(dp);
    free(first);
}

int main() {
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    
    int *price = (int *)malloc((n + 1) * sizeof(int));

    price[0] = 0;

    printf("Enter prices for lengths 1 to %d:\n", n);

    for (int i = 1; i <= n; i++) {
        printf("Price[%d] = ", i);
        scanf("%d", &price[i]);
    }

    rodCutting(n, price);

    free(price);

    return 0;
}