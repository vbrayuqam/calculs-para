#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <x86intrin.h>
#include "matrices.h"
#include "travailafaire.h"

#define DEFAULT_M 8
#define DEFAULT_N 8
#define SCALAIRE  2.5

int main(int argc, char** argv){
    double *vec, *vec_cpy;
    double *A, *B, *C;
    int M = DEFAULT_M, N = DEFAULT_N;
    uint64_t tv1, tv2, tv3, tv4, tv5, tv6, tm1, tm2, tm3, tm4, tm5, tm6, tvm1, tvm2, tvm3, tvm4, tvm5, tvm6;

    if( argc > 1 ){
        M = atoi( argv[ 1 ] );
        if( argc > 2 ){
            N = atoi( argv[ 2 ] );
        } else {
            N = M;
        }
    }
    
    srand( 0 );

    A = allouerMatrice(M, N);
    initMatrice(A, M, N);
    B = allouerMatrice(M, N);
    initMatrice(B, M, N);
    C = allouerMatrice(M, N);
    memset(C, 0, M*N*sizeof( double ));
    
    vec = allouerMatrice(1, N);
    initMatrice(vec, 1, N);

    vec_cpy = allouerMatrice(1, N);
    copierMatrice(vec_cpy, vec, 1, N);

    // Affichage des états d'origine
    printf("\nMATRICE D'ORIGINE A\n");
    afficherMatrice(A, M, N);
    printf("\nMATRICE D'ORIGINE B\n");
    afficherMatrice(B, M, N);
    printf("\nVECTEUR D'ORIGINE\n");
    afficherMatrice(vec, 1, N);

    // scalvec_orig
    tv1 = __rdtsc();
    scalvec_orig(SCALAIRE, vec, N);
    tv2 = __rdtsc();
    printf("\nRESULTAT SCALVEC_ORIG\n");
    afficherMatrice(vec, 1, N);
    copierMatrice(vec, vec_cpy, 1, N);

    // scalvec_sse
    tv3 = __rdtsc();
    scalvec_sse(SCALAIRE, vec, N);
    tv4 = __rdtsc();
    printf("\nRESULTAT SCALVEC_SSE\n");
    afficherMatrice(vec, 1, N);
    copierMatrice(vec, vec_cpy, 1, N);

    // scalvec_axv
    tv5 = __rdtsc();
    scalvec_avx(SCALAIRE, vec, N);
    tv6 = __rdtsc();
    printf("\nRESULTAT SCALVEC_AVX\n");
    afficherMatrice(vec, 1, N);
    copierMatrice(vec, vec_cpy, 1, N);

    // matmult_orig
    tm1 = __rdtsc();
    matmult_orig(C, A, B, M, N, N);
    tm2 = __rdtsc();
    printf("\nRESULTAT MATMULT_ORIG\n");
    afficherMatrice(C, M, N);
    memset(C, 0, M*N*sizeof( double ));

    // matmult_sse
    tm3 = __rdtsc();
    matmult_sse(C, A, B, M, N, N);
    tm4 = __rdtsc();
    printf("\nRESULTAT MATMULT_SSE\n");
    afficherMatrice(C, M, N);
    memset(C, 0, M*N*sizeof( double ));

    // matmult_avx
    tm5 = __rdtsc();
    matmult_avx(C, A, B, M, N, N);
    tm6 = __rdtsc();
    printf("\nRESULTAT MATMULT_AVX\n");
    afficherMatrice(C, M, N);
    memset(C, 0, M*N*sizeof( double ));

    // matvec_orig
    memset(vec_cpy, 0, 1*N*sizeof( double ));
    tvm1 = __rdtsc();
    matvec_orig(vec_cpy, A, vec, M, N);
    tvm2 = __rdtsc();
    printf("\nRESULTAT MATVEC_ORIG\n");
    afficherMatrice(vec_cpy, 1, N);

    // matvec_sse
    memset(vec_cpy, 0, 1*N*sizeof( double ));
    tvm3 = __rdtsc();
    matvec_sse(vec_cpy, A, vec, M, N);
    tvm4 = __rdtsc();
    printf("\nRESULTAT MATVEC_SSE\n");
    afficherMatrice(vec_cpy, 1, N);

    // matvec_avx
    memset(vec_cpy, 0, 1*N*sizeof( double ));
    tvm5 = __rdtsc();
    matvec_avx(vec_cpy, A, vec, M, N);
    tvm6 = __rdtsc();
    printf("\nRESULTAT MATVEC_AVX\n");
    afficherMatrice(vec_cpy, 1, N);

    /* Ajoutez ici l'élimination gaussienne (plusieurs implementations) */

    // Affichage des temps
    printf("\n# OPERATION \t TAILLE \t TEMPS\n" );
    printf("SCALVEC_ORIG \t  %d %d \t %ld\n", M, N, (tv2-tv1));
    printf("SCALVEC_SSE \t  %d %d \t %ld\n", M, N, (tv4-tv3));
    printf("SCALVEC_AVX \t  %d %d \t %ld\n", M, N, (tv6-tv5));
    printf("MATMULT_ORIG \t  %d %d \t %ld\n", M, N, (tm2-tm1));
    printf("MATMULT_SSE \t  %d %d \t %ld\n", M, N, (tm4-tm3));
    printf("MATMULT_AVX \t  %d %d \t %ld\n", M, N, (tm6-tm5));
    printf("MATVEC_ORIG \t  %d %d \t %ld\n", M, N, (tvm2-tvm1));
    printf("MATVEC_SSE \t  %d %d \t %ld\n", M, N, (tvm4-tvm3));
    printf("MATVEC_AVX \t  %d %d \t %ld\n", M, N, (tvm6-tvm5));

    free(A);
    free(B);
    free(C);
    free(vec);
    free(vec_cpy);
    return EXIT_SUCCESS;
}
