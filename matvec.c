#include "travailafaire.h"
#include <x86intrin.h>

void matvec_orig(double* C, double* A, double* vec, int M, int N) {
    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < N ; j++){
            C[ i*N + j] += A[ i + j] * vec[ j*N + j ];
        }
    }
}
void matvec_sse(double* C, double* A, double* vec, int M, int N) {
    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < N ; j++){
            C[ i*N + j] += A[ i + j] * vec[ j*N + j ];
        }
    }
}
void matvec_avx(double* C, double* A, double* vec, int M, int N) {
    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < N ; j++){
            C[ i*N + j] += A[ i + j] * vec[ j*N + j ];
        }
    }
}