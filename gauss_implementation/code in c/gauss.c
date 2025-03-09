#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h>

#define MAXN 20000 

int N;         
float A[MAXN][MAXN], B[MAXN], X[MAXN]; 

void gauss();

void parameters(int argc, char **argv) {
    int seed = 0;

    if (argc < 2) {
        exit(0);
    }

    N = atoi(argv[1]);
    if (N < 1 || N > MAXN) {
        exit(0);
    }

    if (argc == 3) {
        seed = atoi(argv[2]);
        srand(seed);
    } else {
        srand((unsigned int)time(NULL));
    }
}

void initialize_inputs() {
    for (int i = 0; i < N; i++) {
        B[i] = (float)rand() / 32768.0f; 
        for (int j = 0; j < N; j++) {
            A[i][j] = (float)rand() / 32768.0f;
        }
        X[i] = 0.0f;
    }
}

void gauss() {
    int norm, row, col;
    float multiplier;

    for (norm = 0; norm < N - 1; norm++) {
        for (row = norm + 1; row < N; row++) {
            multiplier = A[row][norm] / A[norm][norm];
            for (col = norm; col < N; col++) {
                A[row][col] -= A[norm][col] * multiplier;
            }
            B[row] -= B[norm] * multiplier;
        }
    }

    for (row = N - 1; row >= 0; row--) {
        X[row] = B[row];
        for (col = row + 1; col < N; col++) {
            X[row] -= A[row][col] * X[col];
        }
        X[row] /= A[row][row];
    }
}

int main(int argc, char **argv) {
    LARGE_INTEGER frequency, start, end;
    double elapsed;

    parameters(argc, argv);
    initialize_inputs();

    QueryPerformanceFrequency(&frequency);
    
    QueryPerformanceCounter(&start);
    gauss();
    QueryPerformanceCounter(&end);

    elapsed = (double)(end.QuadPart - start.QuadPart) * 1000.0 / frequency.QuadPart;    
    printf("Tempo C: %.6f ms\n", elapsed);

    return 0;
}
