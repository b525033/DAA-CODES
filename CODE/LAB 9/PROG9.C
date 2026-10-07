#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long weight;
    int index;
} Weight;


void printTree(int **root, int i, int j, int depth,
               Weight weights[]) {
    if (i > j)
        return;

    if (i == j) {
        printf("Weight %lld (index %d) -> depth %d\n",
               weights[i].weight,
               weights[i].index,
               depth);
        return;
    }

    int k = root[i][j];

    printf("Subtree [%d..%d], split after index %d\n",
           i, j, k);

    printTree(root, i, k, depth + 1, weights);
    printTree(root, k + 1, j, depth + 1, weights);
}


long long calculateCost(int **root, int i, int j,
                        int depth, Weight weights[]) {
    if (i > j)
        return 0;

    if (i == j)
        return weights[i].weight * depth;

    int k = root[i][j];

    return calculateCost(root, i, k, depth + 1, weights)
         + calculateCost(root, k + 1, j, depth + 1, weights);
}


long long optimalAlphabeticTree(Weight weights[], int n,
                                int **root) {
    long long prefix[n + 1];

    prefix[0] = 0;

    
    for (int i = 1; i <= n; i++) {
        prefix[i] = prefix[i - 1] + weights[i - 1].weight;
    }

    long long **dp = malloc(n * sizeof(long long *));

    for (int i = 0; i < n; i++)
        dp[i] = malloc(n * sizeof(long long));

    
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
        root[i][i] = -1;
    }

    for (int length = 2; length <= n; length++) {

        for (int i = 0; i + length <= n; i++) {

            int j = i + length - 1;

            dp[i][j] = LLONG_MAX;

            
            long long sum = prefix[j + 1] - prefix[i];

            
            for (int k = i; k < j; k++) {

                long long cost =
                    dp[i][k] +
                    dp[k + 1][j] +
                    sum;

                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    root[i][j] = k;
                }
            }
        }
    }

    long long answer = dp[0][n - 1];

    for (int i = 0; i < n; i++)
        free(dp[i]);

    free(dp);

    return answer;
}

int main() {
    int n;

    printf("Enter number of weights: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of weights must be positive.\n");
        return 1;
    }

    Weight weights[n];

    printf("Enter the weights in alphabetic order:\n");

    for (int i = 0; i < n; i++) {
        scanf("%lld", &weights[i].weight);
        weights[i].index = i + 1;

        if (weights[i].weight < 0) {
            printf("Weights must be non-negative.\n");
            return 1;
        }
    }

    
    int **root = malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++)
        root[i] = malloc(n * sizeof(int));

    long long minimumCost =
        optimalAlphabeticTree(weights, n, root);

    printf("\nMinimum weighted path length = %lld\n",
           minimumCost);

    printf("\nOptimal alphabetic tree:\n");

    printTree(root, 0, n - 1, 0, weights);

    printf("\nDepths and weighted costs:\n");

    long long total = calculateCost(root, 0, n - 1, 0, weights);

    for (int i = 0; i < n; i++) {
        
    }

    printf("Total cost = %lld\n", total);

    for (int i = 0; i < n; i++)
        free(root[i]);

    free(root);

    return 0;
}