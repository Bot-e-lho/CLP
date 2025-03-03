#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <time.h>

#define MAXN 2000
int N;
volatile float A[MAXN][MAXN], B[MAXN], X[MAXN];

unsigned int get_seed() {
  struct timeval t;
  struct timezone tz;
  gettimeofday(&t, &tz);
  return (unsigned int)t.tv_usec;
}

void set_params(int argc, char **argv) {
  int s = 0;
  srand(get_seed());
  if(argc == 3) {
    s = atoi(argv[2]);
    srand(s);
    printf("Random seed = %i\n", s);
  }
  if(argc >= 2) {
    N = atoi(argv[1]);
    if(N < 1 || N > MAXN) {
      printf("N = %i is out of range.\n", N);
      exit(0);
    }
  } else {
    printf("Usage: %s <matrix_dimension> [random seed]\n", argv[0]);
    exit(0);
  }
  printf("\nMatrix dimension N = %i.\n", N);
}

void init_inputs() {
  int i, j;
  printf("\nInitializing...\n");
  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      A[i][j] = (float)rand() / 32768.0;
    }
    B[i] = (float)rand() / 32768.0;
    X[i] = 0.0;
  }
}

void print_matrix() {
  int i, j;
  if(N < 10) {
    printf("\nA =\n\t");
    for(i = 0; i < N; i++){
      for(j = 0; j < N; j++){
        printf("%5.2f%s", A[i][j], (j < N - 1) ? ", " : ";\n\t");
      }
    }
    printf("\nB = [");
    for(i = 0; i < N; i++){
      printf("%5.2f%s", B[i], (i < N - 1) ? "; " : "]\n");
    }
  }
}

void print_solution() {
  int i;
  if(N < 100) {
    printf("\nX = [");
    for(i = 0; i < N; i++){
      printf("%5.2f%s", X[i], (i < N - 1) ? "; " : "]\n");
    }
  }
}

void gauss(){
  int i, j, k;
  float f;
  for(i = 0; i < N - 1; i++){
    for(j = i + 1; j < N; j++){
      f = A[j][i] / A[i][i];
      for(k = i + 1; k < N; k++){
        A[j][k] -= f * A[i][k];
      }
      A[j][i] = 0.0;
      B[j] -= f * B[i];
    }
  }
  for(i = N - 1; i >= 0; i--){
    X[i] = B[i];
    for(j = i + 1; j < N; j++){
      X[i] -= A[i][j] * X[j];
    }
    X[i] /= A[i][i];
  }
}

int main(int argc, char **argv){
  struct timeval start, end;
  struct timezone tz;
  clock_t tstart, tend;
  struct tms cstart, cend;
  unsigned long long us_start, us_end;
  set_params(argc, argv);
  init_inputs();
  print_matrix();
  printf("\nStarting clock.\n");
  gettimeofday(&start, &tz);
  tstart = times(&cstart);
  gauss();
  gettimeofday(&end, &tz);
  tend = times(&cend);
  printf("Stopped clock.\n");
  us_start = (unsigned long long)start.tv_sec * 1000000 + start.tv_usec;
  us_end = (unsigned long long)end.tv_sec * 1000000 + end.tv_usec;
  print_solution();
  printf("\nElapsed time = %g ms.\n", (float)(us_end - us_start) / 1000);
  printf("(CPU times are accurate to the nearest %g ms)\n", 1.0 / CLOCKS_PER_SEC * 1000.0);
  printf("My total CPU time for parent = %g ms.\n", (float)((cend.tms_utime + cend.tms_stime) - (cstart.tms_utime + cstart.tms_stime)) / CLOCKS_PER_SEC * 1000);
  printf("My system CPU time for parent = %g ms.\n", (float)(cend.tms_stime - cstart.tms_stime) / CLOCKS_PER_SEC * 1000);
  printf("My total CPU time for child processes = %g ms.\n", (float)((cend.tms_cutime + cend.tms_cstime) - (cstart.tms_cutime + cstart.tms_cstime)) / CLOCKS_PER_SEC * 1000);
  printf("--------------------------------------------\n");
  exit(0);
}
