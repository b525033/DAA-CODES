#include <stdio.h>
#include <stdlib.h>

#define MAX_N 15


int canToggle(int state, int n, int pos)
{
    int i;

    
    if (pos == n - 1)
        return 1;

    
    if ((state & (1 << (n - 1 - (pos + 1)))) == 0)
        return 0;

    
    for (i = pos + 2; i < n; i++)
    {
        if (state & (1 << (n - 1 - i)))
            return 0;
    }

    return 1;
}


void printState(int state, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        if (state & (1 << (n - 1 - i)))
            printf("1");
        else
            printf("0");
    }
}


long long minimumMovesDP(int n)
{
    long long dp[MAX_N + 1];
    int i;

    dp[1] = 1;

    for (i = 2; i <= n; i++)
    {
        if (i % 2 == 0)
            dp[i] = 2 * dp[i - 1];
        else
            dp[i] = 2 * dp[i - 1] + 1;
    }

    return dp[n];
}


int solveBFS(int n)
{
    int totalStates = 1 << n;
    int start = totalStates - 1;
    int goal = 0;

    int *visited;
    int *parent;
    int *move;
    int *queue;

    int front = 0, rear = 0;
    int current, next;
    int pos, distance;

    visited = (int *)calloc(totalStates, sizeof(int));
    parent = (int *)malloc(totalStates * sizeof(int));
    move = (int *)malloc(totalStates * sizeof(int));
    queue = (int *)malloc(totalStates * sizeof(int));

    if (visited == NULL || parent == NULL ||
        move == NULL || queue == NULL)
    {
        printf("Memory allocation failed.\n");
        return -1;
    }

    for (pos = 0; pos < totalStates; pos++)
    {
        parent[pos] = -1;
        move[pos] = -1;
    }

    
    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear)
    {
        current = queue[front++];

        if (current == goal)
            break;

        for (pos = 0; pos < n; pos++)
        {
            if (canToggle(current, n, pos))
            {
                
                next = current ^ (1 << (n - 1 - pos));

                if (!visited[next])
                {
                    visited[next] = 1;
                    parent[next] = current;
                    move[next] = pos;
                    queue[rear++] = next;
                }
            }
        }
    }

    
    distance = 0;
    current = goal;

    while (current != start)
    {
        distance++;
        current = parent[current];
    }

    printf("\nMinimum sequence of states:\n\n");

    
    int *path = (int *)malloc((distance + 1) * sizeof(int));

    current = goal;

    for (pos = distance; pos >= 0; pos--)
    {
        path[pos] = current;
        current = parent[current];
    }

    
    for (pos = 0; pos <= distance; pos++)
    {
        printf("Step %2d: ", pos);
        printState(path[pos], n);

        if (pos > 0)
            printf("   (Toggled switch %d)", move[path[pos]] + 1);

        printf("\n");
    }

    free(path);
    free(visited);
    free(parent);
    free(move);
    free(queue);

    return distance;
}

int main()
{
    int n;
    long long theoreticalMoves;
    int bfsMoves;

    printf("Enter number of switches (1-%d): ", MAX_N);
    scanf("%d", &n);

    if (n < 1 || n > MAX_N)
    {
        printf("Invalid input!\n");
        return 1;
    }

    
    theoreticalMoves = minimumMovesDP(n);

    printf("\nInitial State: ");
    for (int i = 0; i < n; i++)
        printf("1");

    printf("\nFinal State:   ");
    for (int i = 0; i < n; i++)
        printf("0");

    printf("\n\nMinimum moves using DP = %lld\n",
           theoreticalMoves);

    bfsMoves = solveBFS(n);

    printf("\nMinimum moves found using BFS = %d\n",
           bfsMoves);

    if (bfsMoves == theoreticalMoves)
        printf("\nValidation successful!\n");
    else
        printf("\nValidation failed!\n");

    return 0;
}