#include "travailafaire.h"
#include <x86intrin.h>
#include <stdio.h>

void matvec_orig(double* rVec, double* A, double* vec, int M, int N) {
    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < N ; j++){
            rVec[i] += A[ i*N + j] * vec[j];
        }
    }
}

void matvec_sse(double* rVec, double* A, double* vec, int M, int N) {
    int finVec;
    int reste;
    __m128d registreVecA;
    __m128d registreVecB;
    __m128d registreResultat;

    if(0 == N%2) {
        finVec = N;
        reste = 0;
    } else {
        finVec= N - N%2;
        reste = 1;
    }

    for(int i = 0 ; i < M ; i++) {
        double temp[2] = {0, 0};
        if (!(N<2)) {
            for (int j = 0; j < finVec; j += 2) {
                registreVecA = _mm_set_pd(A[i * N + j], A[i * N + (j + 1)]);
                registreVecB = _mm_set_pd(vec[j], vec[j + 1]);
                registreResultat = _mm_mul_pd(registreVecA, registreVecB);
                registreVecA = _mm_load_pd((double *) &temp);
                registreVecB = _mm_add_pd(registreVecA, registreResultat);
                _mm_store_pd((double *) &temp, registreVecB);
            }
        }
        if(1 == reste) {
            for(int j = finVec ; j < N ; j++){
                rVec[i] += A[ i*N + j] * vec[j];
            }
        }
        rVec[i] += (temp[0] + temp[1]);
    }
}

void matvec_avx(double* rVec, double* A, double* vec, int M, int N) {
    int finVec;
    int reste;
    __m256d registreVecA;
    __m256d registreVecB;
    __m256d registreResultat;

    if(0 == N%4) {
        finVec = N;
        reste = 0;
    } else {
        finVec= N - N%4;
        reste = 1;
    }

    for(int i = 0 ; i < M ; i++) {
        double temp[4] = {0, 0, 0, 0};
        if (!(N<4)) {
            for (int j = 0; j < finVec; j += 4) {
                registreVecA = _mm256_set_pd(A[i * N + j], A[i * N + (j + 1)], A[i * N + (j + 2)], A[i * N + (j + 3)]);
                registreVecB = _mm256_set_pd(vec[j], vec[j + 1], vec[j + 2], vec[j + 3]);
                registreResultat = _mm256_mul_pd(registreVecA, registreVecB);
                registreVecA = _mm256_load_pd((double *) &temp);
                registreVecB = _mm256_add_pd(registreVecA, registreResultat);
                _mm256_store_pd((double *) &temp, registreVecB);
            }
        }
        if(1 == reste) {
            for(int j = finVec; j < N; j++){
                rVec[i] += A[ i*N + j] * vec[j];
            }
        }
        rVec[i] += (temp[0] + temp[1] + temp[2] + temp[3]);
    }
}