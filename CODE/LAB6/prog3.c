#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct
{
    double real;
    double imag;
} Complex;


Complex add(Complex a, Complex b)
{
    Complex c;
    c.real = a.real + b.real;
    c.imag = a.imag + b.imag;
    return c;
}


Complex subtract(Complex a, Complex b)
{
    Complex c;
    c.real = a.real - b.real;
    c.imag = a.imag - b.imag;
    return c;
}


Complex multiply(Complex a, Complex b)
{
    Complex c;
    c.real = a.real * b.real - a.imag * b.imag;
    c.imag = a.real * b.imag + a.imag * b.real;
    return c;
}


void FFT(Complex a[], int n, int invert)
{
    
    for (int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;

        while (j & bit)
        {
            j ^= bit;
            bit >>= 1;
        }

        j ^= bit;

        if (i < j)
        {
            Complex temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    
    for (int len = 2; len <= n; len <<= 1)
    {
        double angle = 2 * PI / len;

        if (invert)
            angle = -angle;

        Complex wlen;
        wlen.real = cos(angle);
        wlen.imag = sin(angle);

        for (int i = 0; i < n; i += len)
        {
            Complex w;
            w.real = 1.0;
            w.imag = 0.0;

            for (int j = 0; j < len / 2; j++)
            {
                Complex u = a[i + j];
                Complex v = multiply(a[i + j + len / 2], w);

                a[i + j] = add(u, v);
                a[i + j + len / 2] = subtract(u, v);

                w = multiply(w, wlen);
            }
        }
    }

   
    if (invert)
    {
        for (int i = 0; i < n; i++)
        {
            a[i].real /= n;
            a[i].imag /= n;
        }
    }
}


void convolution(double A[], int m, double B[], int n,
                 double C[])
{
    int resultSize = m + n - 1;
    int N = 1;

    
    while (N < resultSize)
        N <<= 1;

    Complex *FA = calloc(N, sizeof(Complex));
    Complex *FB = calloc(N, sizeof(Complex));

    
    for (int i = 0; i < m; i++)
        FA[i].real = A[i];

    for (int i = 0; i < n; i++)
        FB[i].real = B[i];

   
    FFT(FA, N, 0);
    FFT(FB, N, 0);

   
    for (int i = 0; i < N; i++)
        FA[i] = multiply(FA[i], FB[i]);

    
    FFT(FA, N, 1);

    
    for (int i = 0; i < resultSize; i++)
        C[i] = FA[i].real;

    free(FA);
    free(FB);
}

int main()
{
    int m, n;

    printf("Enter length of vector A: ");
    scanf("%d", &m);

    printf("Enter length of vector B: ");
    scanf("%d", &n);

    if (n < m)
    {
        printf("Error: n must be greater than or equal to m.\n");
        return 1;
    }

    double *A = malloc(m * sizeof(double));
    double *B = malloc(n * sizeof(double));
    double *C = malloc((m + n - 1) * sizeof(double));

    printf("Enter %d elements of A:\n", m);
    for (int i = 0; i < m; i++)
        scanf("%lf", &A[i]);

    printf("Enter %d elements of B:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%lf", &B[i]);

    convolution(A, m, B, n, C);

    printf("\nConvolution of A and B:\n");

    for (int i = 0; i < m + n - 1; i++)
        printf("C[%d] = %.2f\n", i, C[i]);

    free(A);
    free(B);
    free(C);

    return 0;
}