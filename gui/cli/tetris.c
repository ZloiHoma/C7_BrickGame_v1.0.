#include "../tetris.h"

int main() {
  srand(time(NULL));
  initscr();
  nodelay(stdscr, true);
  scrollok(stdscr, true);
  keypad(stdscr, true);
  curs_set(0);
  noecho();
  initiate_game();
  endwin();
  return 0;
}

void initiate_game() {
  Details_t tet;
  displayGameInfo(&tet);
  setupBoard(&tet);
  game_loop(&tet);
}

void game_loop(Details_t *tet) {
  WINDOW *field_info = newwin(WID, LEN, 0, 0);
  WINDOW *win = newwin(WID, LEN, 0, 12);
  shape_type_t type_st;
  shape_t arr;
  setupShape(&arr, 0, 0);
  bool flag_tetris = TRUE;
  GameState_t fsm_state = START;
  int signal = 0;

  while (flag_tetris) {
    delay_output(50);
    if (fsm_state == GAMEOVER || fsm_state == EXIT_GAME) {
      renderGameOverScreen(&flag_tetris, &fsm_state, signal, tet, &arr);
    } else {
      if (fsm_state == MOVING || fsm_state == START) signal = getch();
      process_game_signal(&arr, get_player_input(signal), tet, &fsm_state,
                          &type_st);
      if (fsm_state == START) {
        renderStartScreen(tet, field_info, win);
      } else if (fsm_state != EXIT_GAME) {
        refreshGameBoard(tet, field_info, win, &arr);
      }
    }
  }
}