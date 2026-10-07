#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SYMBOLS 256

typedef struct Node {
    char symbol;
    int frequency;
    int isLeaf;

    struct Node *left;
    struct Node *right;
} Node;

typedef struct {
    Node **data;
    int size;
    int capacity;
} MinHeap;

typedef struct {
    char symbol;
    int frequency;
    int length;
    unsigned long long code;
} Symbol;


Node *createNode(char symbol, int frequency, int isLeaf)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->symbol = symbol;
    node->frequency = frequency;
    node->isLeaf = isLeaf;
    node->left = NULL;
    node->right = NULL;

    return node;
}


void swap(Node **a, Node **b)
{
    Node *temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap *heap, int index)
{
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap->data[parent]->frequency <=
            heap->data[index]->frequency)
            break;

        swap(&heap->data[parent], &heap->data[index]);

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
            heap->data[left]->frequency <
            heap->data[smallest]->frequency)
            smallest = left;

        if (right < heap->size &&
            heap->data[right]->frequency <
            heap->data[smallest]->frequency)
            smallest = right;

        if (smallest == index)
            break;

        swap(&heap->data[index], &heap->data[smallest]);

        index = smallest;
    }
}

void insertHeap(MinHeap *heap, Node *node)
{
    heap->data[heap->size] = node;
    heapifyUp(heap, heap->size);
    heap->size++;
}

Node *extractMin(MinHeap *heap)
{
    Node *minimum = heap->data[0];

    heap->size--;

    if (heap->size > 0) {
        heap->data[0] = heap->data[heap->size];
        heapifyDown(heap, 0);
    }

    return minimum;
}


Node *buildHuffmanTree(Symbol symbols[], int n)
{
    MinHeap heap;

    heap.size = 0;
    heap.capacity = 2 * n;
    heap.data = (Node **)malloc(
        heap.capacity * sizeof(Node *)
    );

    for (int i = 0; i < n; i++) {
        Node *node =
            createNode(symbols[i].symbol,
                       symbols[i].frequency,
                       1);

        insertHeap(&heap, node);
    }

    while (heap.size > 1) {

        Node *left = extractMin(&heap);
        Node *right = extractMin(&heap);

        Node *parent =
            createNode('\0',
                       left->frequency +
                       right->frequency,
                       0);

        parent->left = left;
        parent->right = right;

        insertHeap(&heap, parent);
    }

    Node *root = extractMin(&heap);

    free(heap.data);

    return root;
}


void findLengths(Node *root, int depth,
                 Symbol symbols[], int n)
{
    if (root == NULL)
        return;

    if (root->isLeaf) {

        for (int i = 0; i < n; i++) {
            if (symbols[i].symbol == root->symbol) {
                symbols[i].length = depth;
                break;
            }
        }

        return;
    }

    findLengths(root->left, depth + 1,
                symbols, n);

    findLengths(root->right, depth + 1,
                symbols, n);
}



int canonicalCompare(const void *a, const void *b)
{
    const Symbol *x = (const Symbol *)a;
    const Symbol *y = (const Symbol *)b;

    if (x->length != y->length)
        return x->length - y->length;

    return (unsigned char)x->symbol -
           (unsigned char)y->symbol;
}



void printCode(unsigned long long code, int length)
{
    if (length == 0) {
        printf("0");
        return;
    }

    for (int i = length - 1; i >= 0; i--) {
        printf("%llu", (code >> i) & 1ULL);
    }
}



void generateCanonicalCodes(Symbol symbols[], int n)
{
    qsort(symbols, n, sizeof(Symbol),
          canonicalCompare);

    unsigned long long code = 0;
    int previousLength = symbols[0].length;

    symbols[0].code = code;

    for (int i = 1; i < n; i++) {

        code++;

        if (symbols[i].length > previousLength) {
            code <<=
                (symbols[i].length - previousLength);
        }

        symbols[i].code = code;
        previousLength = symbols[i].length;
    }
}



double expectedLength(Symbol symbols[], int n)
{
    long long totalFrequency = 0;
    long long weightedLength = 0;

    for (int i = 0; i < n; i++) {
        totalFrequency += symbols[i].frequency;

        weightedLength +=
            (long long)symbols[i].frequency *
            symbols[i].length;
    }

    return (double)weightedLength /
           totalFrequency;
}



void freeTree(Node *root)
{
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);

    free(root);
}


int main()
{
    int n;

    printf("Enter number of symbols: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_SYMBOLS) {
        printf("Invalid number of symbols.\n");
        return 1;
    }

    Symbol symbols[MAX_SYMBOLS];

    printf("Enter symbol and frequency:\n");

    for (int i = 0; i < n; i++) {
        scanf(" %c %d",
              &symbols[i].symbol,
              &symbols[i].frequency);

        if (symbols[i].frequency <= 0) {
            printf("Frequency must be positive.\n");
            return 1;
        }

        symbols[i].length = 0;
        symbols[i].code = 0;
    }

    
    Node *root = buildHuffmanTree(symbols, n);

    findLengths(root, 0, symbols, n);

    
    generateCanonicalCodes(symbols, n);

    printf("\nCanonical Huffman Codebook\n");
    printf("--------------------------\n");
    printf("Symbol\tFrequency\tLength\tCode\n");

    for (int i = 0; i < n; i++) {
        printf("%c\t%d\t\t%d\t",
               symbols[i].symbol,
               symbols[i].frequency,
               symbols[i].length);

        printCode(symbols[i].code,
                  symbols[i].length);

        printf("\n");
    }

    printf("\nMinimum expected code length = %.4f bits/symbol\n",
           expectedLength(symbols, n));

    freeTree(root);

    return 0;
}