#pragma once

#define FIELD_SIZE 3

typedef enum { None = 0, Cross = 1, Zero = 2 } CellState;
typedef enum { Easy = 0, Medium = 1, Hard = 2 } AIType;

extern CellState matrix[FIELD_SIZE][FIELD_SIZE];

void InitializeGame();
void SetCellState(int, int, CellState);
CellState GetCellState(int, int);
void HandleMouseClick(int, int, int[4]);