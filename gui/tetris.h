#ifndef TETRIS_H
#define TETRIS_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "astruct.h"
#include "backend.h"
#include "frontend.h"
#include "fsm.h"

#define LEN 12
#define WID 22
#define FIGURE_ROWS 4

void initiate_game();
void game_loop(Details_t *tet);

#endif