#include <stdio.h>


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


int partition(int a[], int low, int high)
{
    int pivot = a[high];
    int i = low - 1;
    int j;

    for (j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(&a[i], &a[j]);
        }
    }

    swap(&a[i + 1], &a[high]);

    return i + 1;
}


int quickSelect(int a[], int low, int high, int k)
{
    int pos;

    while (low <= high)
    {
        pos = partition(a, low, high);

        if (pos == k)
            return a[pos];

        else if (k < pos)
            high = pos - 1;

        else
            low = pos + 1;
    }

    return -1;
}

int main()
{
    int n, k, i, result;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter %d numbers:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Enter the value of k: ");
    scanf("%d", &k);

    if (k < 1 || k > n)
    {
        printf("Invalid value of k.\n");
        return 0;
    }

    
    result = quickSelect(a, 0, n - 1, k - 1);

    printf("The %dth smallest element is: %d\n", k, result);

    return 0;
}