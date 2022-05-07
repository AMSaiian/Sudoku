#include "GameBoard.h"

GameBoard::GameBoard(int boxSize)
{
	this->boxSize = boxSize;
	this->gridSize = boxSize * boxSize;
}

void GameBoard::CreateBasicBoard()
{
	for (int i = 0; i < gridSize; i++)
	{
		std::vector<int> row;
		for (int j = 0; j < gridSize; j++)
		{
			int number = (i * boxSize + i / boxSize + j) % gridSize + 1;
			row.push_back(number);
		}
		readyCells.push_back(row);
	}
}

void GameBoard::MixRows()
{
	int district = rand() % boxSize;
	int row1 = rand() % boxSize;
	int row2;
	do
	{
		row2 = rand() % boxSize;
	} while (row1 == row2);
	readyCells[boxSize * district + row1].swap(readyCells[boxSize * district + row2]);
}

void GameBoard::MixColumns()
{
	int district = rand() % boxSize;
	int column1 = rand() % boxSize;
	int column2;
	do
	{
		column2 = rand() % boxSize;
	} while (column1 == column2);
	for (int i = 0; i < gridSize; i++)
	{
		std::swap(readyCells[i][boxSize * district + column1], readyCells[i][boxSize * district + column2]);
	}

}

void GameBoard::MixDistrictsVertically()
{
	int district1 = rand() % boxSize;
	int district2;
	do
	{
		district2 = rand() % boxSize;
	} while (district1 == district2);
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < boxSize; j++)
		{
			std::swap(readyCells[i][boxSize * district1 + j], readyCells[i][boxSize * district2 + j]);
		}
	}
}

void GameBoard::MixDistrictsHorizontally()
{
	int district1 = rand() % boxSize;
	int district2;
	do
	{
		district2 = rand() % boxSize;
	} while (district1 == district2);
	for (int i = 0; i < boxSize; i++)
	{
		readyCells[boxSize * district1 + i].swap(readyCells[boxSize * district2 + i]);
	}
}

void GameBoard::TransposingBoard()
{
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = i; j < gridSize; j++)
		{
			std::swap(readyCells[i][j], readyCells[j][i]);
		}
	}
}

void GameBoard::CreateDecision()
{
	int choice;
	for (int i = 0; i < 25; i++)
	{
		choice = rand() % 5 + 1;
		switch (choice)
		{
			case(1):
				this->MixColumns();
				break;
			case(2):
				this->MixRows();
				break;
			case(3):
				this->MixDistrictsHorizontally();
				break;
			case(4):
				this->MixDistrictsVertically();
				break;
		}		
	}
}

int GameBoard::GetBoxSize()
{
	return boxSize;
}

