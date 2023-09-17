#include <stdbool.h>
#include <stdlib.h>
#include "game.h"

CellState matrix[FIELD_SIZE][FIELD_SIZE];

void InitializeGame()
{
	for (int i = 0; i < FIELD_SIZE; ++i)
		for (int j = 0; j < FIELD_SIZE; ++j)
			matrix[i][j] = rand() > RAND_MAX / 2.0f ? Cross : Zero;
}