#include "travailafaire.h"
#include <x86intrin.h>

void scalvec_orig(double scal, double* vec, int N){
    for( int i = 0 ; i < N ; i++ ){
        vec[i] *= scal;
    }
}

void scalvec_sse(double scal, double* vec, int N){
    int i;
    int finVec;
    int reste;
    __m128d registreVecteur;
    __m128d registreScalaire;
    __m128d registreResultat;

    if(0 == N%2){
        finVec = N;
        reste = 0;
    } else {
        finVec = N - N%2;
        reste = 1;
    }

    registreScalaire = _mm_set_pd1(scal);
    for(i = 0 ; i < finVec ; i+=2){
        registreVecteur = _mm_load_pd(&vec[i]);
        registreResultat = _mm_mul_pd(registreVecteur, registreScalaire);
        _mm_store_pd(&vec[i], registreResultat);
    }

    if(1 == reste){
        for(i = finVec ; i < N ; i++){
            vec[i] *= scal;
        }
    }
}

void scalvec_avx(double scal, double* vec, int N){
    int i;
    int finVec;
    int reste;
    __m256d registreVecteur;
    __m256d registreScalaire;
    __m256d registreResultat;

    if(0 == N%4){
        finVec = N;
        reste = 0;
    } else {
        finVec= N - N%4;
        reste = 1;
    }

    registreScalaire = _mm256_set1_pd(scal);
    for(i = 0 ; i < finVec ; i+=4){
        registreVecteur = _mm256_loadu_pd(&vec[i]);
        registreResultat = _mm256_mul_pd(registreVecteur, registreScalaire);
        _mm256_storeu_pd(&vec[i], registreResultat);
    }

    if(1 == reste){
        for(i = finVec ; i < N ; i++){
            vec[i] *= scal;
        }
    }
}


