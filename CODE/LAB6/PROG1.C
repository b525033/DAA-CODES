#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int findMax(int a[], int n)
{
    int max = a[0];

    for (int i = 1; i < n; i++)
        if (a[i] > max)
            max = a[i];

    return max;
}


void findLargestTwo(int a[], int n, int *largest, int *second)
{
    *largest = *second = -2147483648;

    for (int i = 0; i < n; i++)
    {
        if (a[i] > *largest)
        {
            *second = *largest;
            *largest = a[i];
        }
        else if (a[i] > *second && a[i] != *largest)
        {
            *second = a[i];
        }
    }
}

double findMean(int a[], int n)
{
    long long sum = 0;

    for (int i = 0; i < n; i++)
        sum += a[i];

    return (double)sum / n;
}


int compare(const void *x, const void *y)
{
    return (*(int *)x - *(int *)y);
}


double findMedian(int a[], int n)
{
    int *b = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    qsort(b, n, sizeof(int), compare);

    double median;

    if (n % 2 == 0)
        median = (b[n / 2 - 1] + b[n / 2]) / 2.0;
    else
        median = b[n / 2];

    free(b);
    return median;
}


double findStandardDeviation(int a[], int n)
{
    double mean = findMean(a, n);
    double sum = 0.0;

    for (int i = 0; i < n; i++)
    {
        double difference = a[i] - mean;
        sum += difference * difference;
    }

    return sqrt(sum / n);
}


int findMode(int a[], int n)
{
    int mode = a[0];
    int maxCount = 1;

    for (int i = 0; i < n; i++)
    {
        int count = 0;

        for (int j = 0; j < n; j++)
        {
            if (a[j] == a[i])
                count++;
        }

        if (count > maxCount)
        {
            maxCount = count;
            mode = a[i];
        }
    }

    return mode;
}


int removeDuplicates(int a[], int n)
{
    int newSize = 0;

    for (int i = 0; i < n; i++)
    {
        int duplicate = 0;

        for (int j = 0; j < newSize; j++)
        {
            if (a[i] == a[j])
            {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate)
        {
            a[newSize] = a[i];
            newSize++;
        }
    }

    return newSize;
}


void reverseArray(int a[], int n)
{
    int i = 0, j = n - 1;

    while (i < j)
    {
        int temp = a[i];
        a[i] = a[j];
        a[j] = temp;

        i++;
        j--;
    }
}


void partitionArray(int a[], int n, int pivot)
{
    int i = 0, j = n - 1;

    while (i <= j)
    {
        while (i < n && a[i] >= pivot)
            i++;

        while (j >= 0 && a[j] < pivot)
            j--;

        if (i < j)
        {
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
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

    printf("Enter %d integers:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    
    printf("\n(i) Maximum = %d\n", findMax(a, n));

    
    int largest, second;
    findLargestTwo(a, n, &largest, &second);

    printf("(ii) Largest = %d, Second Largest = %d\n",
           largest, second);

    
    printf("(iii) Mean = %.2f\n", findMean(a, n));

    
    printf("(iv) Median = %.2f\n", findMedian(a, n));

    
    printf("(v) Standard Deviation = %.2f\n",
           findStandardDeviation(a, n));

   
    printf("(vi) Mode = %d\n", findMode(a, n));

    
    int *b = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    int newSize = removeDuplicates(b, n);

    printf("(vii) After removing duplicates: ");
    printArray(b, newSize);

    
    for (int i = 0; i < n; i++)
        b[i] = a[i];

    reverseArray(b, n);

    printf("(viii) Reversed array: ");
    printArray(b, n);

    for (int i = 0; i < n; i++)
        b[i] = a[i];

    int pivot;
    printf("(ix) Enter pivot element: ");
    scanf("%d", &pivot);

    partitionArray(b, n, pivot);

    printf("Partitioned array: ");
    printArray(b, n);

    free(a);
    free(b);

    return 0;
}