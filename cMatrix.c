#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix {
    int R;
    int C;
    float* grid;
} Matrix;

void initMatrix(Matrix* mat) {
    if((mat->R > 0) || (mat->C > 0)) {
        return;
    }
    do {
        printf("Enter number of rows: ");
        scanf("%d",&(mat->R));
        printf("Enter number of columns: ");
        scanf("%d",&(mat->C));
    } while(!((mat->R > 0) && (mat->C > 0)));

    mat->grid = (float*)calloc(mat->R*mat->C, sizeof(float));
}

void killMatrix(Matrix* mat) {
    if(((mat->R > 0) && (mat->C > 0))) {
        mat->R = 0;
        mat->C = 0;
        free(mat->grid);
    }
    else {
        return;
    }
}

void matrixEntry(Matrix* mat) {
    for(int i = 0;i < mat->R*mat->C; i++) {
        printf("ROW%d, COLUMN%d = ", i/mat->C, i%mat->C);
        scanf("%f", &mat->grid[i]);
    }
}

void IdentityMat(Matrix* mat, __uint8_t size) {
    mat->R = size;
    mat->C = size;
    mat->grid = (float*)calloc(mat->R*mat->C, sizeof(float));
    for(int i = 0;i < mat->R*mat->C; i++) {
        mat->grid[i*mat->C + i] = 1;
    }
}

void scale_matrix(Matrix* matAns, float scalar, Matrix mat) {
    matAns->R = mat.R;
    matAns->C = mat.C;
    matAns->grid = (float*)calloc(mat.R*mat.C, sizeof(float));
    for(int i = 0; i < mat.R; i++) {
        for(int j = 0; j < mat.C; j++) {
            matAns->grid[i*mat.C + j] = scalar*mat.grid[i*mat.C + j];
        }
    }
}

void addMatrices(Matrix* matAns, Matrix* mat1, Matrix* mat2) {
    if((mat1-> R == mat2->R) && (mat1->C == mat2->C)) {
        matAns->R = mat1->R;
        matAns->C = mat1->C;
        matAns->grid = (float*)calloc(matAns->R*matAns->C, sizeof(float));
        for(int i = 0;i < matAns->R*matAns->C; i++) {
            matAns->grid[i] = mat1->grid[i] + mat2->grid[i];
        }
    }
    else if((mat1-> R == 0) || (mat1->C == 0)) {
        printf("mat1 not initialised.\n");
    }
    else if((mat2-> R == 0) || (mat2->C == 0)) {
        printf("mat2 not initialised.\n");
    }
    else {
        printf("Size mismatch.\n");
    }
}

void subtractMatrices(Matrix* matAns, Matrix* mat1, Matrix* mat2) {
    if((mat1-> R == mat2->R) && (mat1->C == mat2->C)) {
        matAns->R = mat1->R;
        matAns->C = mat1->C;
        matAns->grid = (float*)calloc(matAns->R*matAns->C, sizeof(float));
        for(int i = 0;i < matAns->R*matAns->C; i++) {
            matAns->grid[i] = mat1->grid[i] - mat2->grid[i];
        }
    }
    else if((mat1-> R == 0) || (mat1->C == 0)) {
        printf("mat1 not initialised.\n");
    }
    else if((mat2-> R == 0) || (mat2->C == 0)) {
        printf("mat2 not initialised.\n");
    }
    else {
        printf("Size mismatch.\n");
    }
}

void multiplyMatrices(Matrix* matAns, Matrix* mat1, Matrix* mat2) {
    if(mat1->C == mat2->R) {
        matAns->R = mat1->R;
        matAns->C = mat2->C;
        matAns->grid = (float*)calloc(matAns->R*matAns->C, sizeof(float));
        for(int i = 0; i < matAns->R; i++) {
            for(int j = 0; j < matAns->C; j++) {
                for(int k = 0; k < mat1->C; k++) {
                    matAns->grid[(matAns->C)*i + j] += mat1->grid[k + (mat1->C)*i]*mat2->grid[(mat2->C)*k + j];
                }
            }
        }
    }
}

void rowEchleonUpper(Matrix* matAns, Matrix mat) {
    matAns->R = mat.R;
    matAns->C = mat.C;
    matAns->grid = (float*)calloc(mat.R*mat.C, sizeof(float));

    for(int i = 0; i < mat.R; i++) {
        for(int j = 0; j < mat.C; j++) {
            matAns->grid[i*mat.C + j] = mat.grid[i*mat.C + j];
        }
    }

    for(int i = 0; i < matAns->R; i++) {
        if(matAns->grid[i*matAns->C + i] == 0) {
            int rowExchangeFlag = 0;
            for(int j = i+1; j < matAns->R; j++) {
                if(matAns->grid[j*matAns->C + i] == 0) {
                    rowExchangeFlag = 0;
                    continue;
                }
                else {
                    for(int k = 0; k < matAns->C; k++) {
                        float temp = matAns->grid[j*matAns->C + k];
                        float temp2 = matAns->grid[i*matAns->C + k];
                        matAns->grid[j*matAns->C + k] = matAns->grid[i*matAns->C + k];
                        matAns->grid[i*matAns->C + k] = temp;
                    }
                    rowExchangeFlag = 1;
                    break;
                }
            }
            if(rowExchangeFlag == 0) {
                continue;
            }
            else {
                for(int j = i+1; j < matAns->R; j++) {
                    float ratio = matAns->grid[j*matAns->C + i]/matAns->grid[i*matAns->C + i];
                    for(int k = 0; k < matAns->C; k++) {
                        matAns->grid[j*matAns->C + k] = matAns->grid[j*matAns->C + k] - ratio*matAns->grid[i*matAns->C + k];
                    }
                }
            }
        }
        else {
            for(int j = i+1; j < matAns->R; j++) {
                float ratio = matAns->grid[j*matAns->C + i]/matAns->grid[i*matAns->C + i];
                for(int k = 0; k < matAns->C; k++) {
                    matAns->grid[j*matAns->C + k] = matAns->grid[j*matAns->C + k] - ratio*matAns->grid[i*matAns->C + k];
                }
            }
        }
    }
}

void rowEchleonLower(Matrix* matAns, Matrix mat) {
    matAns->R = mat.R;
    matAns->C = mat.C;
    matAns->grid = (float*)calloc(mat.R*mat.C, sizeof(float));
    
    for(int i = 0; i < mat.R; i++) {
        for(int j = 0; j < mat.C; j++) {
            matAns->grid[i*mat.C + j] = mat.grid[i*mat.C + j];
        }
    }

    for(int i = matAns->R - 1; i >= 0; i--) {
        if(matAns->grid[i*matAns->C + (matAns->C - (matAns->R - i))] == 0) {
            int rowExchangeFlag = 0;
            for(int j = i-1; j >= 0; j--) {
                if(matAns->grid[j*matAns->C + (matAns->C - (matAns->R - i))] == 0) {
                    rowExchangeFlag = 0;
                    continue;
                }
                else {
                    for(int k = 0; k < matAns->C; k++) {
                        float temp = matAns->grid[j*matAns->C + k];
                        float temp2 = matAns->grid[i*matAns->C + k];
                        matAns->grid[j*matAns->C + k] = matAns->grid[i*matAns->C + k];
                        matAns->grid[i*matAns->C + k] = temp;
                    }
                    rowExchangeFlag = 1;
                    break;
                }
            }
            if(rowExchangeFlag == 0) {
                continue;
            }
            else {
                for(int j = i-1; j >= 0; j--) {
                    float ratio = matAns->grid[j*matAns->C + (matAns->C - (matAns->R - i))]/matAns->grid[i*matAns->C + (matAns->C - (matAns->R - i))];
                    for(int k = 0; k < matAns->C; k++) {
                        matAns->grid[j*matAns->C + k] = matAns->grid[j*matAns->C + k] - ratio*matAns->grid[i*matAns->C + k];
                    }
                }
            }
        }
        else {
            for(int j = i-1; j >= 0; j--) {
                float ratio = matAns->grid[j*matAns->C + (matAns->C - (matAns->R - i))]/matAns->grid[i*matAns->C + (matAns->C - (matAns->R - i))];
                for(int k = 0; k < matAns->C; k++) {
                    printf("%f - %f*%f\n", matAns->grid[j*matAns->C + k], ratio, matAns->grid[i*matAns->C + k]);
                    matAns->grid[j*matAns->C + k] = matAns->grid[j*matAns->C + k] - ratio*matAns->grid[i*matAns->C + k];
                }
            }
        }
    }
}

int trace(float* sum, Matrix mat) {
    if((mat.R == mat.C ) && (mat.R > 0)) {
        *sum = 0;
        for(int i = 0; i < mat.R; i++) {
            *sum += mat.grid[i*mat.C + i];
        }
        return 1;
    }
    else {
        printf("Trace is not defined for non-sqaure matrices.\n");
        return 0;
    }
}

int determinant(float* det, Matrix mat) {
    if(mat.R == mat.C) {
        if(mat.R == 1) {
            *det = mat.grid[0];
            return 1;
        }
        else {
            Matrix matRowEchleon;
            rowEchleonLower(&matRowEchleon, mat);
            *det = 1;
            for(int i = 0; i < matRowEchleon.R; i++) {
                *det *= matRowEchleon.grid[i + i*matRowEchleon.C];
            }
            killMatrix(&matRowEchleon);
            return 1;
        }
    }
    else {
        printf("Determinant is not defined for non square matrix.\n");
        return 0;
    }
}

void inverse(Matrix* matAns, Matrix mat) {
    float det;
    if(determinant(&det, mat) && (det != 0)) {
        matAns->R = mat.R;
        matAns->C = mat.C;
        matAns->grid = (float*)calloc(mat.R*mat.C, sizeof(float));
        Matrix matAugmented;
        matAugmented.R = mat.R;
        matAugmented.C = mat.C*2;
        matAugmented.grid = (float*)calloc(2*mat.R*mat.C, sizeof(float));
        for(int i = 0; i < mat.R; i++) {
            for(int j = 0; j < 2*mat.C; j++) {
                if(j == i + mat.C) {
                    matAugmented.grid[i*2*mat.C + j] = 1;
                }
                else if(j < mat.C) {
                    matAugmented.grid[i*2*mat.C + j] = mat.grid[i*mat.C + j];
                }
            }
        }
        rowEchleonUpper(&matAugmented, matAugmented);
        for(int i = 0; i < matAugmented.R; i++) {
            for(int j = 0; j < mat.C; j++) {
                float temp = matAugmented.grid[i*2*mat.C + j];
                float temp2 = matAugmented.grid[i*2*mat.C + j + mat.C];
                matAugmented.grid[i*2*mat.C + j] = matAugmented.grid[i*2*mat.C + j + mat.C];
                matAugmented.grid[i*2*mat.C + j + mat.C] = temp;
            }
        }
        rowEchleonLower(&matAugmented, matAugmented);
        for(int i = 0; i < mat.R; i++) {
            for(int j = 0; j < matAugmented.C; j++) {
                matAugmented.grid[i*matAugmented.C + j] = matAugmented.grid[i*matAugmented.C + j]/matAugmented.grid[i*matAugmented.C + i + mat.C];
            }
        }
        for(int i = 0; i < matAns->R; i++) {
            for(int j = 0; j < matAns->C; j++) {
                matAns->grid[i*matAns->C + j] = matAugmented.grid[i*2*matAns->C + j];
            }
        }
        killMatrix(&matAugmented);
    }
    else {
        printf("Singular matrices are not invertible.\n");
    }
}

void char_poly(Matrix* matAns, Matrix mat) {
    if(mat.R == mat.C) {
        matAns->R = 1;
        matAns->C = mat.C + 1;
        matAns->grid = (float*)calloc(mat.C, sizeof(float));
        matAns->grid[0] = 1;
        Matrix Mi;
        Mi.R = mat.R;
        Mi.C = mat.C;
        Mi.grid = (float*)calloc(mat.R*mat.C, sizeof(float));
        for(int i = 0;i < Mi.R*Mi.C; i++) {
            printf("%f ", Mi.grid[i]);
            if(i%Mi.C == Mi.C-1) {
                printf("\n");
            }
        }
        Matrix In;
        IdentityMat(&In, mat.R);
        printf("\nIdentity matrix:\n");
        for(int i = 0;i < In.R*In.C; i++) {
            printf("%f ", In.grid[i]);
            if(i%In.C == In.C-1) {
                printf("\n");
            }
        }
        for(int i = 1; i < mat.C; i++) {
            Matrix product, product_trace;
            multiplyMatrices(&product, &Mi, &mat);
            printf("\nAMk-1:\n");
            for(int j = 0;j < product.R*product.C; j++) {
                printf("%f ", product.grid[j]);
                if(j%product.C == product.C-1) {
                    printf("\n");
                }
            }
            scale_matrix(&In, matAns->grid[i-1], In);
            printf("\nc(n-k+1)I:\n");
            for(int j = 0;j < In.R*In.C; j++) {
                printf("%f ", In.grid[j]);
                if(j%In.C == In.C-1) {
                    printf("\n");
                }
            }
            addMatrices(&Mi, &product, &In);
            printf("\nMk = AMk-1 + c(n-k+1)I:\n");
            for(int j = 0;j < Mi.R*Mi.C; j++) {
                printf("%f ", Mi.grid[j]);
                if(j%Mi.C == Mi.C-1) {
                    printf("\n");
                }
            }
            scale_matrix(&In, 1/matAns->grid[i-1], In);
            printf("\nc(n-k+1)I/c(n-k+1):\n");
            for(int j = 0;j < In.R*In.C; j++) {
                printf("%f ", In.grid[j]);
                if(j%In.C == In.C-1) {
                    printf("\n");
                }
            }
            printf("\nA:\n");
            for(int j = 0;j < mat.R*mat.C; j++) {
                printf("%f ", mat.grid[j]);
                if(j%mat.C == mat.C-1) {
                    printf("\n");
                }
            }
            printf("\nMk:\n");
            for(int j = 0;j < Mi.R*Mi.C; j++) {
                printf("%f ", Mi.grid[j]);
                if(j%Mi.C == Mi.C-1) {
                    printf("\n");
                }
            }
            multiplyMatrices(&product_trace, &Mi, &mat);
            printf("\nAMk:\n");
            for(int j = 0;j < Mi.R*Mi.C; j++) {
                printf("%f ", Mi.grid[j]);
                if(j%Mi.C == Mi.C-1) {
                    printf("\n");
                }
            }
            float trace_m;
            if(trace(&trace_m, product_trace) == 1) {
                matAns->grid[i] = (-1/((float)i))*(trace_m);
            };
            killMatrix(&product);
            killMatrix(&product_trace);
            printf("\ncn-k: %f\n", matAns->grid[i]);
        }
        // matAns->grid[matAns->C - 1]
        float det;
        determinant(&det, mat);
        matAns->grid[matAns->C - 1] = det;
    }
    else {
        printf("Characteristic polynomial is not defined for non-square matrices.\n");
    }
}

void printMatrix(Matrix* mat) {
    for(int i = 0;i < mat->R*mat->C; i++) {
        printf("%f ", mat->grid[i]);
        if(i%mat->C == mat->C-1) {
            printf("\n");
        }
    }
}