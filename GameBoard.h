#pragma once
#include <vector>
#include <math.h>
#include <fstream>
#include <random>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "SudokuSolver.h"

class GameBoard
{
private:
	int boxSize;
	int gridSize;
	std::vector<std::vector<int>> readyCells;
	std::vector<std::vector<int>> userCells;
	std::vector<int> blockedCells;
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);
	void CreateBasicBoard();
	void MixRows();
	void MixColumns();
	void MixDistrictsVertically();
	void MixDistrictsHorizontally();
	void TransposingBoard();
	void CreateEasyDecision();
	void CreateDecision(SudokuSolver &solver);
public:
	GameBoard();
	GameBoard(int boxSize);
	void CreateTask(int difficulty, SudokuSolver& solver);
	void LoadGameBoard();
	void SaveGameBoard();
	std::vector<std::vector<int>>& GetUserCells();
	std::vector<std::vector<int>>& GetReadyCells();
	int GetGridSize();
	bool checkBlocked(int cellNumber);
	void insertToBlocked(int cellNumber);
};
