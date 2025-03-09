use rand::{Rng};
use rand::rngs::StdRng;
use rand::SeedableRng;
use std::env;
use std::time::Instant;

fn gauss(a: &mut Vec<Vec<f32>>, b: &mut Vec<f32>, n: usize) -> Vec<f32> {
    for norm in 0..n - 1 {
        for row in norm + 1..n {
            let multiplier = a[row][norm] / a[norm][norm];
            for col in norm..n {
                a[row][col] -= a[norm][col] * multiplier;
            }
            b[row] -= b[norm] * multiplier;
        }
    }

    let mut x = vec![0.0f32; n];
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
        eprintln!("Uso: {} <dimensão> [semente]", args[0]);
        std::process::exit(0);
    }

    let n: usize = args[1].parse().expect("Dimensão inválida");
    if n < 1 || n > 20000 {
        eprintln!("Dimensão deve ser entre 1 e 20000");
        std::process::exit(0);
    }

    let seed: u64 = if args.len() >= 3 {
        args[2].parse().expect("Seed inválida")
    } else {
        use std::time::{SystemTime, UNIX_EPOCH};
        SystemTime::now().duration_since(UNIX_EPOCH).unwrap().as_secs()
    };

    let mut rng = StdRng::seed_from_u64(seed);

    let mut a: Vec<Vec<f32>> = (0..n)
        .map(|_| (0..n).map(|_| rng.r#gen::<f32>()).collect())
        .collect();
    let mut b: Vec<f32> = (0..n).map(|_| rng.r#gen::<f32>()).collect();

    let start = Instant::now();
    let _x = gauss(&mut a, &mut b, n);
    let elapsed = start.elapsed();

    println!("Tempo Rust: {:.6} ms", elapsed.as_secs_f64() * 1e3);
}
