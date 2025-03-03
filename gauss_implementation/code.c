#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXN 2000

void gauss(double A[MAXN][MAXN], double B[MAXN], double X[MAXN], int N) {
    for (int norm = 0; norm < N - 1; norm++) {
        for (int row = norm + 1; row < N; row++) {
            double multiplier = A[row][norm] / A[norm][norm];
            for (int col = norm; col < N; col++) {
                A[row][col] -= A[norm][col] * multiplier;
            }
            B[row] -= B[norm] * multiplier;
        }
    }
    for (int row = N - 1; row >= 0; row--) {
        X[row] = B[row];
        for (int col = N - 1; col > row; col--) {
            X[row] -= A[row][col] * X[col];
        }
        X[row] /= A[row][row];
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <matrix_size>\n", argv[0]);
        return -1;
    }
    int N = atoi(argv[1]);
    if (N < 1 || N > MAXN) {
        printf("Matrix size must be between 1 and %d\n", MAXN);
        return -1;
    }
    
    double A[MAXN][MAXN], B[MAXN], X[MAXN];
    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        B[i] = rand() % 100;
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 100;
        }
    }
    
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    
    gauss(A, B, X, N);
    
    clock_gettime(CLOCK_MONOTONIC, &end);
    
    double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Elapsed time: %.6f seconds\n", elapsed);
    
    return 0;
}
