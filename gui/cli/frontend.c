#include "../tetris.h"

void renderGameOverScreen(bool *flag_tetris, GameState_t *fsm_state, int signal,
                          Details_t *tet, shape_t *arr) {
  *flag_tetris = FALSE;
  cleanupBoardAndNext(tet);
  cleanupShape(arr);
  if (*fsm_state == GAMEOVER) {
    storeHighScore(tet);
    clear();
    while (signal != '\n' && signal != 27) {
      refresh();
      mvprintw(7, 2, "GameOver");
      mvprintw(9, 3, "return");
      mvprintw(10, 2, "to enter");
      mvprintw(12, 4, "exit");
      mvprintw(13, 3, "to esc");
      signal = getch();
      if (signal == '\n') {
        displayGameInfo(tet);
        setupShape(arr, 0, 0);
        setupBoard(tet);
        *flag_tetris = TRUE;
        *fsm_state = START;
      }
    }
    clear();
  }
}

void renderStartScreen(Details_t *tet, WINDOW *field_info, WINDOW *win) {
  clear();
  refresh();
  box(field_info, 0, 0);
  box(win, 0, 0);
  mvwprintw(field_info, 10, 2, "press to");
  mvwprintw(field_info, 11, 3, "enter");
  renderGameInfo(win, tet);
  wrefresh(field_info);
  wrefresh(win);
  wclear(win);
  wclear(field_info);
}

void refreshGameBoard(Details_t *tet, WINDOW *field_info, WINDOW *win,
                      shape_t *figur) {
  clear();
  refresh();
  for (int i = 1; i < WID - 1; i++) {
    for (int j = 1; j < LEN - 1; j++) {
      if (tet->field[i][j]) {
        mvwprintw(field_info, i, j, "%d", tet->field[i][j]);
      } else
        mvwprintw(field_info, i, j, " ");
    }
  }
  for (int i = 0; i < figur->rows; i++) {
    for (int j = 0; j < figur->colums; j++) {
      if (figur->figure_now[i][j])
        mvwprintw(field_info, i + figur->figx, j + figur->figy, "%d",
                  figur->type_now + 1);
    }
    wrefresh(field_info);
  }
  box(win, 0, 0);
  box(field_info, 0, 0);
  renderGameInfo(win, tet);
  display_next_shape(win, tet);
  wrefresh(win);
  wrefresh(field_info);
  wclear(win);
  wclear(field_info);
}

void display_next_shape(WINDOW *win, Details_t *tet) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      mvwprintw(win, 15 + i, 2 + j, "%d", tet->next[i][j]);
    }
  }
}

void renderGameInfo(WINDOW *win, Details_t *tet) {
  mvwprintw(win, 1, 1, "score");
  mvwprintw(win, 2, 2, "%d", tet->score);
  mvwprintw(win, 4, 1, "hide rec");
  mvwprintw(win, 5, 2, "%d", tet->high_score);
  mvwprintw(win, 7, 1, "level");
  mvwprintw(win, 8, 2, "%d", tet->level);
  mvwprintw(win, 10, 1, "speed");
  mvwprintw(win, 11, 2, "%d", tet->speed);
  mvwprintw(win, 14, 1, "next");
  display_next_shape(win, tet);
}