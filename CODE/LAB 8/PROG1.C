#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minCoins(int coins[], int n, int V)
{
    int dp[V + 1];

   

    for (int i = 1; i <= V; i++)
        dp[i] = INT_MAX;

    
    for (int amount = 1; amount <= V; amount++)
    {
        for (int j = 0; j < n; j++)
        {
            if (coins[j] <= amount && dp[amount - coins[j]] != INT_MAX)
            {
                int candidate = dp[amount - coins[j]] + 1;

                if (candidate < dp[amount])
                    dp[amount] = candidate;
            }
        }
    }

    if (dp[V] == INT_MAX)
        return -1;

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

    int result = minCoins(coins, n, V);

    if (result == -1)
        printf("Minimum number of coins = -1\n");
    else
        printf("Minimum number of coins = %d\n", result);

    return 0;
}