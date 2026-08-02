#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int hasDuplicate(int arr[], int n)
{
    qsort(arr, n, sizeof(int), compare);

    for (int i = 1; i < n; i++)
    {
        if (arr[i] == arr[i - 1])
            return 1;
    }
    return 0;
}

int main()
{
    int n = 10;
    int arr[10];

    srand(time(NULL));

    printf("Random Numbers:\n");
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 20;   // Random numbers from 0 to 19
        printf("%d ", arr[i]);
    }

    printf("\n");

    if (hasDuplicate(arr, n))
        printf("Duplicate elements found.\n");
    else
        printf("No duplicate elements found.\n");

    return 0;
} 