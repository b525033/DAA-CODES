
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 15
#define MAX_LEN 100

char str[MAX_N][MAX_LEN];

/* overlap[i][j] = maximum suffix-prefix overlap */
int overlap[MAX_N][MAX_N];

/* ---------- Calculate overlap ---------- */

int calculateOverlap(const char *a, const char *b) {
    int lenA = strlen(a);
    int lenB = strlen(b);

    int maxOverlap = lenA < lenB ? lenA : lenB;

    for (int k = maxOverlap; k >= 1; k--) {
        int match = 1;

        for (int i = 0; i < k; i++) {
            if (a[lenA - k + i] != b[i]) {
                match = 0;
                break;
            }
        }

        if (match)
            return k;
    }

    return 0;
}


int removeRedundantStrings(int n) {
    int removed[MAX_N] = {0};
    int newN = 0;

    for (int i = 0; i < n; i++) {
        int redundant = 0;

        for (int j = 0; j < n; j++) {
            if (i != j &&
                strstr(str[j], str[i]) != NULL &&
                strlen(str[j]) >= strlen(str[i])) {

                if (strlen(str[j]) > strlen(str[i]) ||
                    strcmp(str[j], str[i]) != 0) {
                    redundant = 1;
                    break;
                }
            }
        }

        if (!redundant) {
            strcpy(str[newN], str[i]);
            newN++;
        }
    }

    return newN;
}


char *exactSCS(int n) {
    int totalMasks = 1 << n;

    long long **dp =
        malloc(totalMasks * sizeof(long long *));

    int **parent =
        malloc(totalMasks * sizeof(int *));

    for (int mask = 0; mask < totalMasks; mask++) {
        dp[mask] = malloc(n * sizeof(long long));
        parent[mask] = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            dp[mask][i] = LLONG_MAX / 2;
            parent[mask][i] = -1;
        }
    }

   
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = strlen(str[i]);
    }

    
    for (int mask = 1; mask < totalMasks; mask++) {

        for (int last = 0; last < n; last++) {

            if (!(mask & (1 << last)))
                continue;

            if (dp[mask][last] >= LLONG_MAX / 4)
                continue;

            for (int next = 0; next < n; next++) {

                if (mask & (1 << next))
                    continue;

                int newMask = mask | (1 << next);

                long long added =
                    strlen(str[next]) - overlap[last][next];

                long long newCost =
                    dp[mask][last] + added;

                if (newCost < dp[newMask][next]) {
                    dp[newMask][next] = newCost;
                    parent[newMask][next] = last;
                }
            }
        }
    }

    
    int fullMask = totalMasks - 1;
    int last = 0;

    for (int i = 1; i < n; i++) {
        if (dp[fullMask][i] < dp[fullMask][last])
            last = i;
    }

   
    int order[MAX_N];
    int mask = fullMask;

    for (int pos = n - 1; pos >= 0; pos--) {
        order[pos] = last;

        int previous = parent[mask][last];

        mask ^= (1 << last);
        last = previous;

        if (mask == 0)
            break;
    }

    
    int answerSize = (int)dp[fullMask][order[n - 1]];

    char *answer = malloc(answerSize + 1);
    answer[0] = '\0';

    strcat(answer, str[order[0]]);

    for (int i = 1; i < n; i++) {
        int previous = order[i - 1];
        int current = order[i];

        int ov = overlap[previous][current];

        strcat(answer, str[current] + ov);
    }

    
    for (int maskIndex = 0;
         maskIndex < totalMasks;
         maskIndex++) {

        free(dp[maskIndex]);
        free(parent[maskIndex]);
    }

    free(dp);
    free(parent);

    return answer;
}



char *mergeStrings(const char *a, const char *b) {
    int lenA = strlen(a);
    int lenB = strlen(b);

    int ov = calculateOverlap(a, b);

    char *result =
        malloc(lenA + lenB - ov + 1);

    strcpy(result, a);
    strcat(result, b + ov);

    return result;
}


char *greedySCS(int n) {
    char **current =
        malloc(n * sizeof(char *));

    for (int i = 0; i < n; i++) {
        current[i] = malloc(strlen(str[i]) + 1);
        strcpy(current[i], str[i]);
    }

    int count = n;

    while (count > 1) {

        int bestI = 0;
        int bestJ = 1;
        int bestOverlap = -1;

        
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < count; j++) {

                if (i == j)
                    continue;

                int ov =
                    calculateOverlap(
                        current[i],
                        current[j]);

                if (ov > bestOverlap) {
                    bestOverlap = ov;
                    bestI = i;
                    bestJ = j;
                }
            }
        }

        
        char *merged =
            mergeStrings(
                current[bestI],
                current[bestJ]);

        free(current[bestI]);
        current[bestI] = merged;

        free(current[bestJ]);

        
        for (int i = bestJ; i < count - 1; i++)
            current[i] = current[i + 1];

        count--;
    }

    char *answer = current[0];

    free(current);

    return answer;
}



int main() {
    int n;

    printf("Enter number of strings: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_N) {
        printf("n must be between 1 and %d.\n",
               MAX_N);
        return 1;
    }

    printf("Enter the strings:\n");

    for (int i = 0; i < n; i++)
        scanf("%99s", str[i]);


    n = removeRedundantStrings(n);

    if (n == 0) {
        printf("Shortest common superstring = \"\"\n");
        return 0;
    }

    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i == j)
                overlap[i][j] = 0;
            else
                overlap[i][j] =
                    calculateOverlap(str[i], str[j]);
        }
    }

   
    char *optimal = exactSCS(n);

    
    char *greedy = greedySCS(n);

    printf("\nAfter removing redundant strings: %d\n", n);

    printf("\nOptimal shortest common superstring:\n");
    printf("%s\n", optimal);

    printf("Optimal length = %zu\n",
           strlen(optimal));

    printf("\nGreedy maximum-overlap superstring:\n");
    printf("%s\n", greedy);

    printf("Greedy length = %zu\n",
           strlen(greedy));

    printf("\nGreedy / Optimal ratio = %.3f\n",
           (double)strlen(greedy) /
           strlen(optimal));

    free(optimal);
    free(greedy);

    return 0;
}