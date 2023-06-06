#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include <mpi.h>

int main(int argc, char** argv){

    int rank, size;
    int n, i, j, count = 0;
    float **a, *b, *x, *tmp_x, exp, e;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if ( rank == 0) {
        printf("Enter the size of the system:\n");
        printf("MATRIX_SIZE = ");
        fflush(stdout);
        scanf("%i", &n);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    a = (float**)malloc(n*sizeof(float*));
    for(i = 0; i < n; i++){
        a[i] = (float*)malloc(n*sizeof(float));
    }

    b = (float*)malloc(n*sizeof(float));
    x = (float*)malloc(n*sizeof(float));
    tmp_x = (float*)malloc(n*sizeof(float));

    printf("[Rank %d] Matrix A:\n", rank);
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if ( j == i ){
                a[i][j] = 20 + rand() % 100;    //
            } else {                            //  to prevent convergence
                a[i][j] = rand() % 20;          //
            }
            printf("\t%f", a[i][j]);
        }
        printf("\n");
    }

    printf("[Rank %d] Vector B:\n", rank);
    for(i = 0; i < n; i++){
        b[i] = rand() % 100;
        x[i] = 0;
        printf("%f\n", b[i]);
    }

    e = 1e-5;

    do{
        count++;

        for(i = 0; i < n; i++){
            tmp_x[i] = 0.0;
            for(j = 0; j < n; j++){
                if(i != j){
                    tmp_x[i] = tmp_x[i] + (a[i][j] * x[j]);
                }
            }
            tmp_x[i] = (b[i] - tmp_x[i]) / a[i][i];
        }

        exp = 0;

        for(i = 0; i < n; i++){
            if(fabs(x[i] - tmp_x[i]) > exp){
                exp = fabs(x[i] - tmp_x[i]);
            }
            x[i] = tmp_x[i];
        }
    } while(exp > e);

    free(tmp_x);
    for(i = 0; i < n; i++){
        free(a[i]);
    }
    free(a);
    free(b);

    MPI_Barrier(MPI_COMM_WORLD);
    printf("[Rank %d] System solution:\n", rank);
    for(i = 0; i < n; i++){
        printf("x[%d] = %.6f\n", i+1, x[i]);
    }

    free(x);

    MPI_Finalize();
    return 0;
}
