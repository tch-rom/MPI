#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <mpi.h>

bool converge(double *xk, double *xkp, int n, double eps)
{
    bool b = true;
    for (int i = 0; i < n; i++)
    {
        if (fabs(xk[i] - xkp[i]) > eps)
        {
            b = false;
            break;
        }
    }
    return b;
}

int main(int argc, char **argv)
{

    int rank, size;
    int n, i, j, count = 0;
    double **a, *b, *x, *p, var, e;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0)
    {
        printf("Enter the size of the system:\n");
        printf("MATRIX_SIZE = ");
        fflush(stdout);
        scanf("%i", &n);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    a = (double **)malloc(n * sizeof(double *));
    for (i = 0; i < n; i++)
    {
        a[i] = (double *)malloc(n * sizeof(double));
    }

    b = (double *)malloc(n * sizeof(double));
    x = (double *)malloc(n * sizeof(double));
    p = (double *)malloc(n * sizeof(double));

    printf("[Rank %d] Matrix A:\n", rank);
    srand(rank);
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (j == i)
            {
                a[i][j] = 20 + rand() % 100;
            }
            else
            {                            // to prevent convergence
                a[i][j] = rand() % 20;   //
            }
            printf("\t%f", a[i][j]);
        }
        printf("\n");
    }

    printf("[Rank %d] Vector B:\n", rank);
    for (i = 0; i < n; i++)
    {
        b[i] = rand() % 100;
        x[i] = 0;
        printf("%f\n", b[i]);
    }

    e = 1e-5;

    do
    {
        count++;

        for (i = 0; i < n; i++)
        {
            p[i] = x[i];
        }

        for (i = 0; i < n; i++)
        {
            var = 0;
            for (j = 0; j < n; j++)
            {
                if (j != i)
                    var += (a[i][j] * x[j]);
            }
            x[i] = (b[i] - var) / a[i][i];
        }

    } while (!converge(x, p, n, e));

    for (i = 0; i < n; i++)
    {
        free(a[i]);
    }
    free(a);
    free(b);
    free(p);

    MPI_Barrier(MPI_COMM_WORLD);
    printf("[Rank %d] System solution:\n", rank);
    for (i = 0; i < n; i++)
    {
        printf("x[%d] = %.6f\n", i + 1, x[i]);
    }

    free(x);

    MPI_Finalize();
    return 0;
}
