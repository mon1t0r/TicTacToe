#pragma once

#define FIELD_SIZE 3

typedef enum { Empty = 0, Cross = 1, Zero = 2 } CellState;
typedef enum { NoGameOver = 0, Horizontal = 1, Vertical = 2, Diagonal = 3 } GameOverType;
typedef enum { Easy = 0, Medium = 1, Hard = 2 } AIType;

extern CellState matrix[FIELD_SIZE][FIELD_SIZE];
extern GameOverType gameOverType;
extern short gameOverInfo;
extern AIType aiType;

void InitializeGame();
void ChangeAIType();
void HandleMouseClick(int, int, int[4]);