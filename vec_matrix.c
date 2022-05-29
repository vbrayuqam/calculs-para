#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // pour uint64_t
#include <string.h> // pour memset
#include <x86intrin.h>

#include "matrices.h"
#include "travailafaire.h"

#define DEFAULT_M 8
#define DEFAULT_N 8
#define SCALAIRE  2.5

int main( int argc, char** argv ){
    double *vec, *vec_cpy;
    double *A, *B, *C;
    int M = DEFAULT_M, N = DEFAULT_N;
    uint64_t tv1, tv2, tv3, tv4, tv5, tv6, tm1, tm2;


    /* On regarde si l'utilisateur a passé une taille en paramètre */

    if( argc > 1 ){
        M = atoi( argv[ 1 ] );
        if( argc > 2 ){
            N = atoi( argv[ 2 ] );
        } else {
            /* Si l'utilisateur ne passe qu'un paramètre sur la ligne
               de commande, on utilise une matrice carrée */
            N = M;
        }
    }

    /* Initialisation du générateur de nombres aléatoires
       sur une valeur fixe (reproductibilité de l'aléa) */
    
    srand( 0 );

    /* Initialisation de la matrice et du vecteur */

    A = allouerMatrice( M, N );
    initMatrice( A, M, N );
    B = allouerMatrice( M, N );
    initMatrice( B, M, N );
    C = allouerMatrice( M, N );
    memset( C, 0, M*N*sizeof( double ) ); // on l'initialise à 0
    
    vec = allouerMatrice( 1, N );
    initMatrice( vec, 1, N );
    
    /* On garde une copie du vecteur */
    vec_cpy = allouerMatrice( 1, N );
    copierMatrice( vec_cpy, vec, 1, N );

    /* On affiche la matrice  et le vecteur */

    printf("\nMATRICE D'ORIGINE\n");
    afficherMatrice( A, M, N );
    printf("\nVECTEUR D'ORIGINE\n");
    afficherMatrice( vec, 1, N );

    /* On commence les choses intéressantes : multiplication scalaire-vecteur */

    /* scalvec_orig */
    tv1 = __rdtsc();
    scalvec_orig( SCALAIRE, vec, N );
    tv2 = __rdtsc();
    printf("\nRESULTAT SCALVEC_ORIG\n");
    afficherMatrice( vec, 1, N );
    copierMatrice( vec, vec_cpy, 1, N );

    /* scalvec_sse */
    tv3 = __rdtsc();
    scalvec_sse( SCALAIRE, vec, N );
    tv4 = __rdtsc();
    printf("\nRESULTAT SCALVEC_SSE\n");
    afficherMatrice( vec, 1, N );
    copierMatrice( vec, vec_cpy, 1, N );

    /*scalvec_axv*/
    tv5 = __rdtsc();
    scalvec_avx( SCALAIRE, vec, N );
    tv6 = __rdtsc();
    printf("\nRESULTAT SCALVEC_AVX\n");
    afficherMatrice( vec, 1, N );
    copierMatrice( vec, vec_cpy, 1, N );


    /* On l'affiche au format Octave, pour pouvoir 
       la copier-coller dans Octave */
    
    afficherMatriceOctave( A, M, N );

    /* Multiplications matrice-matrice */
    
    tm1 = __rdtsc();
    matmult_orig( C, A, B, M, N, N );
    tm2 = __rdtsc();

    /* Verification */
    
    printf( " A = " );
    afficherMatriceOctave( A, M, N );
    printf( " B = " );
    afficherMatriceOctave( B, N, N );
    printf( " C = " );
    afficherMatriceOctave( C, M, N );
    
    /* Ajoutez ici les autres implementations */

    /* Ajoutez ici les produits vecteur-matrice */

    /* Ajoutez ici l'élimination gaussienne (plusieurs implementations) */

    
    /* Affichage des temps */

    printf( "# OPERATION \t TAILLE \t TEMPS\n" );
    printf( "SCALVEC_ORIG \t  %d %d \t %ld\n", M, N, (tv2-tv1) );
    printf( "SCALVEC_SSE \t  %d %d \t %ld\n", M, N, (tv4-tv3) );
    printf( "SCALVEC_AVX \t  %d %d \t %ld\n", M, N, (tv6-tv5) );
    printf( "MATMULT1 \t  %d %d \t %ld\n", M, N, (tm2-tm1) );

    free( A );
    free( B );
    free( C );
    free( vec );
    free( vec_cpy );
    return EXIT_SUCCESS;
}
