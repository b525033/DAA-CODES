#include <stdio.h>
#include <stdlib.h>
#include <float.h>

void printTree(int root[][20], int i, int j, int parent, char side[]) {
    if (i > j) {
        return;
    }

    int r = root[i][j];

    printf("k%d is %s of ", r, side);

    if (parent == 0)
        printf("ROOT\n");
    else
        printf("k%d\n", parent);

    printTree(root, i, r - 1, r, "LEFT child");
    printTree(root, r + 1, j, r, "RIGHT child");
}

int string() {
    int n;

    printf("Enter number of keys: ");
    scanf("%d", &n);

    if (n >= 20) {
        printf("Maximum supported number of keys is 19.\n");
        return 1;
    }

    double p[20], q[20];
    double e[20][20];
    double w[20][20];
    int root[20][20];

   
    printf("\nEnter probabilities p1 to p%d:\n", n);

    for (int i = 1; i <= n; i++) {
        printf("p[%d] = ", i);
        scanf("%lf", &p[i]);
    }

   
    printf("\nEnter dummy-key probabilities q0 to q%d:\n", n);

    for (int i = 0; i <= n; i++) {
        printf("q[%d] = ", i);
        scanf("%lf", &q[i]);
    }

  
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    
    for (int length = 1; length <= n; length++) {

        for (int i = 1; i <= n - length + 1; i++) {

            int j = i + length - 1;

            e[i][j] = DBL_MAX;

            w[i][j] = w[i][j - 1] + p[j] + q[j];

            
            for (int r = i; r <= j; r++) {

                double cost =
                    e[i][r - 1] +
                    e[r + 1][j] +
                    w[i][j];

                if (cost < e[i][j]) {
                    e[i][j] = cost;
                    root[i][j] = r;
                }
            }
        }
    }

    printf("\n====================================\n");
    printf("       OPTIMAL BST RESULTS\n");
    printf("====================================\n");

    printf("Minimum Expected Search Cost = %.4f\n",
           e[1][n]);

    printf("\nOptimal Root = k%d\n", root[1][n]);

    printf("\nStructure of Optimal BST:\n");
    printTree(root, 1, n, 0, "ROOT");

    printf("\nDP Cost Table:\n");

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            printf("e[%d][%d] = %.4f\n",
                   i, j, e[i][j]);
        }
    }

    return 0;
}