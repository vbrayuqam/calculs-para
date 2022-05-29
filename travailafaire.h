/* Multiplications scalaire-vecteur */

void scalvec_orig( double, double*, int );
void scalvec_sse( double, double*, int );
void scalvec_avx( double, double*, int );

/* Multiplications matrice-matrice */

void matmult_orig( double*, double*, double*, int, int, int );

/* Multiplications vecteur-matrice */

/* Elimination Gaussienne */
