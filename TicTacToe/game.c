#include <stdbool.h>
#include <stdlib.h>
#include "game.h"

CellState matrix[FIELD_SIZE][FIELD_SIZE];

void InitializeGame()
{
	srand(time());
	for (int i = 0; i < FIELD_SIZE; ++i)
		for (int j = 0; j < FIELD_SIZE; ++j)
			matrix[i][j] = rand() > RAND_MAX / 2.0f ? Cross : Zero;
}

void SetCellState(int xCell, int yCell, CellState state)
{
	if (xCell < 0 || xCell >= FIELD_SIZE || yCell < 0 || yCell >= FIELD_SIZE)
		return;
	matrix[xCell][yCell] = state;
}

void HandleMouseClick(int mouseX, int mouseY, int viewport[4])
{
	float x = (mouseX - viewport[0]) / (float)viewport[2];
	float y = 1.0f - (mouseY - viewport[1]) / (float)viewport[3];

	if (x < 0.0f || y < 0.0f)
		return;

	int xCell = (int)(FIELD_SIZE * x);
	int yCell = (int)(FIELD_SIZE * y);
	SetCellState(xCell, yCell, None);
}