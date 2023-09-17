#include <stdbool.h>
#include <stdlib.h>
#include "game.h"

#define PLAYER_SIGN Cross
#define COMPUTER_SIGN Zero

typedef enum { Easy = 0, Medium = 1, Hard = 2 } AIType;

CellState matrix[FIELD_SIZE][FIELD_SIZE];

GameOverType gameOverType = NoGameOver;
short gameOverInfo = 0;

void PerformComputerMove(AIType);
void CheckGameOver();

void InitializeGame()
{
	srand(time());
	for (int i = 0; i < FIELD_SIZE; ++i)
		for (int j = 0; j < FIELD_SIZE; ++j)
			matrix[i][j] = Empty;
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
		return Empty;
	return matrix[xCell][yCell];
}

void HandleMouseClick(int mouseX, int mouseY, int viewport[4])
{
	if (gameOverType)
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
	if (gameOverType)
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

void PerformGameOver(GameOverType type, int info, CellState winner)
{
	gameOverType = type;
	gameOverInfo = info;
}

bool CheckGameOverLine(bool horizontal)
{
	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		CellState colState = Empty;
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			CellState state = horizontal ? matrix[j][i] : matrix[i][j];
			if (!state || (colState != Empty && state != colState))
			{
				colState = Empty;
				break;
			}
			colState = state;
		}
		if (colState)
		{
			PerformGameOver(horizontal ? Horizontal : Vertical, i, colState);
			return true;
		}
	}
	return false;
}

bool CheckGameOverDiagonal(bool up)
{
	CellState colState = Empty;
	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		CellState state = up ? matrix[i][i] : matrix[i][FIELD_SIZE - i - 1];
		if (!state || (colState != Empty && state != colState))
		{
			colState = Empty;
			break;
		}
		colState = state;
	}
	if (colState)
	{
		PerformGameOver(Diagonal, up, colState);
		return true;
	}
	return false;
}

void CheckGameOver()
{
	if (CheckGameOverLine(false))
		return;

	if (CheckGameOverLine(true))
		return;

	if (CheckGameOverDiagonal(false))
		return;

	if (CheckGameOverDiagonal(true))
		return;
}