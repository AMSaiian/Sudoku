#pragma once
#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <string>

class GameBoard
{
public:
	std::vector<std::vector<int>> readyCells;
	std::vector<std::vector<int>> userCells;
public:
	GameBoard();
	void CreateBasicBoard();
	void MixRows();
	void MixColumns();
	void MixDistrictsVertically();
	void MixDistrictsHorizontally();
	void TransposingBoard();
	void CreateDecision();
};

