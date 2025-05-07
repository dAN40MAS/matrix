#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error = OK;

  if (!A || !A->matrix) return ERROR;

  error = s21_create_matrix(A->rows, A->columns, result);

  for (int i = 0; i < A->rows && !error; i++) {
    for (int j = 0; j < A->columns && !error; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }

  return error;
}
