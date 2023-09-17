#pragma once

#define FIELD_SIZE 3

typedef enum { Empty = 0, Cross = 1, Zero = 2 } CellState;
typedef enum { NoGameOver = 0, Horizontal = 1, Vertical = 2, Diagonal = 3 } GameOverType;

extern CellState matrix[FIELD_SIZE][FIELD_SIZE];
extern GameOverType gameOverType;
extern short gameOverInfo;

void InitializeGame();
void SetCellState(int, int, CellState);
CellState GetCellState(int, int);
void HandleMouseClick(int, int, int[4]);