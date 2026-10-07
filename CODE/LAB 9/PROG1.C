#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double v;       
    double w;       
    double lambda;  
    int id;
} Item;


int compareLambda(const void *a, const void *b)
{
    const Item *x = (const Item *)a;
    const Item *y = (const Item *)b;

    if (x->lambda < y->lambda) return -1;
    if (x->lambda > y->lambda) return 1;
    return 0;
}


double calculateValue(Item item[], double x[], int n)
{
    double time = 0.0;
    double totalValue = 0.0;

    for (int i = 0; i < n; i++) {
        if (x[i] <= 0.0)
            continue;

        double density =
            item[i].v / item[i].w
            - item[i].lambda * time;

        
        if (density > 0.0) {
            totalValue += x[i] * item[i].w * density;
            time += x[i] * item[i].w;
        }
    }

    return totalValue;
}

#define STEP 0.05

double bestValue;
double bestX[20];

void exhaustiveSearch(Item item[], int n, int pos,
                      double capacity, double used,
                      double x[])
{
    if (pos == n) {
        double value = calculateValue(item, x, n);

        if (value > bestValue) {
            bestValue = value;

            for (int i = 0; i < n; i++)
                bestX[i] = x[i];
        }
        return;
    }

    
    for (double fraction = 0.0;
         fraction <= 1.0 + 1e-9;
         fraction += STEP) {

        double newUsed = used + fraction * item[pos].w;

        if (newUsed <= capacity + 1e-9) {
            x[pos] = fraction;

            exhaustiveSearch(item, n, pos + 1,
                             capacity, newUsed, x);
        }
    }

    x[pos] = 0.0;
}

int main()
{
    int n;
    double W;

    printf("Enter number of items: ");
    scanf("%d", &n);

    if (n <= 0 || n > 20) {
        printf("Number of items must be between 1 and 20.\n");
        return 1;
    }

    printf("Enter knapsack capacity W: ");
    scanf("%lf", &W);

    Item item[20];

    printf("\nEnter v, w and lambda for each item:\n");

    for (int i = 0; i < n; i++) {
        printf("Item %d: ", i + 1);

        scanf("%lf %lf %lf",
              &item[i].v,
              &item[i].w,
              &item[i].lambda);

        item[i].id = i + 1;

        if (item[i].w <= 0 || item[i].lambda <= 0) {
            printf("Weight must be > 0 and lambda must be > 0.\n");
            return 1;
        }
    }

    
    qsort(item, n, sizeof(Item), compareLambda);

    printf("\nOptimal scheduling order (increasing lambda):\n");

    for (int i = 0; i < n; i++) {
        printf("Item %d: v = %.2f, w = %.2f, lambda = %.2f\n",
               item[i].id,
               item[i].v,
               item[i].w,
               item[i].lambda);
    }

    bestValue = -1.0;

    double x[20] = {0};

    
    exhaustiveSearch(item, n, 0, W, 0.0, x);

    printf("\nOptimal fractional choices:\n");

    double totalWeight = 0.0;

    for (int i = 0; i < n; i++) {
        if (bestX[i] > 1e-9) {
            printf("Item %d: %.2f%%\n",
                   item[i].id,
                   bestX[i] * 100.0);

            totalWeight += bestX[i] * item[i].w;
        }
    }

    printf("\nTotal weight used = %.4f", totalWeight);
    printf("\nMaximum total value = %.4f\n", bestValue);

    return 0;
}