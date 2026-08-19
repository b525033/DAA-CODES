#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Interval;


int compare(const void *a, const void *b) {
    Interval *i1 = (Interval *)a;
    Interval *i2 = (Interval *)b;

    return i1->start - i2->start;
}


int mergeIntervals(Interval intervals[], int n, Interval result[]) {
    if (n == 0)
        return 0;

   
    qsort(intervals, n, sizeof(Interval), compare);

    int k = 0;

    
    result[k] = intervals[0];

    for (int i = 1; i < n; i++) {

        
        if (intervals[i].start <= result[k].end) {

            
            if (intervals[i].end > result[k].end)
                result[k].end = intervals[i].end;

        } else {
           
            k++;
            result[k] = intervals[i];
        }
    }

    return k + 1;
}

int main() {
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Interval intervals[n];
    Interval result[n];

    printf("Enter intervals (start end):\n");

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &intervals[i].start, &intervals[i].end);
    }

    int m = mergeIntervals(intervals, n, result);

    printf("\nMerged intervals:\n");

    for (int i = 0; i < m; i++) {
        printf("(%d,%d)", result[i].start, result[i].end);

        if (i < m - 1)
            printf(", ");
    }

    printf("\n");

    return 0;
}