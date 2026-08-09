#include <stdio.h>
#include <stdlib.h>

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

    /* Input arrays */
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

    int currentK = k;
    int currentSize = n;

    /* Continue until only one array remains */
    while (currentK > 1)
    {
        int newK = (currentK + 1) / 2;

        int **newArrays =
            (int **)malloc(newK * sizeof(int *));

        int index = 0;

        /* Merge arrays in pairs */
        for (i = 0; i < currentK; i += 2)
        {
            if (i + 1 < currentK)
            {
                newArrays[index] =
                    (int *)malloc(2 * currentSize * sizeof(int));

                merge(arrays[i], currentSize,
                      arrays[i + 1], currentSize,
                      newArrays[index]);

                index++;
            }
            else
            {
                /* If number of arrays is odd */
                newArrays[index] =
                    (int *)malloc(currentSize * sizeof(int));

                for (j = 0; j < currentSize; j++)
                {
                    newArrays[index][j] =
                        arrays[i][j];
                }

                index++;
            }
        }

        /* Free old arrays */
        for (i = 0; i < currentK; i++)
        {
            free(arrays[i]);
        }

        free(arrays);

        arrays = newArrays;
        currentK = newK;
        currentSize = currentSize * 2;
    }

    /* Display final sorted array */
    printf("\nSorted merged array:\n");

    for (i = 0; i < k * n; i++)
    {
        printf("%d ", arrays[0][i]);
    }

    printf("\n");

    free(arrays[0]);
    free(arrays);

    return 0;
}