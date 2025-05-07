#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR 1
#define EPS 1e-7
#define ERROR_ARIFMETIK 2

#define SUCCESS 1
#define FAILURE 0

// 0 — OK;
// 1 — Ошибка, некорректная матрица;
// 2 — Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т. д.).

// Значение 1e-7 означает 10^(-7), то есть 0.0000001.

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Создание матрицы
int s21_create_matrix(int rows, int columns, matrix_t *result);
// Отчистка матрицы
void s21_remove_matrix(matrix_t *A);
// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);
// Сложение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Умножение матриц
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);
// Минор матрицы и матрица алгебраических дополнений
int s21_calc_complements(matrix_t *A, matrix_t *result);
// Определитель матрицы
int s21_determinant(matrix_t *A, double *result);
// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
// проверка на валидность матрицы
int valid_Matrix(matrix_t *matrix);
// избегание дублирования кода sign = 0 - сложение, sign = 1 - вычитание
int s21_sub_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result, int sign);

#endif /* S21_MATRIX_H */
