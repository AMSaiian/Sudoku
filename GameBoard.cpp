#include "GameBoard.h"

GameBoard::GameBoard()
{
}

void GameBoard::CreateBasicBoard()
{
	for (int i = 0; i < 9; i++)
	{
		std::vector<int> row;
		for (int j = 0; j < 9; j++)
		{
			int number = (i * 3 + i / 3 + j) % 9 + 1;
			row.push_back(number);
		}
		readyCells.push_back(row);
	}
}

void GameBoard::MixRows()
{
	int district = rand() % 2;
	int row1 = rand() % 2;
	int row2;
	do
	{
		row2 = rand() % 2;
	} while (row1 == row2);
	readyCells[3 * district + row1].swap(readyCells[3 * district + row2]);
}

void GameBoard::MixColumns()
{
	int district = rand() % 3;
	int column1 = rand() % 3;
	int column2;
	do
	{
		column2 = rand() % 3;
	} while (column1 == column2);
	for (int i = 0; i < 9; i++)
	{
		std::swap(readyCells[i][3 * district + column1], readyCells[i][3 * district + column2]);
	}

}

void GameBoard::MixDistrictsVertically()
{
	int district1 = rand() % 3;
	int district2;
	do
	{
		district2 = rand() % 3;
	} while (district1 == district2);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::swap(readyCells[i][3 * district1 + j], readyCells[i][3 * district2 + j]);
		}
	}
}

void GameBoard::MixDistrictsHorizontally()
{
	int district1 = rand() % 3;
	int district2;
	do
	{
		district2 = rand() % 3;
	} while (district1 == district2);
	for (int i = 0; i < 3; i++)
	{
		readyCells[3 * district1 + i].swap(readyCells[3 * district2 + i]);
	}
}

void GameBoard::TransposingBoard()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = i; j < 9; j++)
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
