#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error = OK;

  if (!A || !A->matrix || !B || !B->matrix) return ERROR;
  if (A->columns != B->rows) return ERROR_ARIFMETIK;

  error = s21_create_matrix(A->rows, B->columns, result);

  for (int i = 0; i < A->rows && !error; i++) {
    for (int j = 0; j < B->columns && !error; j++) {
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
      }
    }
  }

  return error;
}
