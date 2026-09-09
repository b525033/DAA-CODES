#include <stdio.h>

#define MAX 100


void printPossible(int possible[], int n)
{
    int i;
    int found = 0;

    printf("{ ");

    for (i = 0; i < n; i++)
    {
        if (possible[i])
        {
            printf("%d ", i + 1);
            found = 1;
        }
    }

    if (!found)
        printf("EMPTY ");

    printf("}");
}


void moveTarget(int possible[], int n)
{
    int next[MAX] = {0};
    int i;

    for (i = 0; i < n; i++)
    {
        if (possible[i])
        {
            if (i > 0)
                next[i - 1] = 1;

            
            if (i < n - 1)
                next[i + 1] = 1;
        }
    }

    for (i = 0; i < n; i++)
        possible[i] = next[i];
}


int shoot(int possible[], int n, int position)
{
    int i;
    int targetStillPossible = 0;

   
    possible[position - 1] = 0;

    
    for (i = 0; i < n; i++)
    {
        if (possible[i])
        {
            targetStillPossible = 1;
            break;
        }
    }

    return targetStillPossible;
}



int performShot(int possible[], int n,
                int position, int shotNumber)
{
    int stillPossible;

    printf("\nShot %d: Shoot hiding spot %d\n",
           shotNumber, position);

    stillPossible = shoot(possible, n, position);

    printf("Possible target positions after shot: ");
    printPossible(possible, n);
    printf("\n");

   
    if (stillPossible)
    {
        moveTarget(possible, n);

        printf("Possible positions after target moves: ");
        printPossible(possible, n);
        printf("\n");
    }

    return stillPossible;
}


int main()
{
    int n;
    int possible[MAX];
    int i;
    int shotNumber = 0;
    int stillPossible = 1;

    printf("Enter number of hiding spots: ");
    scanf("%d", &n);

    if (n < 2 || n > MAX)
    {
        printf("Invalid input!\n");
        return 1;
    }

    
    for (i = 0; i < n; i++)
        possible[i] = 1;

    printf("\nHiding spots: ");

    for (i = 1; i <= n; i++)
        printf("%d ", i);

    printf("\n\nInitial possible target positions: ");
    printPossible(possible, n);
    printf("\n");


    
    if (n == 2)
    {
        stillPossible =
            performShot(possible, n, 1, ++shotNumber);

        if (stillPossible)
            stillPossible =
                performShot(possible, n, 1, ++shotNumber);
    }

    /* n is even */
    else if (n % 2 == 0)
    {
        
        for (i = 2; i <= n - 1 && stillPossible; i++)
        {
            stillPossible =
                performShot(possible, n, i, ++shotNumber);
        }

       
        for (i = n - 1; i >= 2 && stillPossible; i--)
        {
            stillPossible =
                performShot(possible, n, i, ++shotNumber);
        }
    }

    else
    {
        
        for (i = 2; i <= n - 1 && stillPossible; i++)
        {
            stillPossible =
                performShot(possible, n, i, ++shotNumber);
        }

        
        for (i = 2; i <= n - 1 && stillPossible; i++)
        {
            stillPossible =
                performShot(possible, n, i, ++shotNumber);
        }
    }


    printf("\n-----------------------------------\n");

    if (!stillPossible)
    {
        printf("Target is guaranteed to be hit!\n");
        printf("Number of shots used = %d\n", shotNumber);
    }
    else
    {
        printf("Target may still be hiding.\n");
    }

    printf("-----------------------------------\n");

    return 0;
}