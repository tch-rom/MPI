#include <stdio.h>
#include <mpi.h>

double calculate_partial_sum(int start, int end) {
    double sum = 0.0;

    for (int i = start; i < end; i++) {
        double x = i;
        // calculation of the value of the general term
        double term = (1 + (x + x + 1) * (x + x + 1) * (19 - 14 * x + 3 * x * x - 14 * x + 6 * x * (x + 1) + 3 * (x + 1) * (x + 1))) * (30 + (2 * x - 3 * (x + 1)) * (2 * x - 3 * (x + 1)) * (18 - 32 * x + 12 * x * x + 48 * x - 36 * x * (x + 1) + 27 * (x + 1) * (x + 1))); 
        sum += term;
    }

    return sum;
}


int main(int argc, char** argv) {
    // Initialize MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double total_sum = 0.0;
    double partial_sum = 0.0;

    // Divide partials for each process
    int n = 100;  
    int chunk_size = (n + size - 1) / size; // In case we'd have noninteger number of portions
    //they'd be sliced and nothing will be forgotten
    int start = rank * chunk_size;
    int end = (start + chunk_size) < n ? (start + chunk_size) : n; // to not go outside of the range

    // Sum for each process
    partial_sum = calculate_partial_sum(start, end);

    if (rank != 0) {
        MPI_Send(&partial_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    } else {
        total_sum = partial_sum;

       for (int i = 1; i < size; i ++) {
            double received_sum;
            MPI_Recv(&received_sum, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_sum += received_sum;
        }
        printf("Total sum: %f\n", total_sum);
    }

    MPI_Finalize();

    return 0;
}

