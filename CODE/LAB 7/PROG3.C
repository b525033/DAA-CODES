#include <stdio.h>
#include <limits.h>

#define MAX 20

long long dp[MAX + 1];
int split[MAX + 1];


long long moveCount = 0;


void moveDisk(int disk, char from, char to)
{
    moveCount++;
    printf("%2lld. Move disk %d from Peg %c to Peg %c\n",
           moveCount, disk, from, to);
}


void hanoi3(int n, int offset,
            char source, char destination, char auxiliary)
{
    if (n == 0)
        return;

    hanoi3(n - 1, offset, source, auxiliary, destination);

    moveDisk(offset + n, source, destination);

    hanoi3(n - 1, offset, auxiliary, destination, source);
}

void hanoi4(int n, int offset,
            char source, char destination,
            char auxiliary1, char auxiliary2)
{
    int k;

    if (n == 0)
        return;

    if (n == 1)
    {
        moveDisk(offset + 1, source, destination);
        return;
    }

    k = split[n];

    
    hanoi4(k, offset,
           source, auxiliary1,
           destination, auxiliary2);

    
    hanoi3(n - k, offset + k,
           source, destination, auxiliary2);

   
    hanoi4(k, offset,
           auxiliary1, destination,
           source, auxiliary2);
}

 
void calculateDP(int n)
{
    int i, k;

    dp[0] = 0;
    dp[1] = 1;
    split[1] = 0;

    for (i = 2; i <= n; i++)
    {
        dp[i] = LLONG_MAX;

        for (k = 1; k < i; k++)
        {
            long long moves;

            moves = 2 * dp[k]
                    + ((1LL << (i - k)) - 1);

            if (moves < dp[i])
            {
                dp[i] = moves;
                split[i] = k;
            }
        }
    }
}

int main()
{
    int n;

    printf("Enter number of disks (maximum %d): ", MAX);
    scanf("%d", &n);

    if (n < 1 || n > MAX)
    {
        printf("Invalid number of disks!\n");
        return 1;
    }

    calculateDP(n);

    printf("\nMinimum number of moves = %lld\n", dp[n]);
    printf("Optimal split for %d disks = %d disks\n\n",
           n, split[n]);

    printf("Sequence of moves:\n\n");

    hanoi4(n, 0, 'A', 'D', 'B', 'C');

    printf("\nTotal moves performed = %lld\n", moveCount);

    return 0;
}