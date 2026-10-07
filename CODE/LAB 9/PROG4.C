#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;




void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}




void heapifyUp(MinHeap *heap, int index)
{
    while (index > 0) {

        int parent = (index - 1) / 2;

        if (heap->data[parent] <= heap->data[index])
            break;

        swap(&heap->data[parent],
             &heap->data[index]);

        index = parent;
    }
}


void heapifyDown(MinHeap *heap, int index)
{
    while (1) {

        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;

        if (left < heap->size &&
            heap->data[left] < heap->data[smallest])
            smallest = left;

        if (right < heap->size &&
            heap->data[right] < heap->data[smallest])
            smallest = right;

        if (smallest == index)
            break;

        swap(&heap->data[index],
             &heap->data[smallest]);

        index = smallest;
    }
}



void insert(MinHeap *heap, int value)
{
    heap->data[heap->size] = value;

    heapifyUp(heap, heap->size);

    heap->size++;
}




int extractMin(MinHeap *heap)
{
    int minimum = heap->data[0];

    heap->size--;

    if (heap->size > 0) {

        heap->data[0] =
            heap->data[heap->size];

        heapifyDown(heap, 0);
    }

    return minimum;
}



long long minimumConnectionCost(int lengths[], int n)
{
    MinHeap heap;

    heap.size = 0;
    heap.capacity = n;

    heap.data =
        (int *)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        insert(&heap, lengths[i]);

    long long totalCost = 0;

    while (heap.size > 1) {

        
        int x = extractMin(&heap);
        int y = extractMin(&heap);

        int newStick = x + y;

       
        totalCost += newStick;

        printf("Connect %d + %d = %d, cost = %d\n",
               x, y, newStick, newStick);

       
        insert(&heap, newStick);
    }

    free(heap.data);

    return totalCost;
}



int main()
{
    int n;

    printf("Enter number of sticks: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of sticks must be positive.\n");
        return 1;
    }

    int *lengths =
        (int *)malloc(n * sizeof(int));

    printf("Enter stick lengths:\n");

    for (int i = 0; i < n; i++) {
        scanf("%d", &lengths[i]);

        if (lengths[i] <= 0) {
            printf("Stick lengths must be positive.\n");
            free(lengths);
            return 1;
        }
    }

    printf("\nConnection steps:\n");

    long long answer =
        minimumConnectionCost(lengths, n);

    printf("\nMinimum total connection cost = %lld\n",
           answer);

    free(lengths);

    return 0;
}