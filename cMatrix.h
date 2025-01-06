#ifndef cMatrix_H
#define cMatrix_H

typedef struct Matrix {
    int R;
    int C;
    float* grid;
} Matrix;

void initMatrix(Matrix* mat);
void killMatrix(Matrix* mat);
void matrixEntry(Matrix* mat);
void IdentityMat(Matrix* mat, __uint8_t size);
void scale_matrix(Matrix* matAns, float scalar, Matrix mat);
void addMatrices(Matrix* matAns, Matrix* mat1, Matrix* mat2);
void subtractMatrices(Matrix* matAns, Matrix* mat1, Matrix* mat2);
void multiplyMatrices(Matrix* matAns, Matrix* mat1, Matrix* mat2);
void rowEchleonUpper(Matrix* matAns, Matrix mat);
void rowEchleonLower(Matrix* matAns, Matrix mat);
int trace(float* sum, Matrix mat);
int determinant(float* det, Matrix mat);
void inverse(Matrix* matAns, Matrix mat);
void char_poly(Matrix* matAns, Matrix mat);
void printMatrix(Matrix* mat);

#endif