#include "test.h"

START_TEST(test_start_1) {
  int action = KEY_DOWN;
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = START;
  shape_type_t fig_type;
  setupShape(&figure, 0, 0);
  createAndPlaceFigure(&info, &fig_type, &figure);
  ck_assert_int_eq(process_game_signal(&figure, get_player_input(action), &info,
                                       &fsm_state, &fig_type),
                   START);
  cleanupBoardAndNext(&info);
  cleanupShape(&figure);
}
END_TEST

START_TEST(test_start_2) {
  int action = 1;
  get_player_input(action);
  action = '\n';
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = START;
  shape_type_t fig_type;
  setupShape(&figure, 0, 0);
  createAndPlaceFigure(&info, &fig_type, &figure);
  ck_assert_int_eq(process_game_signal(&figure, get_player_input(action), &info,
                                       &fsm_state, &fig_type),
                   SPAWN);
  cleanupBoardAndNext(&info);
  cleanupShape(&figure);
}
END_TEST

START_TEST(test_start_3) {
  int action = '\t';
  get_player_input(action);
  action = 27;
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = START;
  shape_type_t fig_type;
  setupShape(&figure, 0, 0);
  createAndPlaceFigure(&info, &fig_type, &figure);
  ck_assert_int_eq(process_game_signal(&figure, get_player_input(action), &info,
                                       &fsm_state, &fig_type),
                   EXIT_GAME);
  cleanupBoardAndNext(&info);
  cleanupShape(&figure);
}
END_TEST

Suite *start_suite(void) {
  Suite *suite = suite_create("starting");
  TCase *tcase_core = tcase_create("starting_case");
  tcase_add_test(tcase_core, test_start_1);
  tcase_add_test(tcase_core, test_start_2);
  tcase_add_test(tcase_core, test_start_3);
  suite_add_tcase(suite, tcase_core);
  return suite;
}