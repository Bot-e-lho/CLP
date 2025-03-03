package main

import (
	"flag"
	"fmt"
	"math/rand"
	"time"
)

const MAXN = 2000 // Max value of N

func gauss(A [][]float64, B []float64, X []float64) {
	fmt.Println("Computing serially...")

	N := len(B)

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
		for col := N - 1; col > row; col-- {
			X[row] -= A[row][col] * X[col]
		}
		X[row] /= A[row][row]
	}
}

func main() {
	N := flag.Int("n", 0, "Matrix dimension (required)")
	seed := flag.Int64("seed", time.Now().UnixNano(), "Random seed (optional)")
	flag.Parse()

	if *N < 1 || *N > MAXN {
		fmt.Printf("N = %d is out of range.\n", *N)
		return
	}

	fmt.Printf("\nMatrix dimension N = %d.\n", *N)
	fmt.Printf("Random seed = %d\n", *seed)

	rand.Seed(*seed)

	A := initializeMatrix(*N)
	B := initializeVector(*N)
	X := make([]float64, *N)

	if *N < 10 {
		printMatrix("A", A)
		printVector("B", B)
	}

	start := time.Now()

	gauss(A, B, X)

	elapsed := time.Since(start)

	if *N < 100 {
		printVector("X", X)
	}

	fmt.Printf("\nElapsed time = %.3f ms\n", elapsed.Seconds()*1000)
}

func initializeMatrix(N int) [][]float64 {
	fmt.Println("\nInitializing matrix A...")
	A := make([][]float64, N)
	for i := range A {
		A[i] = make([]float64, N)
		for j := range A[i] {
			A[i][j] = float64(rand.Int31()) / 32768.0 // Int31 to mimic C random
		}
	}
	return A
}

func initializeVector(N int) []float64 {
	fmt.Println("Initializing vector B...")
	B := make([]float64, N)
	for i := range B {
		B[i] = float64(rand.Int31()) / 32768.0 // Int31 to mimic C random
	}
	return B
}

func printMatrix(name string, matrix [][]float64) {
	fmt.Printf("\n%s =\n", name)
	for _, row := range matrix {
		for _, val := range row {
			fmt.Printf("%12.2f ", val)
		}
		fmt.Println()
	}
}

func printVector(name string, vector []float64) {
	fmt.Printf("\n%s = [", name)
	for _, val := range vector {
		fmt.Printf("%12.2f ", val)
	}
	fmt.Println("]")
}
