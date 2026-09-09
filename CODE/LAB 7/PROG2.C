#include <stdio.h>
#include <limits.h>

#define MAX_EGGS 100
#define MAX_FLOORS 1000


int max(int a, int b)
{
    return (a > b) ? a : b;
}


int eggDrop(int E, int F)
{
    int dp[MAX_EGGS + 1][MAX_FLOORS + 1];
    int e, f, x;

    for (e = 1; e <= E; e++)
    {
        dp[e][0] = 0;

        if (F >= 1)
            dp[e][1] = 1;
    }

    
    for (f = 1; f <= F; f++)
    {
        dp[1][f] = f;
    }

    
    for (e = 2; e <= E; e++)
    {
        for (f = 2; f <= F; f++)
        {
            dp[e][f] = INT_MAX;

           
            for (x = 1; x <= f; x++)
            {
                int breaks = dp[e - 1][x - 1];
                int survives = dp[e][f - x];

                int worstCase = 1 + max(breaks, survives);

                if (worstCase < dp[e][f])
                {
                    dp[e][f] = worstCase;
                }
            }
        }
    }

    return dp[E][F];
}

int main()
{
    int E, F;

    printf("Enter number of eggs: ");
    scanf("%d", &E);

    printf("Enter number of floors: ");
    scanf("%d", &F);

    if (E < 1 || E > MAX_EGGS ||
        F < 1 || F > MAX_FLOORS)
    {
        printf("Invalid input!\n");
        return 1;
    }

    printf("\nMinimum number of drops required = %d\n",
           eggDrop(E, F));

    return 0;
}