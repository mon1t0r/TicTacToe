#pragma once

#define FIELD_SIZE 3

typedef enum { None = 0, Cross = 1, Zero = 2 } CellState;

extern CellState matrix[FIELD_SIZE][FIELD_SIZE];

void InitializeGame();
void SetCellState(int, int, CellState);
void HandleMouseClick(int, int, int[4]);