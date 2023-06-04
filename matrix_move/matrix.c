#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MATRIX_SIZE 4

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int matrix[MATRIX_SIZE][MATRIX_SIZE];

    // Generate diagonal matrix in the root process
    if (rank == 0) {
        for (int i = 0; i < MATRIX_SIZE; i++) {
            for (int j = 0; j < MATRIX_SIZE; j++) {
                if (i <= j) {
                    matrix[i][j] =rand() % 100 ;
                } else {
                    matrix[i][j] = 0;
                }
                printf("\t%d", matrix[i][j]);
            }
            printf("\n");
        }
    }

    // Create MPI datatype for diagonal matrix
    MPI_Datatype diag_type;
    MPI_Type_vector(MATRIX_SIZE, 1, MATRIX_SIZE, MPI_INT, &diag_type);
    MPI_Type_commit(&diag_type);


     // Scatterv parameters
    int* send_counts = (int*)malloc(sizeof(int) * size);
    int* displacements = (int*)malloc(sizeof(int) * size);

    // Because we could have different kind of portions this should be added to
    for (int i = 0; i < size; i++) {
        send_counts[i] = MATRIX_SIZE*MATRIX_SIZE / size;
        displacements[i] = i * send_counts[i];
    }

    // Adjust send_counts and displacements for the last process
    send_counts[size - 1] = MATRIX_SIZE*MATRIX_SIZE - (size - 1) * (MATRIX_SIZE*MATRIX_SIZE / size);

    //MPI_Scatterv(data, send_counts, displacements, MPI_INT, recv_data, send_counts[rank], MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter the diagonal elements of the matrix to all processes
    int recv_data[MATRIX_SIZE*MATRIX_SIZE];
    MPI_Scatterv(matrix, send_counts, displacements, MPI_INT, recv_data, send_counts[rank], MPI_INT, 0, MPI_COMM_WORLD);

    // Print the received data
    printf("[Rank %d] Received data: ", rank);
    for (int i = 0; i < send_counts[rank]; i++) {
        printf("%d ", recv_data[i]);
    }
    printf("\n");

    // Cleanup
    MPI_Type_free(&diag_type);
    MPI_Finalize();

    return 0;
}
