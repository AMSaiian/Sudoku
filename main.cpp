#include "GameBoard.h"
#include <iostream>

int main()
{
	srand(time(NULL));
	GameBoard testBoard;
	testBoard.CreateBasicBoard();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << testBoard.readyCells[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl;
	testBoard.CreateDecision();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			std::cout << testBoard.readyCells[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}