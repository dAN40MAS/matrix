#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  return s21_sub_sum_matrix(A, B, result, 1);
}
