#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrices.h"

#define RAND(a,b) a + ( ( b - a + 1 ) * (double)rand() ) / (double) RAND_MAX

double* allouerMatrice( int lignes, int colonnes ){
    double* mat = (double*) malloc( lignes*colonnes*sizeof( double ) );
    return mat;
}

void initMatrice( double* mat, int lignes, int colonnes ){
    for( int i = 0 ; i < lignes*colonnes ; i++ ){
        mat[i] = RAND( -100, 100 );
    }
}

void afficherMatrice( double* mat, int lignes, int colonnes ){
    for( int i = 0 ; i < lignes ; i++ ){
        for( int j = 0 ; j < colonnes ; j++ ){
            printf( "%.2lf   ", mat[ i*colonnes + j ] );
        }
        printf( "\n" );
    }
}

void afficherMatriceOctave( double* mat, int lignes, int colonnes ){
    printf( "[ " );
    for( int i = 0 ; i < lignes ; i++ ){
        printf( "[ " );
        for( int j = 0 ; j < colonnes ; j++ ){
            printf( "%lf ", mat[ i*colonnes + j ] );
        }
        printf( " ] " );
        if( i < lignes - 1 ){
            printf( "; " );
        }
    }
    printf( " ]\n" );
}

void copierMatrice( double* out, double* in, int lignes, int colonnes ){
    memcpy( out, in, lignes*colonnes*sizeof( double ) );
}
