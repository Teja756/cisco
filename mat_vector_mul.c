#include <stdio.h>

#define MAX_SIZE 10

void matrixVectorMultiplication(int matrix[MAX_SIZE][MAX_SIZE], int vector[MAX_SIZE], int size) {
    int result[MAX_SIZE] = { 0 };

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    printf("Resulting vector:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
}

int main() {
    int matrix[MAX_SIZE][MAX_SIZE];
    int vector[MAX_SIZE];
    int size;

    printf("Enter the size of the matrix and vector (maximum %d): ", MAX_SIZE);
    scanf("%d", &size);

    printf("Enter the matrix elements:\n");
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    printf("Enter the vector elements:\n");
    for (int i = 0; i < size; i++) {
        scanf("%d", &vector[i]);
    }

    matrixVectorMultiplication(matrix, vector, size);

    return 0;
}

