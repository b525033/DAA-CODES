#include <stdio.h>
#include <stdlib.h>

typedef long long ll;



typedef struct {
    ll *data;
    int size;
    int capacity;
} MaxHeap;


void swap(ll *a, ll *b)
{
    ll temp = *a;
    *a = *b;
    *b = temp;
}



void heapifyUp(MaxHeap *heap, int index)
{
    while (index > 0) {

        int parent = (index - 1) / 2;

        if (heap->data[parent] >= heap->data[index])
            break;

        swap(&heap->data[parent],
             &heap->data[index]);

        index = parent;
    }
}



void heapifyDown(MaxHeap *heap, int index)
{
    while (1) {

        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < heap->size &&
            heap->data[left] >
            heap->data[largest])
            largest = left;

        if (right < heap->size &&
            heap->data[right] >
            heap->data[largest])
            largest = right;

        if (largest == index)
            break;

        swap(&heap->data[index],
             &heap->data[largest]);

        index = largest;
    }
}



void insertHeap(MaxHeap *heap, ll value)
{
    heap->data[heap->size] = value;

    heapifyUp(heap, heap->size);

    heap->size++;
}

ll extractMax(MaxHeap *heap)
{
    ll maximum = heap->data[0];

    heap->size--;

    if (heap->size > 0) {

        heap->data[0] =
            heap->data[heap->size];

        heapifyDown(heap, 0);
    }

    return maximum;
}


ll minimumDeviation(ll A[], int n)
{
    MaxHeap heap;

    heap.data =
        (ll *)malloc(n * sizeof(ll));

    heap.size = 0;
    heap.capacity = n;

    ll minimum = __LONG_LONG_MAX__;

    
    for (int i = 0; i < n; i++) {

        if (A[i] % 2 != 0)
            A[i] *= 2;

        if (A[i] < minimum)
            minimum = A[i];

        insertHeap(&heap, A[i]);
    }

    ll answer =
        extractMax(&heap) - minimum;

    
    while (heap.size > 0) {

        ll maximum = extractMax(&heap);

        
        if (maximum % 2 != 0) {
            ll currentDeviation =
                maximum - minimum;

            if (currentDeviation < answer)
                answer = currentDeviation;

            break;
        }

        
        maximum /= 2;

        
        if (maximum < minimum)
            minimum = maximum;

        
        ll currentDeviation =
            maximum - minimum;

        if (currentDeviation < answer)
            answer = currentDeviation;

        
        insertHeap(&heap, maximum);
    }

    free(heap.data);

    return answer;
}



int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of elements must be positive.\n");
        return 1;
    }

    ll *A =
        (ll *)malloc(n * sizeof(ll));

    if (A == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter positive integers:\n");

    for (int i = 0; i < n; i++) {

        scanf("%lld", &A[i]);

        if (A[i] <= 0) {
            printf("All elements must be positive.\n");
            free(A);
            return 1;
        }
    }

    ll answer =
        minimumDeviation(A, n);

    printf("\nMinimum deviation = %lld\n",
           answer);

    free(A);

    return 0;
}