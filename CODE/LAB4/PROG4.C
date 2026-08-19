#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int time;
    int type;      
} Event;

/* Comparison function for qsort */
int compare(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    return e1->time - e2->time;
}

int main()
{
    int n, i;
    int *entry, *exit;
    Event *events;

    int current = 0;
    int maxPeople = 0;
    int maxTime = 0;

    printf("Enter number of persons: ");
    scanf("%d", &n);

    entry = (int *)malloc(n * sizeof(int));
    exit = (int *)malloc(n * sizeof(int));
    events = (Event *)malloc(2 * n * sizeof(Event));

    printf("Enter entry and exit times:\n");

    for (i = 0; i < n; i++)
    {
        printf("Person %d: ", i + 1);
        scanf("%d %d", &entry[i], &exit[i]);

        events[2 * i].time = entry[i];
        events[2 * i].type = 1;

        events[2 * i + 1].time = exit[i];
        events[2 * i + 1].type = -1;
    }

    
    qsort(events, 2 * n, sizeof(Event), compare);

    printf("\nSorted events:\n");

    for (i = 0; i < 2 * n; i++)
    {
        if (events[i].type == 1)
            printf("Time %d : Entry\n", events[i].time);
        else
            printf("Time %d : Exit\n", events[i].time);
    }

    
    for (i = 0; i < 2 * n; i++)
    {
        current += events[i].type;

        if (current > maxPeople)
        {
            maxPeople = current;
            maxTime = events[i].time;
        }
    }

    printf("\nMaximum number of people present = %d\n", maxPeople);
    printf("Time when maximum people were simultaneously present = %d\n",
           maxTime);

    free(entry);
    free(exit);
    free(events);

    return 0;
}