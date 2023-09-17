#include <stdbool.h>
#include <stdlib.h>
#include "game.h"

#define PLAYER_SIGN Cross
#define COMPUTER_SIGN Zero

typedef enum { Easy = 0, Medium = 1, Hard = 2 } AIType;

CellState matrix[FIELD_SIZE][FIELD_SIZE];

GameOverType gameOverType;
short gameOverInfo;

void PerformComputerMove(AIType);
void CheckGameOver();

void InitializeGame()
{
	srand(time());
	for (int i = 0; i < FIELD_SIZE; ++i)
		for (int j = 0; j < FIELD_SIZE; ++j)
			matrix[i][j] = Empty;
	gameOverType = NoGameOver;
	gameOverInfo = 0;
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

	PerformComputerMove(Hard);
}

int CheckComputerLine(bool horizontal, CellState stateNoDanger)
{
	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		int dangerCellIndex = -1;
		for (int j = 0; j < FIELD_SIZE; ++j)
		{
			CellState state = horizontal ? matrix[j][i] : matrix[i][j];
			if (!state)
				dangerCellIndex = dangerCellIndex == -1 ? j : -2;
			else if (state == stateNoDanger)
				dangerCellIndex = -2;
		}
		if (dangerCellIndex >= 0)
			return (i << 16) | dangerCellIndex;
	}
	return -1;
}

int CheckComputerDiagonal(bool up, CellState stateNoDanger)
{
	int dangerCellIndex = -1;
	for (int i = 0; i < FIELD_SIZE; ++i)
	{
		CellState state = up ? matrix[i][i] : matrix[i][FIELD_SIZE - i - 1];
		if (!state)
			dangerCellIndex = dangerCellIndex == -1 ? i : -2;
		else if (state == stateNoDanger)
			dangerCellIndex = -2;
	}
	if (dangerCellIndex >= 0)
		return dangerCellIndex;
	return -1;
}

bool PerformSmartMove(CellState stateNoDanger)
{
	int index;
	bool flag;

	index = CheckComputerLine(flag = false, stateNoDanger);
	if (index < 0)
		index = CheckComputerLine(flag = true, stateNoDanger);
	if (index >= 0)
	{
		int i = (index >> 16) & 0xFFFF;
		int j = index & 0xFFFF;
		if (flag)
			SetCellState(j, i, COMPUTER_SIGN);
		else
			SetCellState(i, j, COMPUTER_SIGN);
		return true;
	}

	index = CheckComputerDiagonal(flag = false, stateNoDanger);
	if (index < 0)
		index = CheckComputerDiagonal(flag = true, stateNoDanger);
	if (index >= 0)
	{
		if (flag)
			SetCellState(index, index, COMPUTER_SIGN);
		else
			SetCellState(index, FIELD_SIZE - index - 1, COMPUTER_SIGN);
		return true;
	}

	return false;
}

bool SetComputerCellIfEmpty(int xCell, int yCell)
{
	if (!GetCellState(xCell, yCell))
	{
		SetCellState(xCell, yCell, COMPUTER_SIGN);
		return true;
	}
	return false;
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

		if (emptyCellsCount)
		{
			int cell = emptyCells[rand() % emptyCellsCount];

			int i = (cell >> 16) & 0xFFFF;
			int j = cell & 0xFFFF;

			SetCellState(i, j, COMPUTER_SIGN);
		}
		CheckGameOver();
	}
	else
	{
		if (PerformSmartMove(PLAYER_SIGN))
		{
			CheckGameOver();
			return;
		}

		if (PerformSmartMove(COMPUTER_SIGN))
		{
			CheckGameOver();
			return;
		}

		if (SetComputerCellIfEmpty(FIELD_SIZE / 2, FIELD_SIZE / 2))
		{
			CheckGameOver();
			return;
		}

		if (SetComputerCellIfEmpty(0, 0) || 
			SetComputerCellIfEmpty(FIELD_SIZE - 1, 0) ||
			SetComputerCellIfEmpty(0, FIELD_SIZE - 1) ||
			SetComputerCellIfEmpty(FIELD_SIZE - 1, FIELD_SIZE - 1))
		{
			CheckGameOver();
			return;
		}

		PerformComputerMove(Easy);
		return;
	}
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
	if (CheckGameOverLine(false) == -1)
		return;

	if (CheckGameOverLine(true) == -1)
		return;

	if (CheckGameOverDiagonal(false) == -1)
		return;

	if (CheckGameOverDiagonal(true) == -1)
		return;
}