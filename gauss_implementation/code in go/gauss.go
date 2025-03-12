package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

const MAXN = 2000

var N int
var A [][]float32
var B []float32
var X []float32

func configurarParametros() {
	if len(os.Args) >= 3 {
		n, err := strconv.Atoi(os.Args[1])
		seed, errSeed := strconv.ParseInt(os.Args[2], 10, 64)
		if err != nil || n < 1 || n > MAXN || errSeed != nil {
			os.Exit(0)
		}
		N = n
		rand.Seed(seed)
	} else {
		os.Exit(0)
	}
}

func inicializarDados() {
	A = make([][]float32, N)
	for i := 0; i < N; i++ {
		A[i] = make([]float32, N)
		for j := 0; j < N; j++ {
			A[i][j] = rand.Float32() / 32768.0
		}
	}

	B = make([]float32, N)
	X = make([]float32, N)
	for i := 0; i < N; i++ {
		B[i] = rand.Float32() / 32768.0
		X[i] = 0.0
	}
}

func gauss() {
	for pivo := 0; pivo < N-1; pivo++ {
		for linha := pivo + 1; linha < N; linha++ {
			multiplicador := A[linha][pivo] / A[pivo][pivo]
			for coluna := pivo; coluna < N; coluna++ {
				A[linha][coluna] -= A[pivo][coluna] * multiplicador
			}
			B[linha] -= B[pivo] * multiplicador
		}
	}

	for linha := N - 1; linha >= 0; linha-- {
		X[linha] = B[linha]
		for coluna := N - 1; coluna > linha; coluna-- {
			X[linha] -= A[linha][coluna] * X[coluna]
		}
		X[linha] /= A[linha][linha]
	}
}

func main() {
	configurarParametros()
	inicializarDados()

	inicio := time.Now()
	gauss()
	tempo := time.Since(inicio).Seconds() * 1000.0

	fmt.Printf("Tempo de execucao: %.3f\n", tempo)
}
