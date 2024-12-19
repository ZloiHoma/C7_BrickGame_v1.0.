#include "../../gui/tetris.h"

void moveFigureRight(shape_t *tet, Details_t *info) {
  tet->figy++;
  if (isShapeColliding(info, tet)) {
    tet->figy--;
  }
}

void moveFigureLeft(shape_t *tet, Details_t *info) {
  tet->figy--;
  if (isShapeColliding(info, tet)) {
    tet->figy++;
  }
}

int moveFigureDown(shape_t *tet, Details_t *info) {
  int gener = 1;
  tet->figx++;
  if (isShapeColliding(info, tet)) {
    tet->figx--;
    gener = 0;
  }
  return gener;
}

int togglePause(PlayerInput_t action, Details_t *info) {
  int res = action;
  if (action == Pause) {
    if (info->pause == 0) {
      info->pause = 1;
    }
    res = togglePauseGame(action, info);
  }
  return res;
}

void createNewFigure(GameState_t *fsm_state, shape_t *figure,
                     shape_type_t *fig_type, Details_t *info) {
  createAndPlaceFigure(info, fig_type, figure);
  *fsm_state = MOVING;
}

void processShift(shape_t *figure, Details_t *info, GameState_t *fsm_state) {
  if (!moveFigureDown(figure, info)) {
    *fsm_state = COLLIDED;
  } else {
    *fsm_state = MOVING;
  }
}

void processStartAction(PlayerInput_t sign, GameState_t *fsm_state) {
  switch (sign) {
    case Start:
      *fsm_state = SPAWN;
      break;
    case Terminate:
      *fsm_state = EXIT_GAME;
      break;
    default:
      *fsm_state = START;
      break;
  }
}

void processCollision(GameState_t *fsm_state, shape_t *figure,
                      Details_t *info) {
  if (!isGameOver(info)) {
    *fsm_state = GAMEOVER;
  } else {
    adjustLevelAndSpeed(info);
    initializeGameBoard(info, figure);
    checkLinesForClearance(info);
    *fsm_state = SPAWN;
  }
}

void processFallingTetromino(PlayerInput_t sign, GameState_t *fsm_state,
                             shape_t *figure, Details_t *info) {
  int reached_figure = 1;
  switch (sign) {
    case Down:
      if (!(reached_figure = moveFigureDown(figure, info)))
        *fsm_state = COLLIDED;
      break;
    case Left:
      moveFigureLeft(figure, info);
      break;
    case Right:
      moveFigureRight(figure, info);
      break;
    case Action:
      rotateCurrentShape(figure, info);
      break;
    case Pause:
      if (togglePause(sign, info) == Terminate) {
        *fsm_state = EXIT_GAME;
      }
      break;
    case Terminate:
      *fsm_state = EXIT_GAME;
      break;

    default:
      delay_output(300 - (info->level * 25));
      if (*fsm_state != EXIT_GAME) {
        if (!reached_figure)
          *fsm_state = COLLIDED;
        else {
          *fsm_state = SHIFTING;
        }
      }
      break;
  }
}

PlayerInput_t get_player_input(int action) {
  PlayerInput_t cont;
  switch (action) {
    case KEY_DOWN:
      cont = Down;
      break;
    case KEY_LEFT:
      cont = Left;
      break;
    case KEY_RIGHT:
      cont = Right;
      break;
    case ' ':
      cont = Action;
      break;
    case '\n':
      cont = Start;
      break;
    case '\t':
      cont = Pause;
      break;
    case 27:
      cont = Terminate;
      break;
    default:
      cont = NoAction;
      break;
  }
  return cont;
}

GameState_t process_game_signal(shape_t *figure, PlayerInput_t sign,
                                Details_t *info, GameState_t *fsm_state,
                                shape_type_t *fig_type) {
  switch (*fsm_state) {
    case START:
      processStartAction(sign, fsm_state);
      break;
    case SPAWN:
      createNewFigure(fsm_state, figure, fig_type, info);
      break;
    case MOVING:
      processFallingTetromino(sign, fsm_state, figure, info);
      break;
    case SHIFTING:
      processShift(figure, info, fsm_state);
      break;
    case COLLIDED:
      processCollision(fsm_state, figure, info);
      break;
    case GAMEOVER:
      break;
    default:
      break;
  }
  return *fsm_state;
}