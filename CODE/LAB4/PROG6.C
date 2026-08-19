#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int point;
    int type;       
} Event;

int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->point != e2->point)
        return e1->point - e2->point;

    return e2->type - e1->type;
}

int main()
{
    int n;

    printf("Enter number of intervals: ");
    scanf("%d", &n);

    Event *events = (Event *)malloc(2 * n * sizeof(Event));

    printf("Enter the intervals (left right):\n");

    for (int i = 0; i < n; i++) {
        int l, r;

        scanf("%d %d", &l, &r);

        events[2 * i].point = l;
        events[2 * i].type = +1;

        events[2 * i + 1].point = r;
        events[2 * i + 1].type = -1;
    }

    
    qsort(events, 2 * n, sizeof(Event), compare);

    int count = 0;
    int maxCount = 0;
    int bestPoint = 0;

    
    for (int i = 0; i < 2 * n; i++) {
        count += events[i].type;

        if (count > maxCount) {
            maxCount = count;
            bestPoint = events[i].point;
        }
    }

    printf("\nPoint with maximum overlapping intervals: %d\n", bestPoint);
    printf("Maximum number of overlapping intervals: %d\n", maxCount);

    free(events);

    return 0;
}