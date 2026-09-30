#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int longestIncreasingSubsequence(int A[], int n)
{
    
    int *dp = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        dp[i] = 1;

    
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[j] < A[i])
            {
                dp[i] = max(dp[i], dp[j] + 1);
            }
        }
    }

    
    int result = dp[0];

    for (int i = 1; i < n; i++)
    {
        if (dp[i] > result)
            result = dp[i];
    }

    free(dp);

    return result;
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *A = (int *)malloc(n * sizeof(int));

    printf("Enter the elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &A[i]);

    int result = longestIncreasingSubsequence(A, n);

    printf("Length of Longest Increasing Subsequence = %d\n", result);

    free(A);

    return 0;
}