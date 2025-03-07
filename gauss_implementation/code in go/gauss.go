package main

import (
	"flag"
	"fmt"
	"math/rand"
	"os"
	"time"
)

const MAXN = 2000

func gauss(A [][]float32, B []float32, N int) []float32 {
	X := make([]float32, N)

	for norm := 0; norm < N-1; norm++ {
		for row := norm + 1; row < N; row++ {
			multiplier := A[row][norm] / A[norm][norm]
			for col := norm; col < N; col++ {
				A[row][col] -= A[norm][col] * multiplier
			}
			B[row] -= B[norm] * multiplier
		}
	}

	for row := N - 1; row >= 0; row-- {
		X[row] = B[row]
		for col := row + 1; col < N; col++ {
			X[row] -= A[row][col] * X[col]
		}
		X[row] /= A[row][row]
	}
	return X
}

func main() {
	nPtr := flag.Int("n", 0, "dimensão da matriz")
	seedPtr := flag.Int64("seed", 0, "semente para o gerador aleatório")
	flag.Parse()

	if *nPtr < 1 || *nPtr > MAXN {
		fmt.Fprintf(os.Stderr, "Dimensão deve ser entre 1 e %d\n", MAXN)
		os.Exit(0)
	}

	N := *nPtr
	seed := *seedPtr
	if seed == 0 {
		seed = time.Now().Unix()
	}
	rand.Seed(seed)

	A := make([][]float32, N)
	for i := 0; i < N; i++ {
		A[i] = make([]float32, N)
		for j := 0; j < N; j++ {
			A[i][j] = rand.Float32()
		}
	}
	B := make([]float32, N)
	for i := 0; i < N; i++ {
		B[i] = rand.Float32()
	}

	start := time.Now()
	_X := gauss(A, B, N)
	elapsed := time.Since(start)

	fmt.Printf("Tempo Go: %.6f ms\n", float64(elapsed.Nanoseconds())/1e6)
	_ = _X // Não estamos imprimindo X para focar na medição de tempo
}
