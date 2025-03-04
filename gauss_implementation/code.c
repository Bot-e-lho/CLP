#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void gauss(double *A, double *B, double *X, int N) {
    for (int norm = 0; norm < N - 1; norm++) {
        for (int row = norm + 1; row < N; row++) {
            double multiplier = A[row * N + norm] / A[norm * N + norm];
            for (int col = norm; col < N; col++) {
                A[row * N + col] -= A[norm * N + col] * multiplier;
            }
            B[row] -= B[norm] * multiplier;
        }
    }

    for (int row = N - 1; row >= 0; row--) {
        X[row] = B[row];
        for (int col = row + 1; col < N; col++) {
            X[row] -= A[row * N + col] * X[col];
        }
        X[row] /= A[row * N + row];
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s -n <tamanho da matriz> -seed <semente>\n", argv[0]);
        return -1;
    }

    int N = atoi(argv[2]);
    int seed = atoi(argv[4]);
    if (N < 1 || N > 2000) {
        printf("Tamanho da matriz deve ser entre 1 e 2000\n");
        return -1;
    }

    double *A = malloc(N * N * sizeof(double));
    double *B = malloc(N * sizeof(double));
    double *X = malloc(N * sizeof(double));
    if (!A || !B || !X) {
        printf("Erro de alocação de memória!\n");
        free(A); free(B); free(X);
        return -1;
    }

    srand(seed);
    for (int i = 0; i < N; i++) {
        B[i] = (double)rand() / RAND_MAX * 100.0;
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)rand() / RAND_MAX * 100.0;
        }
    }

    printf("Matriz A:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%6.2f ", A[i * N + j]);
        }
        printf("\n");
    }

    printf("Vetor B: ");
    for (int i = 0; i < N; i++) {
        printf("%6.2f ", B[i]);
    }
    printf("\n");

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    gauss(A, B, X, N);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Vetor solução X: ");
    for (int i = 0; i < N; i++) {
        printf("%6.2f ", X[i]);
    }
    printf("\nTempo de execução: %.6f segundos\n", elapsed);

    free(A); free(B); free(X);
    return 0;
}
