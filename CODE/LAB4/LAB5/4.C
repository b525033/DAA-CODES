#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    
    if (left < n && a[left] > a[largest])
        largest = left;

    
    if (right < n && a[right] > a[largest])
        largest = right;

    
    if (largest != i)
    {
        swap(&a[i], &a[largest]);

        
        heapify(a, n, largest);
    }
}


void heapSort(int a[], int n)
{
    int i;

    
    for (i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    
    for (i = n - 1; i > 0; i--)
    {
        
        swap(&a[0], &a[i]);

        
        heapify(a, i, 0);
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

    printf("\nRandomly generated elements:\n");

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

    
    heapSort(a, n);

    printf("\n\nSorted elements using Heap Sort:\n");

    for (i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n\nNumbers are stored in file: numbers.txt\n");

    return 0;
}