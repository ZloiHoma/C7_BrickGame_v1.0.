#include "test.h"

START_TEST(test_move_1) {
  int action = ' ';
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = MOVING;
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

START_TEST(test_move_2) {
  int action = KEY_DOWN;
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = MOVING;
  shape_type_t fig_type;
  fig_type.is = 1;
  fig_type.js = 1;
  fig_type.ls = 1;
  fig_type.os = 0;
  fig_type.ss = 1;
  fig_type.ts = 1;
  fig_type.zs = 1;
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

START_TEST(test_move_3) {
  int action = KEY_LEFT;
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = MOVING;
  shape_type_t fig_type;
  fig_type.is = 1;
  fig_type.js = 1;
  fig_type.ls = 1;
  fig_type.os = 0;
  fig_type.ss = 0;
  fig_type.ts = 1;
  fig_type.zs = 1;
  setupShape(&figure, 0, 0);
  createAndPlaceFigure(&info, &fig_type, &figure);
  figure.figy = 0;
  ck_assert_int_eq(process_game_signal(&figure, get_player_input(action), &info,
                                       &fsm_state, &fig_type),
                   MOVING);
  cleanupBoardAndNext(&info);
  cleanupShape(&figure);
}
END_TEST

START_TEST(test_move_4) {
  int action = KEY_RIGHT;
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = MOVING;
  shape_type_t fig_type;
  fig_type.is = 1;
  fig_type.js = 1;
  fig_type.ls = 1;
  fig_type.os = 0;
  fig_type.ss = 1;
  fig_type.ts = 1;
  fig_type.zs = 1;
  setupShape(&figure, 0, 0);
  createAndPlaceFigure(&info, &fig_type, &figure);
  figure.figy = 9;
  ck_assert_int_eq(process_game_signal(&figure, get_player_input(action), &info,
                                       &fsm_state, &fig_type),
                   MOVING);
  cleanupBoardAndNext(&info);
  cleanupShape(&figure);
}
END_TEST

START_TEST(test_move_5) {
  int action = 27;
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = MOVING;
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

// START_TEST(test_move_6) {
//   int action = 1;
//   shape_t figure;
//   Details_t info;
//   displayGameInfo(&info);
//   setupBoard(&info);
//   GameState_t fsm_state = MOVING;
//   shape_type_t fig_type;
//   setupShape(&figure, 0, 0);
//   createAndPlaceFigure(&info, &fig_type, &figure);
//   ck_assert_int_eq(process_game_signal(&figure, get_player_input(action),
//   &info, &fsm_state, &fig_type), SHIFTING); cleanupBoardAndNext(&info);
//   cleanupShape(&figure);
// }
// END_TEST

Suite *move_suite(void) {
  Suite *suite = suite_create("move");
  TCase *tcase_core = tcase_create("move_case");
  tcase_add_test(tcase_core, test_move_1);
  tcase_add_test(tcase_core, test_move_2);
  tcase_add_test(tcase_core, test_move_3);
  tcase_add_test(tcase_core, test_move_4);
  tcase_add_test(tcase_core, test_move_5);
  // tcase_add_test(tcase_core, test_move_6);
  suite_add_tcase(suite, tcase_core);

  return suite;
}
