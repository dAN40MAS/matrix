#include "s21_matrix.h"

int s21_sub_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sign) {
  if (!A || !B || !result) return ERROR;

  if (!A->matrix || !B->matrix) return ERROR;

  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0)
    return ERROR;

  if (A->columns != B->columns || A->rows != B->rows) return ERROR_ARIFMETIK;

  int error = s21_create_matrix(A->rows, A->columns, result);

  if (error == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = sign ? A->matrix[i][j] - B->matrix[i][j]
                                    : A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return error;
}