#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct SinglyNode {
    int key;
    struct SinglyNode *next;
} SinglyNode;

typedef struct DoublyNode {
    int key;
    struct DoublyNode *prev;
    struct DoublyNode *next;
} DoublyNode;

double get_time_sec(clock_t start, clock_t end) {
    return ((double)(end - start)) / CLOCKS_PER_SEC;
}

int search_unsorted_array(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) return i;
    }
    return -1;
}

int search_sorted_array(int arr[], int n, int key) {
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key) return mid;
        else if (arr[mid] < key) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

SinglyNode* search_singly_list(SinglyNode *head, int key) {
    SinglyNode *curr = head;
    while (curr != NULL) {
        if (curr->key == key) return curr;
        curr = curr->next;
    }
    return NULL;
}

int main(void) {
    int sizes[] = {10000, 30000, 60000, 100000};
    int num_sizes = 4;
    int num_queries = 1000;

    printf("N,UnsortedArray_Search_s,SortedArray_Search_s,SinglyList_Search_s\n");

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];
        int *unsorted_arr = (int *)malloc(n * sizeof(int));
        int *sorted_arr = (int *)malloc(n * sizeof(int));
        SinglyNode *head = NULL;

        for (int i = 0; i < n; i++) {
            int val = rand() % (n * 10);
            unsorted_arr[i] = val;
            sorted_arr[i] = i * 2; 

            SinglyNode *node = (SinglyNode *)malloc(sizeof(SinglyNode));
            node->key = val;
            node->next = head;
            head = node;
        }

         clock_t start = clock();
        for (int q = 0; q < num_queries; q++) {
            search_unsorted_array(unsorted_arr, n, -1);
        }
        clock_t end = clock();
        double time_unsorted = get_time_sec(start, end);

     start = clock();
        for (int q = 0; q < num_queries; q++) {
            search_sorted_array(sorted_arr, n, -1);
        }
        end = clock();
        double time_sorted = get_time_sec(start, end);

        start = clock();
        for (int q = 0; q < num_queries; q++) {
            search_singly_list(head, -1);
        }
        end = clock();
        double time_singly = get_time_sec(start, end);

        printf("%d,%.6f,%.6f,%.6f\n", n, time_unsorted, time_sorted, time_singly);

         free(unsorted_arr);
        free(sorted_arr);
        while (head != NULL) {
            SinglyNode *temp = head;
            head = head->next;
            free(temp);
        }
    }

    return 0;
}