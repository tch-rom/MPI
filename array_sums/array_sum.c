#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 100


void generate_data(int* data, int size) {
    for (int i = 0; i < size; i++) {
        data[i] = i + 1;  // Creation of data for array
    }
}

int calculate_partial_sum(int* data, int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++) {
        sum += data[i];  
    }
    return sum;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int data[ARRAY_SIZE];
    int recv_data[ARRAY_SIZE / size];
    int partial_sum = 0;
    int total_sum = 0;

    if (rank == 0) {
        // Generate data in the 0 process
        generate_data(data, ARRAY_SIZE);
    }


    // Scatterv parameters
    int* send_counts = (int*)malloc(sizeof(int) * size);
    int* displacements = (int*)malloc(sizeof(int) * size);

    // Because we could have different kind of portions this should be added to
    for (int i = 0; i < size; i++) {
        send_counts[i] = ARRAY_SIZE / size;
        displacements[i] = i * send_counts[i];
    }

    // Adjust send_counts and displacements for the last process
    send_counts[size - 1] = ARRAY_SIZE - (size - 1) * (ARRAY_SIZE / size);

    MPI_Scatterv(data, send_counts, displacements, MPI_INT, recv_data, send_counts[rank], MPI_INT, 0, MPI_COMM_WORLD);

//    printf("[!] Array of rank %d:\n", rank);
//    for (int i = 0; i < ARRAY_SIZE / size; i++) {
//        printf("%d\t", recv_data[i]);
//    }
//    printf("\n");

    int start = 0;
    int end = send_counts[rank]; // to not go outside of the range

    partial_sum = calculate_partial_sum(recv_data, start, end);

    printf("[+] rank %d\tsum %d\tstart position %d\tend position %d\n", rank, partial_sum, start, end);

    // Process sync
    MPI_Barrier(MPI_COMM_WORLD);

    // Gathering all sums in process rank 0
    MPI_Reduce(&partial_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    free(send_counts);
    free(displacements);

    if (rank == 0) {
        printf("\nTotal sum: %d\n", total_sum);
    }

    MPI_Finalize();

    return 0;
}

