use rand::Rng;
use std::time::Instant;

const MAXN: usize = 2000;

type Matrix = Vec<Vec<f64>>;
type Vector = Vec<f64>;

fn gauss(a: &mut Matrix, b: &mut Vector, n: usize) -> Vector {
    let mut x = vec![0.0; n];

    // Eliminação
    for norm in 0..n - 1 {
        for row in norm + 1..n {
            let multiplier = a[row][norm] / a[norm][norm];
            for col in norm..n {
                a[row][col] -= a[norm][col] * multiplier;
            }
            b[row] -= b[norm] * multiplier;
        }
    }

    // Substituição reversa
    for row in (0..n).rev() {
        x[row] = b[row];
        for col in row + 1..n {
            x[row] -= a[row][col] * x[col];
        }
        x[row] /= a[row][row];
    }

    x
}

fn main() {
    let n = 5; // Pode mudar para testar tamanhos diferentes
    let mut rng = rand::thread_rng();

    let mut a: Matrix = (0..n)
        .map(|_| (0..n).map(|_| rng.gen_range(-10.0..10.0)).collect())
        .collect();
    let mut b: Vector = (0..n).map(|_| rng.gen_range(-10.0..10.0)).collect();

    println!("Matriz A:");
    for row in &a {
        println!("{:?}", row);
    }
    println!("Vetor B: {:?}", b);

    let start = Instant::now();
    let x = gauss(&mut a, &mut b, n);
    let duration = start.elapsed();

    println!("Solução X: {:?}", x);
    println!("Tempo de execução: {:?}", duration);
}

