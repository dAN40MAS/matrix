#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (!A || !result || !A->matrix || A->columns < 1 || A->rows < 1)
    return ERROR;

  if (A->columns != A->rows) return ERROR_ARIFMETIK;

  int error = OK;
  double determinant = 0;
  matrix_t B = {0};
  matrix_t temp = {0};

  error = s21_determinant(A, &determinant);

  if (!error) {
    if (fabs(determinant) < EPS) return ERROR_ARIFMETIK;

    if (A->rows == 1 && A->columns == 1) {
      error = s21_create_matrix(1, 1, result);
      if (error == OK) {
        result->matrix[0][0] = 1.0 / A->matrix[0][0];
      }
    } else {
      error = s21_calc_complements(A, &B);
      if (!error) error = s21_transpose(&B, &temp);
      if (!error) error = s21_mult_number(&temp, 1. / determinant, result);
    }
  }

  s21_remove_matrix(&B);
  s21_remove_matrix(&temp);

  return error;
}