#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10

// Bubble Sort with Early Termination
int bubbleSortEarly(int a[], int n) {
    int i, j, temp, swapped;
    int comparisons = 0;

    for(i = 0; i < n - 1; i++) {
        swapped = 0;
        for(j = 0; j < n - i - 1; j++) {
            comparisons++;
            if(a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = 1;
            }
        }
        if(swapped == 0)
            break;
    }
    return comparisons;
}

// Bubble Sort without Early Termination
int bubbleSortNormal(int a[], int n) {
    int i, j, temp;
    int comparisons = 0;

    for(i = 0; i < n - 1; i++) {
        for(j = 0; j < n - i - 1; j++) {
            comparisons++;
            if(a[j] > a[j + 1]) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    return comparisons;
}

int main() {
    int arr1[SIZE], arr2[SIZE];
    int i;

    srand(time(NULL));

    printf("Random Array:\n");
    for(i = 0; i < SIZE; i++) {
        arr1[i] = rand() % 100;
        arr2[i] = arr1[i];
        printf("%d ", arr1[i]);
    }

    printf("\n\n");

    int earlyComp = bubbleSortEarly(arr1, SIZE);
    int normalComp = bubbleSortNormal(arr2, SIZE);

    printf("Sorted Array:\n");
    for(i = 0; i < SIZE; i++)
        printf("%d ", arr1[i]);

    printf("\n\n");
    printf("Comparisons (Early Termination) = %d\n", earlyComp);
    printf("Comparisons (Normal Bubble Sort) = %d\n", normalComp);

    return 0;
}