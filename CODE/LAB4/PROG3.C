 #include <stdio.h>
#include <stdlib.h>
int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}
int twoSum(int a[], int left, int right, int target)
{
    while (left < right)
    {
        int sum = a[left] + a[right];
    if (sum == target)
            return 1;   
  if (sum < target)
            left++;
        else
            right--;
    }
 return 0;
}
int kSum(int a[], int n, int start, int count,
         int kMinus2, int target)
{
   int i;
    if (count == kMinus2)
    {
        return twoSum(a, start, n - 1, target);
    }
   for (i = start; i <= n - (kMinus2 - count); i++)
    {
        if (kSum(a, n, i + 1, count + 1,
                 kMinus2, target - a[i]))
        {
            return 1;
        }
    }
    return 0;
}
int main()
{
    int n, k, T;
    int *S;
    int i, result;
 printf("Enter number of elements: ");
    scanf("%d", &n);
  S = (int *)malloc(n * sizeof(int));
  printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++)
        scanf("%d", &S[i]);
    printf("Enter k: ");
    scanf("%d", &k);
  printf("Enter target T: ");
    scanf("%d", &T);

    if (k < 2 || k > n)
    {
        printf("Invalid value of k.\n");
        free(S);
        return 0;
    }
    qsort(S, n, sizeof(int), compare);

    printf("\nSorted set: ");
    for (i = 0; i < n; i++)
        printf("%d ", S[i]);
    printf("\n");
    if (k == 2)
        result = twoSum(S, 0, n - 1, T);
    else
        result = kSum(S, n, 0, 0, k - 2, T);
    if (result)
        printf("\nYES: %d elements add up to %d.\n", k, T);
    else
        printf("\nNO: No %d elements add up to %d.\n", k, T);
   free(S);
 return 0;
}
