#include "test.h"

START_TEST(test_spawn_1) {
  int action = KEY_DOWN;
  shape_t figure;
  Details_t info;
  displayGameInfo(&info);
  setupBoard(&info);
  GameState_t fsm_state = SPAWN;
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

Suite *spawn_suite(void) {
  Suite *suite = suite_create("spawn");
  TCase *tcase_core = tcase_create("spawn_case");
  tcase_add_test(tcase_core, test_spawn_1);
  suite_add_tcase(suite, tcase_core);
  return suite;
}