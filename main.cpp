#include "GameBoard.h"
#include "SudokuGenerator.h"
#include <iostream>

int main()
{
	std::vector<std::vector<int>> grid1{ std::vector<int>{5, 3, 0, 0, 7, 0, 0, 0, 0},
	std::vector<int>{6, 0, 0, 1, 9, 5, 0, 0, 0},
	std::vector<int>{0, 9, 8, 0, 0, 0, 0, 6, 0},
	std::vector<int>{8, 0, 0, 0, 6, 0, 0, 0, 3},
	std::vector<int>{4, 0, 0, 8, 0, 3, 0, 0, 1},
	std::vector<int>{7, 0, 0, 0, 2, 0, 0, 0, 6},
	std::vector<int>{0, 6, 0, 0, 0, 0, 2, 8, 0},
	std::vector<int>{0, 0, 0, 4, 1, 9, 0, 0, 5},
	std::vector<int>{0, 0, 0, 0, 8, 0, 0, 7, 9} };
	grid1 = solveSudoku(grid1, 3, 3);
	for (int i = 0; i < std::size(grid1); i++)
	{
		for (int j = 0; j < std::size(grid1[0]); j++)
		{
			std::cout << grid1[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	/*srand(time(NULL));
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
	}*/
}