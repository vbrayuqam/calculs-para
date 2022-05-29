#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrices.h"

/* Tire un double aléatoire entre a et b 
 */

#define RAND(a,b) a + ( ( b - a + 1 ) * (double)rand() ) / (double) RAND_MAX

/* Alloue une matrice de doubles contenant `lignes` lignes et 
 * `colonnes` colonnes. Retourne un pointeur vers le tableau 
 * alloué.
 * La matrice est allouée comme un tableau d'une dimension.
 */

double* allouerMatrice( int lignes, int colonnes ){
    double* mat = (double*) malloc( lignes*colonnes*sizeof( double ) );
    return mat;
}

/* Initialise la matrice passée en paramètre avec des valeurs 
 * aléatoires entre -100 et 100.
 */

void initMatrice( double* mat, int lignes, int colonnes ){
    for( int i = 0 ; i < lignes*colonnes ; i++ ){
        mat[i] = RAND( -100, 100 );
    }
}

/* Affiche la matrice ligne par ligne
 */

void afficherMatrice( double* mat, int lignes, int colonnes ){
    for( int i = 0 ; i < lignes ; i++ ){
        for( int j = 0 ; j < colonnes ; j++ ){
            printf( "%.2lf   ", mat[ i*colonnes + j ] );
        }
        printf( "\n" );
    }
}

/* Affiche la matrice au format d'Octave. On affiche avec davantage 
 * de décimales pour réduire l'erreur d'arrondi quand on vérifiera
 * avec Octave.
 */

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

/* Copie le contenu d'une matrice dans une autre */

void copierMatrice( double* out, double* in, int lignes, int colonnes ){
    memcpy( out, in, lignes*colonnes*sizeof( double ) );
}
