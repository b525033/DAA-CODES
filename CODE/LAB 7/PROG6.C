#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50


typedef struct {
    char name[MAX_NAME];
    int birth;
    int death;
} Scientist;


typedef struct {
    int year;
    int type;   
} Event;


int compareEvents(const void *a, const void *b)
{
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;

    if (e1->year < e2->year)
        return -1;

    if (e1->year > e2->year)
        return 1;

    
    return e1->type - e2->type;
}



void bestTime(Scientist scientists[], int n)
{
    Event *events;
    int i;

    int currentAlive = 0;
    int maxAlive = 0;
    int bestYear = -1;

    events = (Event *)malloc(2 * n * sizeof(Event));

    if (events == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }
* 
    for (i = 0; i < n; i++)
    {
        events[2 * i].year = scientists[i].birth;
        events[2 * i].type = +1;

        events[2 * i + 1].year = scientists[i].death;
        events[2 * i + 1].type = -1;
    }

    
    qsort(events, 2 * n, sizeof(Event), compareEvents);

    
    for (i = 0; i < 2 * n; i++)
    {
        currentAlive += events[i].type;

        if (currentAlive > maxAlive)
        {
            maxAlive = currentAlive;
            bestYear = events[i].year;
        }
    }

    
    printf("\n--------------------------------------\n");
    printf("Best time to be alive: %d\n", bestYear);
    printf("Maximum scientists alive: %d\n", maxAlive);
    printf("--------------------------------------\n");

    free(events);
}


int main()
{
    int n, i;

    printf("Enter number of scientists: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of scientists!\n");
        return 1;
    }

    Scientist *scientists =
        (Scientist *)malloc(n * sizeof(Scientist));

    if (scientists == NULL)
    {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("\nEnter scientist information:\n");
    printf("Name BirthYear DeathYear\n\n");

    for (i = 0; i < n; i++)
    {
        scanf("%s %d %d",
              scientists[i].name,
              &scientists[i].birth,
              &scientists[i].death);
    }

    bestTime(scientists, n);

    free(scientists);

    return 0;
}