#include <stdio.h>
#include <stdlib.h>
#include <time.h>


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


void quickSort(int a[], int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);

        quickSort(a, low, p - 1);
        quickSort(a, p + 1, high);
    }
}

int main()
{
    int n, i;
    FILE *fp;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n];

    
    srand(time(NULL));

    printf("\nRandom elements:\n");

    for (i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
        printf("%d ", a[i]);
    }

    
    fp = fopen("numbers.txt", "w");

    if (fp == NULL)
    {
        printf("\nError opening file.\n");
        return 1;
    }

    
    for (i = 0; i < n; i++)
    {
        fprintf(fp, "%d ", a[i]);
    }

    fclose(fp);

    
    fp = fopen("numbers.txt", "r");

    if (fp == NULL)
    {
        printf("\nError opening file.\n");
        return 1;
    }

    
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%d", &a[i]);
    }

    fclose(fp);

    
    quickSort(a, 0, n - 1);

    printf("\n\nSorted elements:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n\nElements are stored in file: numbers.txt\n");

    return 0;
}