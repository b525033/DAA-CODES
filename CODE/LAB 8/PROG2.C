#include <stdio.h>
#include <stdlib.h>

long long countWays(int coins[], int n, int V)
{
    
    long long dp[V + 1];

   
    for (int j = 0; j <= V; j++)
        dp[j] = 0;

   
    dp[0] = 1;

    
    for (int i = 0; i < n; i++)
    {
        for (int j = coins[i]; j <= V; j++)
        {
            dp[j] = dp[j] + dp[j - coins[i]];
        }
    }

    return dp[V];
}

int main()
{
    int n, V;

    printf("Enter number of coin denominations: ");
    scanf("%d", &n);

    int coins[n];

    printf("Enter the coin denominations: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter target amount: ");
    scanf("%d", &V);

    long long result = countWays(coins, n, V);

    printf("Total number of combinations = %lld\n", result);

    return 0;
}