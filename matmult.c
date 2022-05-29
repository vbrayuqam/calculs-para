#include "travailafaire.h"

/* Multiplication matrice-matrice
 * C <- A*B + C
 * C de taille MxN
 * A de taille MxK
 * B de taille KxN
 */

void matmult_orig( double* C, double* A, double* B, int M, int N, int K ){
    for( int i = 0 ; i < M ; i++ ){
        for( int j = 0 ; j < N ; j++ ){
            for( int k = 0 ; k < K ; k++ ){
                C[ i*N + j] += A[ i*K + k] * B[ k*N + j ];
            }
        }
    }
}
