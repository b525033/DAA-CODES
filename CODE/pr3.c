
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void mergeTwo(int *A, int nA, int *B, int nB, int *out) {
    int i = 0, j = 0, k = 0;
    while (i < nA && j < nB) {
        if (A[i] <= B[j]) out[k++] = A[i++];
        else out[k++] = B[j++];
    }
    while (i < nA) out[k++] = A[i++];
    while (j < nB) out[k++] = B[j++];
}

int* mergeK_Method1(int **arrays, int k, int n) {
    int current_size = n;
    int *current_res = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) current_res[i] = arrays[0][i];

    for (int i = 1; i < k; i++) {
        int *next_res = (int *)malloc((current_size + n) * sizeof(int));
        mergeTwo(current_res, current_size, arrays[i], n, next_res);
        free(current_res);
        current_res = next_res;
        current_size += n;
    }
    return current_res;
}
int* mergeK_Method2(int **arrays, int k, int n) {
    int num_arrays = k;
    int **arr_list = (int **)malloc(k * sizeof(int *));
    int *sizes = (int *)malloc(k * sizeof(int));

    for (int i = 0; i < k; i++) {
        arr_list[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) arr_list[i][j] = arrays[i][j];
        sizes[i] = n;
    }

    while (num_arrays > 1) {
        int new_num = (num_arrays + 1) / 2;
        int **next_list = (int **)malloc(new_num * sizeof(int *));
        int *next_sizes = (int *)malloc(new_num * sizeof(int));

        int idx = 0;
        for (int i = 0; i < num_arrays; i += 2) {
            if (i + 1 < num_arrays) {
                int s1 = sizes[i], s2 = sizes[i + 1];
                next_sizes[idx] = s1 + s2;
                next_list[idx] = (int *)malloc((s1 + s2) * sizeof(int));
                mergeTwo(arr_list[i], s1, arr_list[i + 1], s2, next_list[idx]);
                free(arr_list[i]);
                free(arr_list[i + 1]);
            } else {
                next_sizes[idx] = sizes[i];
                next_list[idx] = arr_list[i];
            }
            idx++;
        }

        free(arr_list);
        free(sizes);
        arr_list = next_list;
        sizes = next_sizes;
        num_arrays = new_num;
    }

    int *final_res = arr_list[0];
    free(arr_list);
    free(sizes);
    return final_res;
}

int main(void) {
    int k = 64;   
    int n = 5000; 

    int **arrays = (int **)malloc(k * sizeof(int *));
    for (int i = 0; i < k; i++) {
        arrays[i] = (int *)malloc(n * sizeof(int));
        int val = rand() % 10;
        for (int j = 0; j < n; j++) {
            val += rand() % 5;
            arrays[i][j] = val;
        }
    }

    clock_t t1 = clock();
    int *res1 = mergeK_Method1(arrays, k, n);
    clock_t t2 = clock();
    double time1 = ((double)(t2 - t1)); 

     t1 = clock();
    int *res2 = mergeK_Method2(arrays, k, n);
    t2 = clock();
    double time2 = ((double)(t2 - t1));

    printf("Merging k = %d arrays of size n = %d (Total N = %d elements):\n", k, n, k * n);
    printf("Method 1 (Iterative, O(n*k^2)) Time: %.6f seconds\n", time1);
    printf("Method 2 (Pairwise,  O(n*k*log k)) Time: %.6f seconds\n", time2);

     free(res1);
    free(res2);
    for (int i = 0; i < k; i++) free(arrays[i]);
    free(arrays);

    return 0;
}