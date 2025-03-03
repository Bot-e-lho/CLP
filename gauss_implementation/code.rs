use rand::Rng;
use std::env;
use std::time::Instant;

const MAXN: usize = 2000;

type Matrix = Vec<Vec<f64>>;
type Vector = Vec<f64>;

fn gauss(a: &mut Matrix, b: &mut Vector, n: usize) -> Vector {
    let mut x = vec![0.0; n];

    for norm in 0..n - 1 {
        for row in norm + 1..n {
            let multiplier = a[row][norm] / a[norm][norm];
            for col in norm..n {
                a[row][col] -= a[norm][col] * multiplier;
            }
            b[row] -= b[norm] * multiplier;
        }
    }

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
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("Usage: {} <matrix_size>", args[0]);
        return;
    }

    let n: usize = args[1].parse().unwrap_or(0);
    if n < 1 || n > MAXN {
        eprintln!("Matrix size must be between 1 and {}", MAXN);
        return;
    }

    let mut rng = rand::thread_rng();
    let mut a: Matrix = (0..n)
        .map(|_| (0..n).map(|_| rng.gen_range(0.0..100.0)).collect())
        .collect();
    let mut b: Vector = (0..n).map(|_| rng.gen_range(0.0..100.0)).collect();

    let start = Instant::now();
    gauss(&mut a, &mut b, n);
    let elapsed = start.elapsed();

    println!("Elapsed time: {:.6} seconds", elapsed.as_secs_f64());
}
