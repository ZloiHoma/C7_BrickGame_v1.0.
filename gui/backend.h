#ifndef BACKEND_H
#define BACKEND_H

#include "tetris.h"

// Game Board Management
void initializeGameBoard(Details_t *tet, shape_t *arr);
void checkLinesForClearance(Details_t *tet);
void dropShapes(Details_t *tet, int *i);
int isShapeColliding(Details_t *tet, shape_t *arr);

// Score Management
void recordHighScore(Details_t *info);
void storeHighScore(Details_t *info);
void displayGameInfo(Details_t *info);
void incrementScore(int count, Details_t *tet_info);
void adjustLevelAndSpeed(Details_t *tet_info);

// Shape Management
int getRandomShape(shape_type_t *fig);
int isShapeAvailable(shape_type_t *fig);
void resetShapeTypes(shape_type_t *fig);
void duplicateShape(shape_t *tet, shape_t *tmp);
void rotateCurrentShape(shape_t *tet, Details_t *info);
int isRotationValid(shape_t *tet, Details_t *info);

// Game Control
int togglePauseGame(PlayerInput_t action, Details_t *info);
int isGameOver(Details_t *info);

// Board Initialization and Cleanup
void setupBoard(Details_t *A);
void cleanupBoardAndNext(Details_t *A);
void setupShape(shape_t *A, int rows, int colums);
void cleanupShape(shape_t *A);

// Figure Generation and Management
void createAndPlaceFigure(Details_t *info, shape_type_t *fig,
                          shape_t *figure_now);
void allocateAndFillFigure(shape_t *now_figure, Details_t *info, int type);
void prepareNextFigure(Details_t *info, int type);
void clearNextShape(Details_t *info);
void initializeFirstFigure(Details_t *info, shape_type_t *fig,
                           shape_t *now_figure);

#endif