#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX_SIZE 10

void matrixVectorMultiplication(int *localMatrix, int *vector, int *localResult, int localSize, int size) {
    for (int i = 0; i < localSize; i++) {
        localResult[i] = 0;
        for (int j = 0; j < size; j++) {
            localResult[i] += localMatrix[i * size + j] * vector[j];
        }
    }
}

int main(int argc, char *argv[]) {
    int size, rank;
    int matrix[MAX_SIZE][MAX_SIZE];
    int vector[MAX_SIZE];
    int localMatrix[MAX_SIZE * MAX_SIZE];
    int localVector[MAX_SIZE];
    int localResult[MAX_SIZE];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int localSize = MAX_SIZE / size;
    if (MAX_SIZE % size != 0 && rank == 0) {
        printf("Number of processes must be divisible by MAX_SIZE.\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    if (rank == 0) {
        printf("Enter the matrix elements:\n");
        for (int i = 0; i < MAX_SIZE; i++) {
            for (int j = 0; j < MAX_SIZE; j++) {
                scanf("%d", &matrix[i][j]);
            }
        }

        printf("Enter the vector elements:\n");
        for (int i = 0; i < MAX_SIZE; i++) {
            scanf("%d", &vector[i]);
        }
    }

    MPI_Scatter(matrix, localSize * MAX_SIZE, MPI_INT, localMatrix, localSize * MAX_SIZE, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(vector, localSize, MPI_INT, localVector, localSize, MPI_INT, 0, MPI_COMM_WORLD);

    matrixVectorMultiplication(localMatrix, localVector, localResult, localSize, MAX_SIZE);

    int *result = NULL;
    if (rank == 0) {
        result = (int *)malloc(MAX_SIZE * sizeof(int));
    }

    MPI_Gather(localResult, localSize, MPI_INT, result, localSize, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Resulting vector:\n");
        for (int i = 0; i < MAX_SIZE; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
        free(result);
    }

    MPI_Finalize();
    return 0;
}

