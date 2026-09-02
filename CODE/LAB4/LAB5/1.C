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
    int n, i;
    int median1, median2;
    double median;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter %d numbers:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &a[i]);

    if (n % 2 == 1)
    {
        
        median = quickSelect(a, 0, n - 1, n / 2);
    }
    else
    {
        
        median1 = quickSelect(a, 0, n - 1, n / 2 - 1);
        median2 = quickSelect(a, 0, n - 1, n / 2);

        median = (median1 + median2) / 2.0;
    }

    printf("Median = %.2f\n", median);

    return 0;
}