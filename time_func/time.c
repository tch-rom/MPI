#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

double func(double x) {
    return sin(x);
}

int main(int argc, char** argv){
    int rank, size, num_points, chunk_size;
    double x, *local_result, *result, end_time, start_time;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    start_time = MPI_Wtime();
    if (rank == 0) {
                  // time of the start of calculations

        num_points = (int) (10 / 0.1) + 1; // count the whole number of points
        chunk_size = num_points / size;      // count the number of points per processor

        result = (double*) malloc(num_points * sizeof(double));
    }

    MPI_Bcast(&chunk_size, 1, MPI_INT, 0, MPI_COMM_WORLD);
    local_result = (double*) malloc(chunk_size * sizeof(double));

    // calculate sin(x) on each processor
    for (int i = 0; i < chunk_size; i++) {
        x = rank * chunk_size * 0.1 + i* 0.1; // usage of rank for the uniqueness for every process
        local_result[i] = sin(x);
    }

    // gather all local_results into one result
    MPI_Gather(local_result, chunk_size, MPI_DOUBLE, result, chunk_size, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();
    if (rank == 0) {

        printf("\tsin(x)\n");
        for (int i = 0; i < num_points; i++) {
            printf("%0.1f\t%0.6f\n", i * 0.1, result[i]);
        }

        free(result);
    }

    free(local_result);
    MPI_Barrier(MPI_COMM_WORLD);
    printf("[Rank %d] time: %0.6f seconds\n", rank, end_time - start_time); // time of execution
    MPI_Finalize();
    return 0;
}
