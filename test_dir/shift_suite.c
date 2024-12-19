#include "test.h"

START_TEST(test_shifting_1) {
  int action = KEY_DOWN;
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = SHIFTING;
  shape_type_t fig_type;
  setupShape(&figure, 0, 0);
  createAndPlaceFigure(&info, &fig_type, &figure);
  ck_assert_int_eq(process_game_signal(&figure, get_player_input(action), &info,
                                       &fsm_state, &fig_type),
                   MOVING);
  cleanupBoardAndNext(&info);
  cleanupShape(&figure);
}
END_TEST

START_TEST(test_shifting_2) {
  int action = KEY_LEFT;
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = SHIFTING;
  shape_type_t fig_type;
  setupShape(&figure, 0, 0);
  createAndPlaceFigure(&info, &fig_type, &figure);
  figure.figx = 19;
  ck_assert_int_eq(process_game_signal(&figure, get_player_input(action), &info,
                                       &fsm_state, &fig_type),
                   COLLIDED);
  cleanupBoardAndNext(&info);
  cleanupShape(&figure);
}
END_TEST

Suite *shifting_suite(void) {
  Suite *suite = suite_create("shifting");
  TCase *tcase_core = tcase_create("shifting_case");
  tcase_add_test(tcase_core, test_shifting_1);
  tcase_add_test(tcase_core, test_shifting_2);
  suite_add_tcase(suite, tcase_core);
  return suite;
}