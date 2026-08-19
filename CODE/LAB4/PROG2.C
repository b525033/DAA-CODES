#include <stdio.h>
#include <stdlib.h>


void merge(int arr[], int left, int mid, int right)
{
    int i = left;
    int j = mid + 1;
    int k = 0;

    int temp[right - left + 1];

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; i++, k++)
        arr[i] = temp[k];
}


void mergeSort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}


int binarySearch(int arr[], int n, int target)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == target)
            return 1;

        if (arr[mid] < target)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return 0;
}

int main()
{
    int n, x;
    int i;
    int found = 0;

    printf("Enter the size of each set: ");
    scanf("%d", &n);

    int S1[n], S2[n];

    printf("Enter elements of S1:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &S1[i]);

    printf("Enter elements of S2:\n");
    for (i = 0; i < n; i++)
        scanf("%d", &S2[i]);

    printf("Enter x: ");
    scanf("%d", &x);

    
    mergeSort(S2, 0, n - 1);

    
    for (i = 0; i < n; i++)
    {
        int target = x - S1[i];

        if (binarySearch(S2, n, target))
        {
            printf("\nPair found: %d + %d = %d\n",
                   S1[i], target, x);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nNo pair exists whose sum is %d.\n", x);
    }

    return 0;
}