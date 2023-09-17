#include <stdbool.h>
#include <stdlib.h>
#include "game.h"

#define PLAYER_SIGN Cross
#define COMPUTER_SIGN Zero

CellState matrix[FIELD_SIZE][FIELD_SIZE];
bool isGameOver = false;

void PerformComputerMove(AIType);
void CheckGameOver();

void InitializeGame()
{
	srand(time());
	for (int i = 0; i < FIELD_SIZE; ++i)
		for (int j = 0; j < FIELD_SIZE; ++j)
			matrix[i][j] = None;
}

void SetCellState(int xCell, int yCell, CellState state)
{
	if (xCell < 0 || xCell >= FIELD_SIZE || yCell < 0 || yCell >= FIELD_SIZE)
		return;
	matrix[xCell][yCell] = state;
}

CellState GetCellState(int xCell, int yCell)
{
	if (xCell < 0 || xCell >= FIELD_SIZE || yCell < 0 || yCell >= FIELD_SIZE)
		return None;
	return matrix[xCell][yCell];
}

void HandleMouseClick(int mouseX, int mouseY, int viewport[4])
{
	if (isGameOver)
		return;

	float x = (mouseX - viewport[0]) / (float)viewport[2];
	float y = 1.0f - (mouseY - viewport[1]) / (float)viewport[3];

	if (x < 0.0f || y < 0.0f)
		return;

	int xCell = (int)(FIELD_SIZE * x);
	int yCell = (int)(FIELD_SIZE * y);

	if (GetCellState(xCell, yCell))
		return;

	SetCellState(xCell, yCell, PLAYER_SIGN);

	CheckGameOver();

	PerformComputerMove(Easy);
}

void PerformComputerMove(AIType type)
{
	if (isGameOver)
		return;

	if (type == Easy)
	{
		int emptyCells[FIELD_SIZE * FIELD_SIZE] = { 0 };
		int emptyCellsCount = 0;

		for (int i = 0; i < FIELD_SIZE; ++i)
			for (int j = 0; j < FIELD_SIZE; ++j)
				if (!matrix[i][j])
					emptyCells[emptyCellsCount++] = (i << 16) | j;

		int cell = emptyCells[rand() % emptyCellsCount];

		int i = (cell >> 16) & 0xFFFF;
		int j = cell & 0xFFFF;

		SetCellState(i, j, COMPUTER_SIGN);
	}

	CheckGameOver();
}

void CheckGameOver()
{
	bool gameOver = true;

	for (int i = 0; gameOver && i < FIELD_SIZE; ++i)
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			if (!matrix[i][j])
			{
				gameOver = false;
				break;
			}
		}

	if (gameOver)
		isGameOver = true;
}