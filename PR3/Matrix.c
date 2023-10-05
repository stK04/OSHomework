#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int** data;
    int rows;
    int cols;
} Matrix;

Matrix initMatrix(int rows, int cols) {
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    mat.data = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        mat.data[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0;
        }
    }

    return mat;
}

void freeMatrix(Matrix mat) {
    for (int i = 0; i < mat.rows; i++) {
        free(mat.data[i]);
    }
    free(mat.data);
}

void setElement(Matrix* mat, int row, int col, int value) {
    if (row >= 0 && row < mat->rows && col >= 0 && col < mat->cols) {
        mat->data[row][col] = value;
    }
}

int getElement(Matrix mat, int row, int col) {
    if (row >= 0 && row < mat.rows && col >= 0 && col < mat.cols) {
        return mat.data[row][col];
    } else {
        return 0;
    }
}

int numRows(Matrix mat) {
    return mat.rows;
}

int numCols(Matrix mat) {
    return mat.cols;
}

void printMatrix(Matrix mat) {
    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            printf("%d\t", mat.data[i][j]);
        }
        printf("\n");
    }
}

Matrix resizeMatrix(Matrix mat, int newRows, int newCols) {
    Matrix newMat = initMatrix(newRows, newCols);

    for (int i = 0; i < mat.rows && i < newRows; i++) {
        for (int j = 0; j < mat.cols && j < newCols; j++) {
            newMat.data[i][j] = mat.data[i][j];
        }
    }

    freeMatrix(mat);

    return newMat;
}

void saveMatrixToFile(Matrix mat, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(file, "%d %d\n", mat.rows, mat.cols);

    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            fprintf(file, "%d ", mat.data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

Matrix loadMatrixFromFile(const char* filename) {
    Matrix mat;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        mat.rows = 0;
        mat.cols = 0;
        mat.data = NULL;
        return mat;
    }

    fscanf(file, "%d %d", &mat.rows, &mat.cols);

    mat = initMatrix(mat.rows, mat.cols);

    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            fscanf(file, "%d", &mat.data[i][j]);
        }
    }

    fclose(file);

    return mat;
}

Matrix addMatrices(Matrix mat1, Matrix mat2) {
    if (mat1.rows != mat2.rows || mat1.cols != mat2.cols) {
        printf("It is not possible to add matrices of different sizes.\n");
        Matrix emptyMat;
        emptyMat.rows = 0;
        emptyMat.cols = 0;
        emptyMat.data = NULL;
        return emptyMat;
    }

    Matrix result = initMatrix(mat1.rows, mat1.cols);

    for (int i = 0; i < mat1.rows; i++) {
        for (int j = 0; j < mat1.cols; j++) {
            result.data[i][j] = mat1.data[i][j] + mat2.data[i][j];
        }
    }

    return result;
}

Matrix subtractMatrices(Matrix mat1, Matrix mat2) {
    if (mat1.rows != mat2.rows || mat1.cols != mat2.cols) {
        printf("It is not possible to subtract matrices of different sizes.\n");
        Matrix emptyMat;
        emptyMat.rows = 0;
        emptyMat.cols = 0;
        emptyMat.data = NULL;
        return emptyMat;
    }

    Matrix result = initMatrix(mat1.rows, mat1.cols);

    for (int i = 0; i < mat1.rows; i++) {
        for (int j = 0; j < mat1.cols; j++) {
            result.data[i][j] = mat1.data[i][j] - mat2.data[i][j];
        }
    }

    return result;
}

Matrix multiplyMatrixByScalar(Matrix mat, int scalar) {
    Matrix result = initMatrix(mat.rows, mat.cols);

    for (int i = 0; i < mat.rows; i++) {
        for (int j = 0; j < mat.cols; j++) {
            result.data[i][j] = mat.data[i][j] * scalar;
        }
    }

    return result;
}

Matrix multiplyMatrices(Matrix mat1, Matrix mat2) {
    if (mat1.cols != mat2.rows) {
        printf("It is not possible to multiply matrices with such dimensions.\n");
        Matrix emptyMat;
        emptyMat.rows = 0;
        emptyMat.cols = 0;
        emptyMat.data = NULL;
        return emptyMat;
    }

    Matrix result = initMatrix(mat1.rows, mat2.cols);

    for (int i = 0; i < mat1.rows; i++) {
        for (int j = 0; j < mat2.cols; j++) {
            for (int k = 0; k < mat1.cols; k++) {
                result.data[i][j] += mat1.data[i][k] * mat2.data[k][j];
            }
        }
    }

    return result;
}

