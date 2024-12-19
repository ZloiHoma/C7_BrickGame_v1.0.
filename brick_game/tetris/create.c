#include "../../gui/tetris.h"

void setupBoard(Details_t *A) {
  A->field = (int **)calloc(WID, sizeof(int *) + LEN * sizeof(int));
  A->field[0] = (int *)(A->field + WID);
  for (int i = 1; i < WID; i++) {
    A->field[i] = A->field[0] + i * LEN;
  }
  for (int i = 0; i < WID; i++) {
    for (int j = 0; j < LEN; j++) {
      if (j == 0 || j == LEN - 1) {
        A->field[i][j] = 1;
      }
      if (i == 0 || i == WID - 1) {
        A->field[i][j] = 1;
      }
    }
  }
  A->next =
      (int **)calloc(FIGURE_ROWS, sizeof(int *) + FIGURE_ROWS * sizeof(int));
  A->next[0] = (int *)(A->next + FIGURE_ROWS);
  for (int i = 1; i < FIGURE_ROWS; i++) {
    A->next[i] = A->next[0] + i * FIGURE_ROWS;
  }
}

void cleanupBoardAndNext(Details_t *A) {
  if (A != NULL || A->field != NULL || A->next != NULL) {
    free(A->field);
    free(A->next);
  }
}

void setupShape(shape_t *A, int rows, int colums) {
  A->colums = colums;
  A->rows = rows;
  A->figure_now = (int **)calloc(rows, sizeof(int *) + colums * sizeof(int));
  A->figure_now[0] = (int *)(A->figure_now + rows);
  for (int i = 1; i < rows; i++) {
    A->figure_now[i] = A->figure_now[0] + i * colums;
  }
}

void cleanupShape(shape_t *A) {
  if (A != NULL || A->figure_now != NULL) {
    free(A->figure_now);
    A->colums = 0;
    A->rows = 0;
  }
}
