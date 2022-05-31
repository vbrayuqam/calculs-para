//Multiplications scalaire-vecteur

void scalvec_orig(double, double*, int);
void scalvec_sse(double, double*, int);
void scalvec_avx(double, double*, int);

//Multiplications matrice-matrice

void matmult_orig(double*, double*, double*, int, int, int);
void matmult_sse(double*, double*, double*, int, int, int);
void matmult_avx(double*, double*, double*, int, int, int);

//Multiplications vecteur-matrice
void matvec_orig(double*, double*, double*, int, int);
void matvec_sse(double*, double*, double*, int, int);
void matvec_avx(double*, double*, double*, int, int);

//Elimination Gaussienne
