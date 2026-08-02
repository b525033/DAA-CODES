#include <stdio.h>

int findTransition(int arr[], int n)
{
    int low = 0, high = n - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == 1 && (mid == 0 || arr[mid - 1] == 0))
            return mid;   // Transition point found

        if (arr[mid] == 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1; // No transition found
}

int main()
{
    int arr[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1};
    int n = sizeof(arr) / sizeof(arr[0]);

    int index = findTransition(arr, n);

    if (index != -1)
    {
        printf("Transition point is at index %d\n", index);
        printf("0 changes to 1 between index %d and %d\n", index - 1, index);
    }
    else
    {
        printf("No transition found.\n");
    }

    return 0;
}