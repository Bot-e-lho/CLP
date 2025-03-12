use std::env;
use std::process;
use std::time::Instant;
use rand::{Rng, SeedableRng};
use rand::rngs::StdRng;

const MAXN: usize = 2000;

fn configurar_parametros() -> (usize, u64) {
    let args: Vec<String> = env::args().collect();
    if args.len() < 3 {
        process::exit(0);
    }
    let n: usize = args[1].parse().unwrap_or(0);
    let seed: u64 = args[2].parse().unwrap_or(0);
    if n < 1 || n > MAXN {
        process::exit(0);
    }
    (n, seed)
}

fn inicializar_dados(n: usize, seed: u64) -> (Vec<Vec<f32>>, Vec<f32>, Vec<f32>) {
    let mut rng = StdRng::seed_from_u64(seed); 
    let mut a: Vec<Vec<f32>> = vec![vec![0.0; n]; n];
    for linha in 0..n {
        for coluna in 0..n {
            a[linha][coluna] = rng.r#gen::<f32>() / 32768.0;
        }
    }
    let mut b: Vec<f32> = vec![0.0; n];
    let x: Vec<f32> = vec![0.0; n];
    for i in 0..n {
        b[i] = rng.r#gen::<f32>() / 32768.0;
    }
    (a, b, x)
}

fn gauss(n: usize, a: &mut Vec<Vec<f32>>, b: &mut Vec<f32>, x: &mut Vec<f32>) {
    for pivo in 0..n - 1 {
        for linha in pivo + 1..n {
            let multiplicador = a[linha][pivo] / a[pivo][pivo];
            for coluna in pivo..n {
                a[linha][coluna] -= a[pivo][coluna] * multiplicador;
            }
            b[linha] -= b[pivo] * multiplicador;
        }
    }

    for linha in (0..n).rev() {
        x[linha] = b[linha];
        for coluna in ((linha + 1)..n).rev() {
            x[linha] -= a[linha][coluna] * x[coluna];
        }
        x[linha] /= a[linha][linha];
    }
}


fn main() {
    let (n, seed) = configurar_parametros();
    let (mut a, mut b, mut x) = inicializar_dados(n, seed);

    let inicio = Instant::now();
    gauss(n, &mut a, &mut b, &mut x);
    let duracao = inicio.elapsed();
    println!("{:.3}", duracao.as_secs_f64() * 1000.0);
}
