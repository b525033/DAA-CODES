#include <stdio.h>
#include <limits.h>

#define MAX 20


long long m[MAX][MAX];
int s[MAX][MAX];


void printOptimalOrder(int i, int j)
{
    if (i == j)
    {
        printf("A%d", i);
        return;
    }

    printf("(");

    printOptimalOrder(i, s[i][j]);
    printOptimalOrder(s[i][j] + 1, j);

    printf(")");
}


void matrixChainOrder(int p[], int n)
{
    int i, j, k, L;
    long long cost;

    
    for (i = 1; i <= n; i++)
    {
        m[i][i] = 0;
    }

    
    for (L = 2; L <= n; L++)
    {
        for (i = 1; i <= n - L + 1; i++)
        {
            j = i + L - 1;

            m[i][j] = LLONG_MAX;

            for (k = i; k < j; k++)
            {
                cost = m[i][k]
                     + m[k + 1][j]
                     + (long long)p[i - 1] * p[k] * p[j];

                if (cost < m[i][j])
                {
                    m[i][j] = cost;
                    s[i][j] = k;
                }
            }
        }
    }
}

int main()
{
    int n, i;
    int p[MAX + 1];

    printf("Enter number of matrices: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX - 1)
    {
        printf("Invalid number of matrices!\n");
        return 1;
    }

    printf("\nEnter dimensions array (size %d):\n", n + 1);
    printf("Example: For matrices 10x20, 20x30, 30x40\n");
    printf("Enter: 10 20 30 40\n\n");

    for (i = 0; i <= n; i++)
    {
        scanf("%d", &p[i]);
    }

    matrixChainOrder(p, n);

    printf("\n----------------------------------------\n");
    printf("Minimum scalar multiplications = %lld\n",
           m[1][n]);

    printf("Optimal Parenthesization = ");
    printOptimalOrder(1, n);
    printf("\n");

    printf("----------------------------------------\n");

    return 0;
}