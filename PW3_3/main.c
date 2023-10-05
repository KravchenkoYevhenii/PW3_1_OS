#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int** data;
    size_t rows;
    size_t cols;
} Matrix;

void initMatrix(Matrix* mat, size_t rows, size_t cols) {
    mat->data = (int**)malloc(rows * sizeof(int*));
    for (size_t i = 0; i < rows; ++i) {
        mat->data[i] = (int*)malloc(cols * sizeof(int));
    }
    mat->rows = rows;
    mat->cols = cols;
}

void freeMatrix(Matrix* mat) {
    for (size_t i = 0; i < mat->rows; ++i) {
        free(mat->data[i]);
    }
    free(mat->data);
    mat->rows = 0;
    mat->cols = 0;
}

void resizeMatrix(Matrix* mat, size_t newRows, size_t newCols) {
    int** newData = (int**)malloc(newRows * sizeof(int*));
    for (size_t i = 0; i < newRows; ++i) {
        newData[i] = (int*)malloc(newCols * sizeof(int));
    }

    size_t minRows = (mat->rows < newRows) ? mat->rows : newRows;
    size_t minCols = (mat->cols < newCols) ? mat->cols : newCols;

    for (size_t i = 0; i < minRows; ++i) {
        for (size_t j = 0; j < minCols; ++j) {
            newData[i][j] = mat->data[i][j];
        }
        free(mat->data[i]);
    }
    free(mat->data);

    mat->data = newData;
    mat->rows = newRows;
    mat->cols = newCols;
}

void printMatrix(Matrix* mat) {
    for (size_t i = 0; i < mat->rows; ++i) {
        for (size_t j = 0; j < mat->cols; ++j) {
            printf("%d ", mat->data[i][j]);
        }
        printf("\n");
    }
}

void saveMatrixToFile(Matrix* mat, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for writing.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%zu %zu\n", mat->rows, mat->cols);
    for (size_t i = 0; i < mat->rows; ++i) {
        for (size_t j = 0; j < mat->cols; ++j) {
            fprintf(file, "%d ", mat->data[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void loadMatrixFromFile(Matrix* mat, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading.\n");
        exit(EXIT_FAILURE);
    }

    size_t rows, cols;
    fscanf(file, "%zu %zu", &rows, &cols);
    initMatrix(mat, rows, cols);

    for (size_t i = 0; i < mat->rows; ++i) {
        for (size_t j = 0; j < mat->cols; ++j) {
            fscanf(file, "%d", &mat->data[i][j]);
        }
    }

    fclose(file);
}

void addMatrices(Matrix* result, Matrix* mat1, Matrix* mat2) {
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        fprintf(stderr, "Matrix dimensions do not match for addition.\n");
        return;
    }

    initMatrix(result, mat1->rows, mat1->cols);

    for (size_t i = 0; i < mat1->rows; ++i) {
        for (size_t j = 0; j < mat1->cols; ++j) {
            result->data[i][j] = mat1->data[i][j] + mat2->data[i][j];
        }
    }
}

void subtractMatrices(Matrix* result, Matrix* mat1, Matrix* mat2) {
    if (mat1->rows != mat2->rows || mat1->cols != mat2->cols) {
        fprintf(stderr, "Matrix dimensions do not match for subtraction.\n");
        return;
    }

    initMatrix(result, mat1->rows, mat1->cols);

    for (size_t i = 0; i < mat1->rows; ++i) {
        for (size_t j = 0; j < mat1->cols; ++j) {
            result->data[i][j] = mat1->data[i][j] - mat2->data[i][j];
        }
    }
}

void multiplyMatrixByScalar(Matrix* result, Matrix* mat, int num) {
    initMatrix(result, mat->rows, mat->cols);

    for (size_t i = 0; i < mat->rows; ++i) {
        for (size_t j = 0; j < mat->cols; ++j) {
            result->data[i][j] = mat->data[i][j] * num;
        }
    }
}

void multiplyMatrices(Matrix* result, Matrix* mat1, Matrix* mat2) {
    if (mat1->cols != mat2->rows) {
        fprintf(stderr, "Matrix dimensions do not match for multiplication.\n");
        return;
    }

    initMatrix(result, mat1->rows, mat2->cols);

    for (size_t i = 0; i < mat1->rows; ++i) {
        for (size_t j = 0; j < mat2->cols; ++j) {
            result->data[i][j] = 0;
            for (size_t k = 0; k < mat1->cols; ++k) {
                result->data[i][j] += mat1->data[i][k] * mat2->data[k][j];
            }
        }
    }
}

int main() {
    srand(time(NULL));
    Matrix mat1, mat2, result;
    initMatrix(&mat1, 3, 3);
    initMatrix(&mat2, 3, 3);
    int switch_num;
    while(1) {
        printf("1. generate matrix;\n");
        printf("2. add matrix;\n");
        printf("3. subtract matrix;\n");
        printf("4. multiply matrix;\n");
        printf("5. multiply by num;\n");
        printf("6. print;\n");
        printf("7. read from file;\n");
        printf("8. save to file;\n");
        printf("0. exit;\n");
        scanf("%d", &switch_num);
        switch(switch_num) {
            case 1:{
                for (size_t i = 0; i < mat1.rows; ++i) {
                    for (size_t j = 0; j < mat1.cols; ++j) {
                        mat1.data[i][j] = rand() % 10;
                    }
                }

                for (size_t i = 0; i < mat2.rows; ++i) {
                    for (size_t j = 0; j < mat2.cols; ++j) {
                        mat2.data[i][j] = rand() % 10;
                    }
                }
                continue;
            }
            case 2:{
                addMatrices(&result, &mat1, &mat2);
                printf("Result of addition:\n");
                printMatrix(&result);
                continue;
            }
            case 3:{
                subtractMatrices(&result, &mat1, &mat2);
                printf("Result of subtraction:\n");
                printMatrix(&result);
                continue;
            }
            case 4:{
                multiplyMatrices(&result, &mat1, &mat2);
                printf("Result of matrix multiplication:\n");
                printMatrix(&result);
                continue;
            }
            case 5:{
                printf("Enter scalar: ");
                int scalar;
                scanf("%d", &scalar);
                multiplyMatrixByScalar(&result, &mat1, scalar);
                printf("Result of multiplication by scalar (mat1):\n");
                printMatrix(&result);
                multiplyMatrixByScalar(&result, &mat2, scalar);
                printf("Result of multiplication by scalar (mat2):\n");
                printMatrix(&result);
                continue;
            }
            case 6:{
                printMatrix(&mat1);
                printMatrix(&mat2);
                continue;
            }
            case 7:{
                loadMatrixFromFile(&mat1, "mat1");
                loadMatrixFromFile(&mat2, "mat2");
                continue;
            }
            case 8: {
                saveMatrixToFile(&mat1, "mat1");
                saveMatrixToFile(&mat2, "mat2");
                continue;
            }
            case 0:{
                freeMatrix(&mat1);
                freeMatrix(&mat2);
                freeMatrix(&result);
                return 0;
            }
        }
    }
}
