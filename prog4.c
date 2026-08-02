#include <stdio.h>
#include <math.h>

void TOH(int n, char source, char auxiliary, char destination)
{
    if (n == 1)
    {
        printf("Move Disk 1 from %c to %c\n", source, destination);
        return;
    }

    TOH(n - 1, source, destination, auxiliary);
    printf("Move Disk %d from %c to %c\n", n, source, destination);
    TOH(n - 1, auxiliary, source, destination);
}

int main()
{
    int n;
    long long moves;

    printf("Enter the number of disks: ");
    scanf("%d", &n);

    TOH(n, 'A', 'B', 'C');

    moves = (1LL << n) - 1;   // Total moves = 2^n - 1

    printf("\nTotal number of moves = %lld\n", moves);

    return 0;
}