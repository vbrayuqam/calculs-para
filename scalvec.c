#include <stdio.h> /* Pour les printf. Vous ne devriez plus en avoir besoin ensuite */
#include "travailafaire.h"

/* Multiplie un vecteur par un scalaire. Le vecteur est
 * de taille N. Vous devez en implémenter d'autres */

void scalvec_orig( double scal, double* vec, int N ){
    for( int i = 0 ; i < N ; i++ ){
        vec[i] *= scal;
    }
}

void scalvec_sse( double scal, double* vec, int N ){
    printf( "Implémentez ici\n" );
}

void scalvec_avx( double scal, double* vec, int N ){
    printf( "Implémentez ici\n" );
}


