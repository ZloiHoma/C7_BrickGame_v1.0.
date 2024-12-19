#include "../../gui/tetris.h"

void createAndPlaceFigure(Details_t *info, shape_type_t *fig,
                          shape_t *figure_now) {
  figure_now->figx = 1;
  figure_now->figy = 4;
  if (figure_now->colums == 0) {
    initializeFirstFigure(info, fig, figure_now);
  } else {
    allocateAndFillFigure(figure_now, info, fig->next_type);

    figure_now->type_now = fig->next_type;
    fig->next_type = getRandomShape(fig);
    prepareNextFigure(info, fig->next_type);
  }
}

void allocateAndFillFigure(shape_t *now_figure, Details_t *info, int type) {
  if (now_figure->colums != 0) {
    cleanupShape(now_figure);
  }
  if (!type) {
    setupShape(now_figure, 4, 4);
  } else if (type == 1) {
    setupShape(now_figure, 2, 2);
  } else {
    setupShape(now_figure, 3, 3);
  }
  for (int i = 0; i < now_figure->rows; i++) {
    for (int j = 0; j < now_figure->colums; j++) {
      now_figure->figure_now[i][j] = info->next[i][j];
    }
  }
}

void prepareNextFigure(Details_t *info, int type) {
  clearNextShape(info);
  for (int i = 0; i < FIGURE_ROWS; i++) {
    info->next[shape_tetra[type][0][i].x][shape_tetra[type][0][i].y] = type + 1;
  }
}

void clearNextShape(Details_t *info) {
  for (int i = 0; i < FIGURE_ROWS; i++) {
    for (int j = 0; j < FIGURE_ROWS; j++) {
      if (info->next[i][j]) info->next[i][j] = 0;
    }
  }
}

void initializeFirstFigure(Details_t *info, shape_type_t *fig,
                           shape_t *now_figure) {
  fig->next_type = rand() % 7;
  fig->next_type = getRandomShape(fig);
  now_figure->type_now = fig->next_type;
  prepareNextFigure(info, fig->next_type);
  allocateAndFillFigure(now_figure, info, fig->next_type);
  fig->next_type = getRandomShape(fig);
  prepareNextFigure(info, fig->next_type);
}
