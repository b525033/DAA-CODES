#include <stdio.h>
#include <stdlib.h>

long long totalCost = 0;
int reversalCount = 0;

 
void reverseRange(int a[], int l, int r)
{
    if (l >= r)
        return;

    int length = r - l + 1;

    int i = l;
    int j = r;

    while (i < j)
    {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;

        i++;
        j--;
    }

    reversalCount++;
    totalCost += length;

    printf("  Reverse(%d, %d), cost = %d\n",
           l + 1, r + 1, length);
}

void stablePartition(int a[], int l, int r, int pivot)
{
    if (l >= r)
        return;

    int mid = (l + r) / 2;

    stablePartition(a, l, mid, pivot);
    stablePartition(a, mid + 1, r, pivot);

    

    int firstLarge = l;

    while (firstLarge <= mid && a[firstLarge] <= pivot)
        firstLarge++;

    int secondSmall = mid + 1;

    while (secondSmall <= r && a[secondSmall] <= pivot)
        secondSmall++;

    
    if (firstLarge > mid || secondSmall == mid + 1)
        return;

    

    reverseRange(a, firstLarge, mid);

    reverseRange(a, mid + 1, secondSmall - 1);

    reverseRange(a, firstLarge, secondSmall - 1);
}

int findPartitionPoint(int a[], int l, int r, int pivot)
{
    int i;

    for (i = l; i <= r; i++)
    {
        if (a[i] > pivot)
            return i;
    }

    return r + 1;
}

void reversalSort(int a[], int l, int r,
                  int minValue, int maxValue)
{
    if (l >= r || minValue >= maxValue)
        return;

    int pivot = (minValue + maxValue) / 2;

    printf("\nPartitioning positions %d to %d "
           "around pivot value %d\n",
           l + 1, r + 1, pivot);

    stablePartition(a, l, r, pivot);

    int split = findPartitionPoint(a, l, r, pivot);

    printf("After partition: ");
    for (int i = l; i <= r; i++)
        printf("%d ", a[i]);
    printf("\n");


    reversalSort(a, l, split - 1,
                 minValue, pivot);

    reversalSort(a, split, r,
                 pivot + 1, maxValue);
}

void printArray(int a[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", a[i]);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int *a = malloc(n * sizeof(int));

    printf("Enter permutation of 1 to %d:\n", n);

    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("\nInitial permutation:\n");
    printArray(a, n);

    reversalSort(a, 0, n - 1, 1, n);

    printf("\nFinal sorted permutation:\n");
    printArray(a, n);

    printf("\nNumber of reversals = %d\n", reversalCount);
    printf("Total reversal cost = %lld\n", totalCost);

    printf("\nRequired bound: O(n log^2 n)\n");

    free(a);

    return 0;
}