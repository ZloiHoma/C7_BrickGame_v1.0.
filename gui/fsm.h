#ifndef FSM_H
#define FSM_H

#include "tetris.h"

// Tetromino Handling
GameState_t process_game_signal(shape_t *figure, PlayerInput_t sign,
                                Details_t *info, GameState_t *fsm_state,
                                shape_type_t *fig_type);
PlayerInput_t get_player_input(int action);
void processFallingTetromino(PlayerInput_t sign, GameState_t *fsm_state,
                             shape_t *figure, Details_t *info);
void processCollision(GameState_t *fsm_state, shape_t *figure, Details_t *info);
void processStartAction(PlayerInput_t sign, GameState_t *fsm_state);
void processShift(shape_t *figure, Details_t *info, GameState_t *fsm_state);

// Figure Generation and Movement
void createNewFigure(GameState_t *fsm_state, shape_t *figure,
                     shape_type_t *fig_type, Details_t *info);
int togglePause(PlayerInput_t action, Details_t *info);
int moveFigureDown(shape_t *tet, Details_t *info);
void moveFigureLeft(shape_t *tet, Details_t *info);
void moveFigureRight(shape_t *tet, Details_t *info);

#endif