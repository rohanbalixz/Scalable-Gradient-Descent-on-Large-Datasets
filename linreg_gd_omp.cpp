#include <iostream>
#include <fstream>
#include <cstdlib>   // malloc, atof, atoi
#include <cstdio>    // printf, perror
#include <omp.h>
using namespace std;

int main(int argc, char** argv) {
  if (argc != 6) {
    cerr<<"Usage: "<<argv[0]<<" data.csv m0 b0 alpha epochs\n";
    return 1;
  }
  string fname = argv[1];
  double m = atof(argv[2]), b = atof(argv[3]), alpha = atof(argv[4]);
  int epochs = atoi(argv[5]);

  const int MAX_POINTS = 9855000;
  double *x = (double*)malloc(MAX_POINTS*sizeof(double));
  double *y = (double*)malloc(MAX_POINTS*sizeof(double));
  if (!x||!y) { perror("malloc"); return 1; }

  ifstream fin(fname);
  for (int i = 0; i < MAX_POINTS; i++) {
    char comma;
    fin >> x[i] >> comma >> y[i];
  }
  fin.close();

  int M = MAX_POINTS;
  double t0 = omp_get_wtime();
  for (int e = 1; e <= epochs; e++) {
    double dm = 0, db = 0, mse = 0;
    #pragma omp parallel for reduction(+:dm,db,mse)
    for (int i = 0; i < M; i++) {
      double pred = m*x[i] + b;
      double diff = y[i] - pred;
      mse += diff*diff;
      dm  += -2*x[i]*diff;
      db  += -2*diff;
    }
    mse /= M; dm /= M; db /= M;
    m -= alpha * dm;
    b -= alpha * db;
    if (e%1000==0 || e==epochs)
      printf("E%4d T%2d: %.8f, %.8f, %.6f\n",
             e, omp_get_max_threads(), m, b, mse);
  }
  double t1 = omp_get_wtime();
  fprintf(stderr,"Threads=%d Time=%.3f\n",
          omp_get_max_threads(), t1-t0);

  free(x); free(y);
  return 0;
}

