#ifndef ASTRUCT_H
#define ASTRUCT_H

#include "tetris.h"

typedef struct shape_t {
  int rows;
  int colums;
  int **figure_now;
  int type_now;
  int figx, figy;
} shape_t;

typedef struct {
  int x, y;
} coordinates_t;

typedef struct tetromino_shape {
  int type;
  int position;
  coordinates_t type_cordinates;
} tetromino_shape;

static const coordinates_t shape_tetra[7][1][4] = {
    {
        {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
    },
    {
        {{0, 0}, {0, 1}, {1, 0}, {1, 1}},
    },
    {
        {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
    },
    {
        {{0, 2}, {1, 0}, {1, 1}, {1, 2}},
    },
    {
        {{0, 1}, {0, 2}, {1, 0}, {1, 1}},
    },
    {
        {{0, 1}, {1, 0}, {1, 1}, {1, 2}},
    },
    {
        {{0, 0}, {0, 1}, {1, 1}, {1, 2}},
    }};

typedef struct {
  int ts, is, ls, js, os, zs, ss;
  int next_type;
} shape_type_t;

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action,
  NoAction
} PlayerInput_t;

typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} Details_t;

typedef struct {
  Details_t *tet;
  PlayerInput_t *signal;
  shape_type_t *type;
  tetromino_shape *tetra_figur;
  shape_t *figure;
} fsm_context_t;

typedef enum {
  START,
  SPAWN,
  MOVING,
  SHIFTING,
  COLLIDED,
  GAMEOVER,
  EXIT_GAME
} GameState_t;

#endif