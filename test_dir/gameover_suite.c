#include "test.h"

START_TEST(test_gameover_1) {
  int action = KEY_DOWN;
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = GAMEOVER;
  shape_type_t fig_type;
  setupShape(&figure, 0, 0);
  createAndPlaceFigure(&info, &fig_type, &figure);
  ck_assert_int_eq(process_game_signal(&figure, get_player_input(action), &info,
                                       &fsm_state, &fig_type),
                   GAMEOVER);
  cleanupBoardAndNext(&info);
  cleanupShape(&figure);
}
END_TEST

Suite *gameover_suite(void) {
  Suite *suite = suite_create("starting");
  TCase *tcase_core = tcase_create("starting_case");
  tcase_add_test(tcase_core, test_gameover_1);
  suite_add_tcase(suite, tcase_core);
  return suite;
}