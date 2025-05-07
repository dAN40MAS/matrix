#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (A == NULL || result == NULL || A->matrix == NULL) {
    return ERROR;
  }

  if (A->rows != A->columns || A->rows <= 1) {
    return ERROR_ARIFMETIK;
  }

  int create_status = s21_create_matrix(A->rows, A->columns, result);
  if (create_status != OK) {
    return create_status;
  }

  matrix_t minor;
  if (s21_create_matrix(A->rows - 1, A->columns - 1, &minor) != OK) {
    s21_remove_matrix(result);
    return ERROR;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      int minor_row = 0;
      for (int row = 0; row < A->rows; row++) {
        if (row == i) continue;
        int minor_col = 0;
        for (int col = 0; col < A->columns; col++) {
          if (col == j) continue;
          minor.matrix[minor_row][minor_col] = A->matrix[row][col];
          minor_col++;
        }
        minor_row++;
      }
      double det_minor;
      s21_determinant(&minor, &det_minor);
      result->matrix[i][j] = pow(-1, i + j) * det_minor;
    }
  }
  s21_remove_matrix(&minor);
  return OK;
}
