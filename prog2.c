#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int n = 10000;
    int i;
    int fairHeads = 0, fairTails = 0;
    int biasedHeads = 0, biasedTails = 0;

    srand(time(NULL));

    // Fair coin simulation (P(Head) = 0.5)
    for(i = 0; i < n; i++) {
        if(rand() % 2 == 0)
            fairHeads++;
        else
            fairTails++;
    }

    // Biased coin simulation (P(Head) ≈ 0.7)
    for(i = 0; i < n; i++) {
        if((rand() % 10) < 7)
            biasedHeads++;
        else
            biasedTails++;
    }

    printf("FAIR COIN (10000 Tosses)\n");
    printf("Heads = %d\n", fairHeads);
    printf("Tails = %d\n", fairTails);
    printf("Probability of Head = %.4f\n", (float)fairHeads / n);
    printf("Probability of Tail = %.4f\n\n", (float)fairTails / n);

    printf("BIASED COIN (10000 Tosses)\n");
    printf("Heads = %d\n", biasedHeads);
    printf("Tails = %d\n", biasedTails);
    printf("Probability of Head = %.4f\n", (float)biasedHeads / n);
    printf("Probability of Tail = %.4f\n", (float)biasedTails / n);

    return 0;
}