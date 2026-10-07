#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int time;
    int type;      
} Event;


int compareEvents(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->time != e2->time)
        return e1->time - e2->time;

    return e1->type - e2->type;
}

int minConferenceRooms(int start[], int end[], int n) {
    if (n == 0)
        return 0;

    Event events[2 * n];

    
    for (int i = 0; i < n; i++) {
        events[2 * i].time = start[i];
        events[2 * i].type = 1;     // start

        events[2 * i + 1].time = end[i];
        events[2 * i + 1].type = -1; // end
    }

    qsort(events, 2 * n, sizeof(Event), compareEvents);

    int currentRooms = 0;
    int maxRooms = 0;

    
    for (int i = 0; i < 2 * n; i++) {
        currentRooms += events[i].type;

        if (currentRooms > maxRooms)
            maxRooms = currentRooms;
    }

    return maxRooms;
}

int main() {
    int n;

    printf("Enter number of meetings: ");
    scanf("%d", &n);

    int start[n], end[n];

    printf("Enter start and end times:\n");

    for (int i = 0; i < n; i++) {
        printf("Meeting %d: ", i + 1);
        scanf("%d %d", &start[i], &end[i]);

        if (start[i] >= end[i]) {
            printf("Invalid interval.\n");
            return 1;
        }
    }

    int result = minConferenceRooms(start, end, n);

    printf("\nMinimum number of conference rooms required = %d\n",
           result);

    return 0;
}