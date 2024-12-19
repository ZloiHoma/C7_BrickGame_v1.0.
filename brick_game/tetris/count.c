#include "../../gui/tetris.h"

void recordHighScore(Details_t *info) {
  FILE *rec = NULL;
  if ((rec = fopen("gui/record_score/record.txt", "r")) == NULL) {
    rec = fopen("gui/record_score/record.txt", "w");
    fprintf(rec, "%d", info->high_score);
  } else {
    fscanf(rec, "%d", &info->high_score);
  }
  fclose(rec);
}

void storeHighScore(Details_t *info) {
  FILE *rec = NULL;
  rec = fopen("gui/record_score/record.txt", "w");
  fprintf(rec, "%d", info->high_score);
  fclose(rec);
}

void displayGameInfo(Details_t *info) {
  info->field = NULL;
  info->high_score = 0;
  info->level = 1;
  info->next = NULL;
  info->pause = 0;
  info->score = 0;
  info->speed = 1;
  recordHighScore(info);
}

void incrementScore(int count, Details_t *tet_info) {
  if (count == 1) {
    tet_info->score += 100;
  } else if (count == 2) {
    tet_info->score += 200;
  } else if (count == 3) {
    tet_info->score += 300;
  } else if (count == 4) {
    tet_info->score += 400;
  }
  if (tet_info->score > tet_info->high_score) {
    tet_info->high_score = tet_info->score;
  }
}

void adjustLevelAndSpeed(Details_t *tet_info) {
  tet_info->level = tet_info->score / 300 + 1;
  if (tet_info->level > 10) {
    tet_info->level = 10;
  }
  tet_info->speed = tet_info->level;
}

int getRandomShape(shape_type_t *fig) {
  int r = rand() % 7;
  int flag = 1;
  if (isShapeAvailable(fig)) resetShapeTypes(fig);
  while (flag) {
    flag = 0;
    if (r == 0 && !fig->is) {
      fig->is = 1;
    } else if (r == 1 && !fig->js) {
      fig->js = 1;
    } else if (r == 2 && !fig->ls) {
      fig->ls = 1;
    } else if (r == 3 && !fig->os) {
      fig->os = 1;
    } else if (r == 4 && !fig->ss) {
      fig->ss = 1;
    } else if (r == 5 && !fig->ts) {
      fig->ts = 1;
    } else if (r == 6 && !fig->zs) {
      fig->zs = 1;
    } else {
      flag = 1;
      r = rand() % 7;
    }
  }
  return r;
}

int isShapeAvailable(shape_type_t *fig) {
  int check = 0;
  if (fig->is && fig->js && fig->ls && fig->os && fig->ss && fig->ts &&
      fig->zs) {
    check = 1;
  }
  return check;
}

void resetShapeTypes(shape_type_t *fig) {
  fig->is = 0;
  fig->js = 0;
  fig->ls = 0;
  fig->os = 0;
  fig->ss = 0;
  fig->ts = 0;
  fig->zs = 0;
}

void duplicateShape(shape_t *tet, shape_t *tmp) {
  for (int i = 0; i < tet->rows; i++) {
    for (int j = 0; j < tet->colums; j++) {
      tmp->figure_now[i][j] = tet->figure_now[i][j];
    }
  }
}

void rotateCurrentShape(shape_t *tet, Details_t *info) {
  if (!isRotationValid(tet, info)) {
    shape_t tmp;
    setupShape(&tmp, tet->rows, tet->colums);
    duplicateShape(tet, &tmp);
    cleanupShape(tet);
    setupShape(tet, tmp.colums, tmp.rows);
    for (int i = 0; i < tet->rows; i++) {
      for (int j = 0; j < tet->colums; j++) {
        tet->figure_now[i][j] = tmp.figure_now[tmp.rows - 1 - j][i];
      }
    }
    cleanupShape(&tmp);
  }
}

int isRotationValid(shape_t *tet, Details_t *info) {
  int flag = 0;
  shape_t check;
  setupShape(&check, tet->rows, tet->colums);
  for (int i = 0; i < tet->rows; i++) {
    for (int j = 0; j < tet->colums; j++) {
      check.figure_now[i][j] = tet->figure_now[check.rows - 1 - j][i];
    }
  }
  for (int i = 0; i < tet->rows; i++) {
    for (int j = 0; j < tet->colums; j++) {
      if (check.figure_now[i][j]) {
        if (check.figure_now[i][j] + info->field[tet->figx + i][tet->figy + j] >
            tet->type_now + 1) {
          flag = 1;
        }
      }
    }
  }
  cleanupShape(&check);
  return flag;
}

int togglePauseGame(PlayerInput_t action, Details_t *info) {
  while (action != '\t' && action != 27) {
    mvprintw(10, 3, "pause");
    action = getch();
  }
  if (action == 27) {
    action = Terminate;
  }
  if (action == '\t') {
    info->pause = 0;
    action = NoAction;
  }
  return action;
}

int isGameOver(Details_t *info) {
  int flag = 1;
  for (int j = 1; j < LEN - 1; j++) {
    if (j > 3 && j < 8) {
      if (info->field[1][j]) {
        flag = 0;
      }
    }
  }
  return flag;
}