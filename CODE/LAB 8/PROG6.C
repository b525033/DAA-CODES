#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int min3(int a, int b, int c)
{
    int min = a;

    if (b < min)
        min = b;

    if (c < min)
        min = c;

    return min;
}

void printTraceback(char A[], char B[], int dp[MAX][MAX])
{
    int i = strlen(A);
    int j = strlen(B);

    
    char operations[3 * MAX][150];
    int count = 0;

    while (i > 0 || j > 0)
    {
        
        if (i > 0 && j > 0 && A[i - 1] == B[j - 1])
        {
            i--;
            j--;
        }

        else if (i > 0 && j > 0 &&
                 dp[i][j] == dp[i - 1][j - 1] + 1)
        {
            sprintf(operations[count],
                    "Substitute '%c' with '%c'",
                    A[i - 1], B[j - 1]);

            count++;
            i--;
            j--;
        }

        
        else if (i > 0 &&
                 dp[i][j] == dp[i - 1][j] + 1)
        {
            sprintf(operations[count],
                    "Delete '%c'",
                    A[i - 1]);

            count++;
            i--;
        }

        
        else
        {
            sprintf(operations[count],
                    "Insert '%c'",
                    B[j - 1]);

            count++;
            j--;
        }
    }

    printf("\nTraceback Operations:\n");

    
    for (int k = count - 1; k >= 0; k--)
    {
        printf("%d. %s\n", count - k, operations[k]);
    }
}

int editDistance(char A[], char B[])
{
    int m = strlen(A);
    int n = strlen(B);

    int dp[MAX][MAX];

    
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;

    for (int j = 0; j <= n; j++)
        dp[0][j] = j;

    
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (A[i - 1] == B[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + min3(
                    dp[i - 1][j],     // deletion
                    dp[i][j - 1],     // insertion
                    dp[i - 1][j - 1]  // substitution
                );
            }
        }
    }

    printf("\nDP Table:\n\n");

    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            printf("%3d ", dp[i][j]);
        }
        printf("\n");
    }

    printf("\nMinimum Edit Distance = %d\n", dp[m][n]);

    printTraceback(A, B, dp);

    return dp[m][n];
}

int main()
{
    char A[MAX], B[MAX];

    printf("Enter first string: ");
    scanf("%99s", A);

    printf("Enter second string: ");
    scanf("%99s", B);

    editDistance(A, B);

    return 0;
}