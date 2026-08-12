#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Merge two sorted arrays */
void merge(int a[], int n1, int b[], int n2, int result[])
{
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2)
    {
        if (a[i] <= b[j])
            result[k++] = a[i++];
        else
            result[k++] = b[j++];
    }

    while (i < n1)
        result[k++] = a[i++];

    while (j < n2)
        result[k++] = b[j++];
}

/* Simple sorting function */
void sort(int a[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int k, n;
    int i, j;

    printf("Enter number of arrays (k): ");
    scanf("%d", &k);

    printf("Enter number of elements in each array (n): ");
    scanf("%d", &n);

    int **arrays = (int **)malloc(k * sizeof(int *));

    for (i = 0; i < k; i++)
    {
        arrays[i] = (int *)malloc(n * sizeof(int));

        printf("\nEnter elements of Array %d:\n", i + 1);

        for (j = 0; j < n; j++)
        {
            scanf("%d", &arrays[i][j]);
        }

        sort(arrays[i], n);
    }

    /* Start with first array */
    int currentSize = n;

    int *current = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        current[i] = arrays[0][i];

    /* Sequentially merge remaining arrays */
    for (i = 1; i < k; i++)
    {
        int newSize = currentSize + n;

        int *temp = (int *)malloc(newSize * sizeof(int));

        merge(current, currentSize,
              arrays[i], n,
              temp);

        free(current);

        current = temp;
        currentSize = newSize;
    }

    printf("\nSorted merged array:\n");

    for (i = 0; i < currentSize; i++)
    {
        printf("%d ", current[i]);
    }

    printf("\n");

    /* Free memory */
    free(current);

    for (i = 0; i < k; i++)
        free(arrays[i]);

    free(arrays);

    return 0;
}
