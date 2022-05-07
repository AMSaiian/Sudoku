#pragma once
#include "GameBoard.h"

std::vector<std::vector<int>> solveSudoku(std::vector<std::vector<int>> grid, int columnSize, int rowSize);

void fillXset(std::vector<std::tuple<std::string, std::tuple<int, int>>>& X_set, int gridSize);

void fillYset(std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple <int, int>>>>& Y_set, 
	          int rows, int columns, int gridSize);

std::map<std::tuple<std::string, std::tuple<int, int>>, std::set<std::tuple<int, int, int>>> 
findExactCover(std::vector<std::tuple<std::string, std::tuple<int, int>>> X_set, 
               std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple <int, int>>>>& Y_set);

std::vector<std::set<std::tuple<int, int, int>>>
select(std::map<std::tuple<std::string, std::tuple<int, int>>, std::set<std::tuple<int, int, int>>>& X_mod,
	   std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple <int, int>>>>& Y_set,
	   std::tuple<int, int, int> row);

void deselect(std::map<std::tuple<std::string, std::tuple<int, int>>, std::set<std::tuple<int, int, int>>>& X_mod,
	std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple<int, int>>>>& Y_set,
	std::tuple<int, int, int> row, std::vector<std::set<std::tuple<int, int, int>>> columns);

std::vector<std::tuple<int, int, int>>
alghorithmX(std::map<std::tuple<std::string, std::tuple<int, int>>, std::set<std::tuple<int, int, int>>>& X_mod,
	std::map<std::tuple<int, int, int>, std::vector<std::tuple<std::string, std::tuple<int, int>>>>& Y_set,
	std::vector<std::tuple<int, int, int>> cover);