#include <stdio.h>
#include <stdlib.h>


long long nextCollatz(long long n)
{
    if (n % 2 == 0)
        return n / 2;
    else
        return 3 * n + 1;
}

void analyzeTrajectory(long long n)
{
    if (n <= 0)
    {
        printf("Starting value must be positive.\n");
        return;
    }

    long long current = n;
    long long steps = 0;
    long long peak = n;

    printf("\nTrajectory:\n");
    printf("%lld", current);

    while (current != 1)
    {
        current = nextCollatz(current);
        steps++;

        if (current > peak)
            peak = current;

        printf(" -> %lld", current);
    }

    printf("\n\nStarting value = %lld", n);
    printf("\nTotal steps    = %lld", steps);
    printf("\nPeak value     = %lld\n", peak);
}


void analyzeInterval(long long a, long long b)
{
    if (a <= 0 || b <= 0 || a > b)
    {
        printf("Invalid interval.\n");
        return;
    }

    long long maxSteps = -1;
    long long maxStepValue = a;

    printf("\n========================================\n");
    printf("       INTERVAL ANALYSIS [%lld, %lld]\n", a, b);
    printf("========================================\n");

    printf("%-10s %-15s %-15s\n",
           "Start", "Steps", "Peak");

    for (long long n = a; n <= b; n++)
    {
        long long current = n;
        long long steps = 0;
        long long peak = n;

        while (current != 1)
        {
            current = nextCollatz(current);
            steps++;

            if (current > peak)
                peak = current;
        }

        printf("%-10lld %-15lld %-15lld\n",
               n, steps, peak);

        if (steps > maxSteps)
        {
            maxSteps = steps;
            maxStepValue = n;
        }
    }

    printf("\nStarting value with maximum steps = %lld",
           maxStepValue);
    printf("\nMaximum number of steps = %lld\n",
           maxSteps);
}


int main()
{
    int choice;
    long long n, a, b;

    while (1)
    {
        printf("\n========================================\n");
        printf("          COLLATZ ANALYZER\n");
        printf("========================================\n");
        printf("1. Analyze a starting value\n");
        printf("2. Analyze an interval [a, b]\n");
        printf("3. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter starting value n: ");
                scanf("%lld", &n);

                analyzeTrajectory(n);
                break;

            case 2:
                printf("Enter interval [a, b]: ");
                scanf("%lld %lld", &a, &b);

                analyzeInterval(a, b);
                break;

            case 3:
                printf("Program terminated.\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}