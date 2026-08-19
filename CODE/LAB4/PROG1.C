#include <stdio.h>
#include <string.h>

typedef struct {
    int number;
    char colour[10];
} Item;

int main() {
    int n, i;
    int r = 0, b = 0, y = 0;

    printf("Enter number of items: ");
    scanf("%d", &n);

    Item input[n];
    Item red[n], blue[n], yellow[n];

    printf("Enter %d pairs (number colour):\n", n);

    
    for (i = 0; i < n; i++) {
        scanf("%d %s", &input[i].number, input[i].colour);
    }

    
    for (i = 0; i < n; i++) {
        if (strcmp(input[i].colour, "red") == 0) {
            red[r++] = input[i];
        }
        else if (strcmp(input[i].colour, "blue") == 0) {
            blue[b++] = input[i];
        }
        else if (strcmp(input[i].colour, "yellow") == 0) {
            yellow[y++] = input[i];
        }
    }

    printf("\nItems sorted by colour:\n");

    
    for (i = 0; i < r; i++) {
        printf("%d red\n", red[i].number);
    }

    
    for (i = 0; i < b; i++) {
        printf("%d blue\n", blue[i].number);
    }
    for (i = 0; i < y; i++) {
        printf("%d yellow\n", yellow[i].number);
    }

    return 0;
}