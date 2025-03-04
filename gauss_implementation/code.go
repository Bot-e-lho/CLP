// How to run (-n = matrix dimension) (-seed is optional)
// Ex: go run code.go -n 5 -seed 313

//Code
package main

import (
	"flag"
	"fmt"
	"math/rand"
	"time"
)

const MAXN = 2000 // Max value of N

// Gaussian elimination without pivoting
func gauss(A [][]float64, B []float64, X []float64) {
	fmt.Println("Computing serially...")

	N := len(B)

	// Gaussian elimination
	for norm := 0; norm < N-1; norm++ {
		for row := norm + 1; row < N; row++ {
			multiplier := A[row][norm] / A[norm][norm]
			for col := norm; col < N; col++ {
				A[row][col] -= A[norm][col] * multiplier
			}
			B[row] -= B[norm] * multiplier
		}
	}

	// Back substitution
	for row := N - 1; row >= 0; row-- {
		X[row] = B[row]
		for col := N - 1; col > row; col-- {
			X[row] -= A[row][col] * X[col]
		}
		X[row] /= A[row][row]
	}
}

func main() {
	// Parse command-line arguments
	N := flag.Int("n", 0, "Matrix dimension (required)")
	seed := flag.Int64("seed", time.Now().UnixNano(), "Random seed (optional)")
	flag.Parse()

	if *N < 1 || *N > MAXN {
		fmt.Printf("N = %d is out of range.\n", *N)
		return
	}

	fmt.Printf("\nMatrix dimension N = %d.\n", *N)
	fmt.Printf("Random seed = %d\n", *seed)

	// Initialize random number generator
	rand.Seed(*seed)

	// Initialize matrices and vectors
	A := initializeMatrix(*N)
	B := initializeVector(*N)
	X := make([]float64, *N)

	// Print input matrices (for small N)
	if *N < 10 {
		printMatrix("A", A)
		printVector("B", B)
	}

	// Start timing
	start := time.Now()

	// Gaussian Elimination
	gauss(A, B, X)

	// Stop timing
	elapsed := time.Since(start)

	// Print solution vector if N < 100
	if *N < 100 {
		printVector("X", X)
	}

	// Display timing results
	fmt.Printf("\nElapsed time = %.3f ms\n", elapsed.Seconds()*1000)
}

// Initialize matrix A with random values
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

// Initialize vector B with random values
func initializeVector(N int) []float64 {
	fmt.Println("Initializing vector B...")
	B := make([]float64, N)
	for i := range B {
		B[i] = float64(rand.Int31()) / 32768.0 // Int31 to mimic C random
	}
	return B
}

// Print matrix
func printMatrix(name string, matrix [][]float64) {
	fmt.Printf("\n%s =\n", name)
	for _, row := range matrix {
		for _, val := range row {
			fmt.Printf("%12.2f ", val)
		}
		fmt.Println()
	}
}

// Print vector
func printVector(name string, vector []float64) {
	fmt.Printf("\n%s = [", name)
	for _, val := range vector {
		fmt.Printf("%12.2f ", val)
	}
	fmt.Println("]")
}
