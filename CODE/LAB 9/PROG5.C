#include <stdio.h>
#include <stdlib.h>

int minimumCandies(int ratings[], int n, int candies[])
{
    int total = 0;

    
    for (int i = 0; i < n; i++) {
        candies[i] = 1;
    }

    
    for (int i = 1; i < n; i++) {

        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    
    for (int i = n - 2; i >= 0; i--) {

        if (ratings[i] > ratings[i + 1]) {

            if (candies[i] < candies[i + 1] + 1) {
                candies[i] = candies[i + 1] + 1;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        total += candies[i];
    }

    return total;
}


int main()
{
    int n;

    printf("Enter number of children: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of children must be positive.\n");
        return 1;
    }

    int *ratings =
        (int *)malloc(n * sizeof(int));

    int *candies =
        (int *)malloc(n * sizeof(int));

    if (ratings == NULL || candies == NULL) {
        printf("Memory allocation failed.\n");
        free(ratings);
        free(candies);
        return 1;
    }

    printf("Enter ratings:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &ratings[i]);
    }

    int total =
        minimumCandies(ratings, n, candies);

    printf("\nRatings: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", ratings[i]);
    }

    printf("\nCandies: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", candies[i]);
    }

    printf("\n\nMinimum total candies = %d\n",
           total);

    free(ratings);
    free(candies);

    return 0;
}