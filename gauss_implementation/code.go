package main

import (
    "fmt"
    "math/rand"
    "os"
    "strconv"
    "time"
)

const MAXN = 2000

type Matrix [][]float64
type Vector []float64

func gauss(a Matrix, b Vector, n int) Vector {
    x := make(Vector, n)
    for norm := 0; norm < n-1; norm++ {
        for row := norm + 1; row < n; row++ {
            multiplier := a[row][norm] / a[norm][norm]
            for col := norm; col < n; col++ {
                a[row][col] -= a[norm][col] * multiplier
            }
            b[row] -= b[norm] * multiplier
        }
    }
    for row := n - 1; row >= 0; row-- {
        x[row] = b[row]
        for col := row + 1; col < n; col++ {
            x[row] -= a[row][col] * x[col]
        }
        x[row] /= a[row][row]
    }
    return x
}

func main() {
    if len(os.Args) < 2 {
        fmt.Println("Usage: go run main.go <matrix_size>")
        return
    }
    n, err := strconv.Atoi(os.Args[1])
    if err != nil || n < 1 || n > MAXN {
        fmt.Printf("Matrix size must be between 1 and %d\n", MAXN)
        return
    }
    
    a := make(Matrix, n)
    b := make(Vector, n)
    for i := 0; i < n; i++ {
        a[i] = make(Vector, n)
        for j := 0; j < n; j++ {
            a[i][j] = rand.Float64() * 100
        }
        b[i] = rand.Float64() * 100
    }
    
    start := time.Now()
    gauss(a, b, n)
    elapsed := time.Since(start)
    
    fmt.Printf("Elapsed time: %.6f seconds\n", elapsed.Seconds())
}
