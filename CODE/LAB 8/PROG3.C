#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

void findLCS(char X[], char Y[])
{
    int m = strlen(X);
    int n = strlen(Y);

    int **dp = (int **)malloc((m + 1) * sizeof(int *));

    for (int i = 0; i <= m; i++)
        dp[i] = (int *)malloc((n + 1) * sizeof(int));

   
    for (int i = 0; i <= m; i++)
        dp[i][0] = 0;

    for (int j = 0; j <= n; j++)
        dp[0][j] = 0;

    
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    int lcsLength = dp[m][n];

   
    char *lcs = (char *)malloc((lcsLength + 1) * sizeof(char));

    lcs[lcsLength] = '\0';

    
    int i = m;
    int j = n;
    int index = lcsLength - 1;

    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index] = X[i - 1];
            index--;
            i--;
            j--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("\nLength of LCS = %d\n", lcsLength);
    printf("Longest Common Subsequence = %s\n", lcs);

    
    free(lcs);

    for (i = 0; i <= m; i++)
        free(dp[i]);

    free(dp);
}

int main()
{
    char X[100], Y[100];

    printf("Enter first sequence: ");
    scanf("%99s", X);

    printf("Enter second sequence: ");
    scanf("%99s", Y);

    findLCS(X, Y);

    return 0;
}