#pragma once
#include <vector>
#include "SudokuSolver.h"

class GameBoard
{
private:
	int boxSize;
	int gridSize;
	std::vector<std::vector<int>> readyCells;
	std::vector<std::vector<int>> userCells;
	void CreateBasicBoard();
	void MixRows();
	void MixColumns();
	void MixDistrictsVertically();
	void MixDistrictsHorizontally();
	void TransposingBoard();
	void CreateDecision();
public:
	GameBoard(int boxSize);
	void CreateTask(int difficulty);
	std::vector<std::vector<int>>& GetUserCells();
	int GetBoxSize();
};

