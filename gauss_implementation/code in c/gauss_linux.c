#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXN 2000
int N;

float A[MAXN][MAXN], B[MAXN], X[MAXN];

void configurar_parametros(int argc, char **argv) {
    if (argc >= 3) {
        N = atoi(argv[1]);
        int seed = atoi(argv[2]);
        if (N < 1 || N > MAXN) {
            exit(0);
        }
        srand(seed);
    } else {
        exit(0);
    }
}

void inicializar_dados() {
    for (int linha = 0; linha < N; linha++) {
        for (int coluna = 0; coluna < N; coluna++) {
            A[linha][coluna] = (float)rand() / 32768.0;
        }
    }
    
    for (int i = 0; i < N; i++) {
        B[i] = (float)rand() / 32768.0;
        X[i] = 0.0;
    }
}


void gauss() {
    for (int pivo = 0; pivo < N - 1; pivo++) {
        for (int linha = pivo + 1; linha < N; linha++) {
            float multiplicador = A[linha][pivo] / A[pivo][pivo];
            for (int coluna = pivo; coluna < N; coluna++) {
                A[linha][coluna] -= A[pivo][coluna] * multiplicador;
            }
            B[linha] -= B[pivo] * multiplicador;
        }
    }

    for (int linha = N - 1; linha >= 0; linha--) {
        X[linha] = B[linha];
        for (int coluna = N-1; coluna > linha; coluna--) {
            X[linha] -= A[linha][coluna] * X[coluna];
        }
        X[linha] /= A[linha][linha];
    }
}

int main(int argc, char **argv) {
    struct timespec inicio, fim;
    double tempo;
    
    configurar_parametros(argc, argv);
    inicializar_dados();

    clock_gettime(CLOCK_MONOTONIC, &inicio);
    gauss();
    clock_gettime(CLOCK_MONOTONIC, &fim);

    tempo = (fim.tv_sec - inicio.tv_sec) * 1000.0;
    tempo += (fim.tv_nsec - inicio.tv_nsec) / 1000000.0;

    printf("Tempo C: %.3f ms\n", tempo);
    return 0;
}
