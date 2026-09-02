#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 20
#define EPS 1e-9


void printMatrix(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%8.2lf ", A[i][j]);
        printf("\n");
    }
}


void addMatrix(double A[MAX][MAX], double B[MAX][MAX],
               double C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}


void multiplyMatrix(double A[MAX][MAX], double B[MAX][MAX],
                    double C[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            C[i][j] = 0;

            for (int k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    }
}


int isZeroMatrix(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (fabs(A[i][j]) > EPS)
                return 0;

    return 1;
}


int isSymmetric(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(A[i][j] - A[j][i]) > EPS)
                return 0;
        }
    }

    return 1;
}


double determinant(double A[MAX][MAX], int n)
{
    double B[MAX][MAX];
    double det = 1.0;

    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];

    for (int i = 0; i < n; i++)
    {
       
        int pivot = i;

        for (int j = i + 1; j < n; j++)
        {
            if (fabs(B[j][i]) > fabs(B[pivot][i]))
                pivot = j;
        }

        if (fabs(B[pivot][i]) < EPS)
            return 0.0;

       
        if (pivot != i)
        {
            for (int j = 0; j < n; j++)
            {
                double temp = B[i][j];
                B[i][j] = B[pivot][j];
                B[pivot][j] = temp;
            }

            det = -det;
        }

        det *= B[i][i];

        
        for (int j = i + 1; j < n; j++)
        {
            double factor = B[j][i] / B[i][i];

            for (int k = i + 1; k < n; k++)
                B[j][k] -= factor * B[i][k];
        }
    }

    return det;
}


void transposeInPlace(double A[MAX][MAX], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double temp = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = temp;
        }
    }
}


void eigenJacobi(double A[MAX][MAX], int n,
                 double eigenvalues[MAX],
                 double V[MAX][MAX])
{
    double B[MAX][MAX];

    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            B[i][j] = A[i][j];

    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            V[i][j] = (i == j) ? 1.0 : 0.0;

    for (int iteration = 0; iteration < 100; iteration++)
    {
        int p = 0, q = 1;
        double max = fabs(B[0][1]);

       
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (fabs(B[i][j]) > max)
                {
                    max = fabs(B[i][j]);
                    p = i;
                    q = j;
                }
            }
        }

        if (max < EPS)
            break;

        double theta = 0.5 *
            atan2(2.0 * B[p][q], B[q][q] - B[p][p]);

        double c = cos(theta);
        double s = sin(theta);

        
        for (int i = 0; i < n; i++)
        {
            if (i != p && i != q)
            {
                double Bip = B[i][p];
                double Biq = B[i][q];

                B[i][p] = c * Bip - s * Biq;
                B[p][i] = B[i][p];

                B[i][q] = s * Bip + c * Biq;
                B[q][i] = B[i][q];
            }
        }

        double Bpp = B[p][p];
        double Bqq = B[q][q];
        double Bpq = B[p][q];

        B[p][p] = c*c*Bpp - 2*s*c*Bpq + s*s*Bqq;
        B[q][q] = s*s*Bpp + 2*s*c*Bpq + c*c*Bqq;
        B[p][q] = B[q][p] = 0.0;

        
        for (int i = 0; i < n; i++)
        {
            double Vip = V[i][p];
            double Viq = V[i][q];

            V[i][p] = c * Vip - s * Viq;
            V[i][q] = s * Vip + c * Viq;
        }
    }

    for (int i = 0; i < n; i++)
        eigenvalues[i] = B[i][i];
}

int main()
{
    int n;
    double A[MAX][MAX], B[MAX][MAX], C[MAX][MAX];

    printf("Enter order of square matrix: ");
    scanf("%d", &n);

    printf("\nEnter Matrix A:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &A[i][j]);

    printf("\nEnter Matrix B:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &B[i][j]);

    
    addMatrix(A, B, C, n);
    printf("\n(i) Matrix Addition (A + B):\n");
    printMatrix(C, n);

   
    multiplyMatrix(A, B, C, n);
    printf("\n(ii) Matrix Multiplication (A * B):\n");
    printMatrix(C, n);

    
    printf("\n(iii) A is %s a zero matrix.\n",
           isZeroMatrix(A, n) ? "" : "not");

    
    printf("(iv) A is %s a symmetric matrix.\n",
           isSymmetric(A, n) ? "" : "not");

    
    printf("(v) Determinant of A = %.2lf\n",
           determinant(A, n));

    
    transposeInPlace(A, n);
    printf("\n(vi) Transpose of A (in place):\n");
    printMatrix(A, n);

    
    double eigenvalues[MAX];
    double V[MAX][MAX];

    
    if (isSymmetric(B, n))
    {
        eigenJacobi(B, n, eigenvalues, V);

        printf("\n(vii) Eigenvalues of B:\n");
        for (int i = 0; i < n; i++)
            printf("%.4lf ", eigenvalues[i]);

        printf("\n\nCorresponding Eigenvectors (columns):\n");
        printMatrix(V, n);
    }
    else
    {
        printf("\n(vii) Eigenvalues/eigenvectors skipped: ");
        printf("Jacobi method requires a symmetric matrix.\n");
    }

    return 0;
}