#include "s21_matrix.h"

static double get_determinant(matrix_t *A, matrix_t *B);

int s21_determinant(matrix_t *A, double *result) {
  if (!A || !A->matrix || !result) return ERROR;

  if (A->columns <= 0 || A->rows <= 0 || A->columns != A->rows)
    return ERROR_ARIFMETIK;

  if (A->columns == 1) {
    *result = A->matrix[0][0];
    return OK;
  } else {
    matrix_t B = {0};
    int error = s21_calc_complements(A, &B);
    if (error == OK) {
      *result = get_determinant(A, &B);
      s21_remove_matrix(&B);
    }
    return error;
  }
}

double get_determinant(matrix_t *A, matrix_t *B) {
  double res = 0;
  for (int i = 0; i < A->columns; i++) {
    res += A->matrix[0][i] * B->matrix[0][i];
  }
  return res;
}
