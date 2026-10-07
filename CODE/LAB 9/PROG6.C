#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET 256

typedef struct {
    char ch;
    int frequency;
} Character;


typedef struct {
    Character heap[ALPHABET];
    int size;
} MaxHeap;


void swap(Character *a, Character *b)
{
    Character temp = *a;
    *a = *b;
    *b = temp;
}



void heapifyUp(MaxHeap *h, int index)
{
    while (index > 0) {

        int parent = (index - 1) / 2;

        if (h->heap[parent].frequency >=
            h->heap[index].frequency)
            break;

        swap(&h->heap[parent], &h->heap[index]);

        index = parent;
    }
}



void heapifyDown(MaxHeap *h, int index)
{
    while (1) {

        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;

        if (left < h->size &&
            h->heap[left].frequency >
            h->heap[largest].frequency)
            largest = left;

        if (right < h->size &&
            h->heap[right].frequency >
            h->heap[largest].frequency)
            largest = right;

        if (largest == index)
            break;

        swap(&h->heap[index], &h->heap[largest]);

        index = largest;
    }
}



void insertHeap(MaxHeap *h, Character item)
{
    h->heap[h->size] = item;

    heapifyUp(h, h->size);

    h->size++;
}



Character extractMax(MaxHeap *h)
{
    Character result = h->heap[0];

    h->size--;

    if (h->size > 0) {
        h->heap[0] = h->heap[h->size];
        heapifyDown(h, 0);
    }

    return result;
}



typedef struct {
    Character item;
    int availableAt;
} WaitingItem;


char *rearrangeString(char *S, int K)
{
    int n = strlen(S);

    char *result =
        (char *)malloc((n + 1) * sizeof(char));

    if (result == NULL)
        return NULL;

    result[0] = '\0';

    
    if (K <= 1) {
        strcpy(result, S);
        return result;
    }

    
    int frequency[ALPHABET] = {0};

    for (int i = 0; i < n; i++) {
        frequency[(unsigned char)S[i]]++;
    }

    MaxHeap heap;
    heap.size = 0;

    for (int i = 0; i < ALPHABET; i++) {

        if (frequency[i] > 0) {

            Character c;

            c.ch = (char)i;
            c.frequency = frequency[i];

            insertHeap(&heap, c);
        }
    }

    
    WaitingItem *waiting =
        (WaitingItem *)malloc(
            n * sizeof(WaitingItem));

    if (waiting == NULL) {
        free(result);
        return NULL;
    }

    int front = 0;
    int rear = 0;

    for (int position = 0;
         position < n;
         position++) {

        
        while (front < rear &&
               waiting[front].availableAt <= position) {

            insertHeap(&heap,
                       waiting[front].item);

            front++;
        }

        
        if (heap.size == 0) {
            free(waiting);
            free(result);

            return NULL;
        }

        
        Character current =
            extractMax(&heap);

        result[position] = current.ch;

        current.frequency--;

        if (current.frequency > 0) {

            waiting[rear].item = current;
            waiting[rear].availableAt =
                position + K;

            rear++;
        }
    }

    result[n] = '\0';

    free(waiting);

    return result;
}




int validate(char *S, int K)
{
    int n = strlen(S);

    int last[ALPHABET];

    for (int i = 0; i < ALPHABET; i++)
        last[i] = -K;

    for (int i = 0; i < n; i++) {

        unsigned char c = S[i];

        /*
         * Equal characters must be at least K
         * positions apart.
         */
        if (i - last[c] < K)
            return 0;

        last[c] = i;
    }

    return 1;
}



int main()
{
    char S[1000];
    int K;

    printf("Enter string: ");
    scanf("%999s", S);

    printf("Enter K: ");
    scanf("%d", &K);

    if (K < 0) {
        printf("K must be non-negative.\n");
        return 1;
    }

    char *answer =
        rearrangeString(S, K);

    if (answer == NULL) {

        printf("\nRearrangement is impossible.\n");

    } else {

        printf("\nRearranged string: %s\n",
               answer);

        if (validate(answer, K))
            printf("Validation: VALID\n");
        else
            printf("Validation: INVALID\n");

        free(answer);
    }

    return 0;
}