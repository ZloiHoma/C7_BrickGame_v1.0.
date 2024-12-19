#ifndef FRONTEND_H
#define FRONTEND_H

#include "tetris.h"

// Game State Management
void renderGameOverScreen(bool *flag_tetris, GameState_t *fsm_state, int signal,
                          Details_t *tet, shape_t *arr);
void renderStartScreen(Details_t *tet, WINDOW *field_info, WINDOW *win);

// Game Board Updates
void refreshGameBoard(Details_t *tet, WINDOW *field_info, WINDOW *win,
                      shape_t *figur);
void display_next_shape(WINDOW *win, Details_t *tet);

// Game Information Display
void renderGameInfo(WINDOW *win, Details_t *tet);

#endif