#include "../../gui/tetris.h"

void initializeGameBoard(Details_t *tet, shape_t *arr) {
  for (int i = 0; i < arr->rows; i++) {
    for (int j = 0; j < arr->colums; j++) {
      if (arr->figure_now[i][j])
        tet->field[i + arr->figx][j + arr->figy] = arr->figure_now[i][j];
    }
  }
}

void checkLinesForClearance(Details_t *tet) {
  int count = 0;
  int count_line = 0;
  for (int i = WID - 2; i >= 1; i--) {
    for (int j = 1; j < LEN - 1; j++) {
      if (tet->field[i][j]) {
        count++;
      }
      if (count == 10) {
        dropShapes(tet, &i);
        count_line++;
      }
    }
    count = 0;
  }
  if (count_line) {
    incrementScore(count_line, tet);
  }
}

void dropShapes(Details_t *tet, int *i) {
  int ii = *i;
  for (; ii > 1; ii--) {
    for (int j = 1; j < LEN - 1; j++) {
      tet->field[ii][j] = tet->field[ii - 1][j];
    }
  }
  for (int j = 1; j < LEN - 1; j++) {
    tet->field[1][j] = 0;
  }
  (*i)++;
}

int isShapeColliding(Details_t *tet, shape_t *arr) {
  int flag = 0;
  for (int i = 0; i < arr->rows; i++) {
    for (int j = 0; j < arr->colums; j++) {
      if (arr->figure_now[i][j]) {
        if (arr->figure_now[i][j] + tet->field[arr->figx + i][arr->figy + j] !=
            arr->type_now + 1) {
          flag = 1;
        }
      }
    }
  }
  return flag;
}