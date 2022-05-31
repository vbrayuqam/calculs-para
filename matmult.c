#include "travailafaire.h"
#include <x86intrin.h>

void matmult_orig( double* C, double* A, double* B, int M, int N, int K ) {
    for(int i = 0 ; i < M ; i++){
        for(int j = 0 ; j < N ; j++){
            for(int k = 0 ; k < K ; k++){
                C[ i*N + j] += A[ i*K + k] * B[ k*N + j ];
            }
        }
    }
}

void matmult_sse( double* C, double* A, double* B, int M, int N, int K ) {
    int fin;
    int reste;
    __m128d registreA;
    __m128d registreB;
    __m128d registreResultat;

    if(0 == K%2){
        fin = K;
        reste = 0;
    } else {
        fin = K - K%2;
        reste = 1;
    }

    for(int i = 0 ; i < M ; i++ ){
        for(int j = 0 ; j < N ; j++){
            double temp[2] = {0, 0};
            for(int k = 0 ; k < fin ; k += 2){
                registreA = _mm_set_pd(A[i*K + k], A[i*K + (k+1)]);
                registreB = _mm_set_pd(B[k*N + j], B[((k+1)*N) + j]);
                registreResultat = _mm_mul_pd(registreA, registreB);
                registreA = _mm_load_pd((double *) &temp);
                registreB = _mm_add_pd(registreA, registreResultat);
                _mm_store_pd((double *) &temp, registreB);
            }
            if(1 == reste){
                for(int k = fin ; k < K ; k++){
                    C[ i*N + j] += A[ i*K + k] * B[ k*N + j ];
                }
            }
            C[ i*N + j] += (temp[0] + temp[1]);
        }
    }
}

void matmult_avx( double* C, double* A, double* B, int M, int N, int K ) {
    int fin;
    int reste;
    __m256d registreA;
    __m256d registreB;
    __m256d registreResultat;

    if(0 == K%4){
        fin = K;
        reste = 0;
    } else {
        fin = K - K%4;
        reste = 1;
    }

    for(int i = 0 ; i < M ; i++ ){
        for(int j = 0 ; j < N ; j++) {
            double temp[4] = {0, 0, 0, 0};
            for (int k = 0; k < fin; k += 4) {
                registreA = _mm256_set_pd(A[i * K + k], A[i * K + (k + 1)], A[i * K + (k + 2)], A[i * K + (k + 3)]);
                registreB = _mm256_set_pd(B[k * N + j], B[((k + 1) * N) + j], B[((k + 2) * N) + j],
                                          B[((k + 3) * N) + j]);
                registreResultat = _mm256_mul_pd(registreA, registreB);
                registreA = _mm256_load_pd((double *) &temp);
                registreB = _mm256_add_pd(registreA, registreResultat);
                _mm256_store_pd((double *) &temp, registreB);
            }
            if(1 == reste){
                for(int k = fin ; k < K ; k++){
                    C[ i*N + j] += A[ i*K + k] * B[ k*N + j ];
                }
            }
            C[ i*N + j] += (temp[0] + temp[1] + temp[2] + temp[3]);
        }
    }
}
