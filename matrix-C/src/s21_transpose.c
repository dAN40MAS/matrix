#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error = OK;

  if (!A || !A->matrix) return ERROR;

  error = s21_create_matrix(A->columns, A->rows, result);

  for (int i = 0; i < A->columns && !error; i++) {
    for (int j = 0; j < A->rows && !error; j++) {
      result->matrix[i][j] = A->matrix[j][i];
    }
  }

  return error;
}
