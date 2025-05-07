#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  // if (!result || rows < 1 || columns < 1) return ERROR
  //
  if (!result || rows < 1 || columns < 1) return ERROR;

  result->matrix = (double **)calloc(rows, sizeof(double *));

  if (result->matrix == NULL) return ERROR;

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));

    if (result->matrix[i] == NULL) {
      while (i--) free(result->matrix[i]);

      free(result->matrix);

      return ERROR;
    }
  }

  result->rows = rows;
  result->columns = columns;

  return OK;
}