#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(int boxSize)
{
	this->boxSize = boxSize;
	this->gridSize = boxSize * boxSize;
}

std::vector<std::vector<int>> SudokuSolver::solveSudoku(std::vector<std::vector<int>> grid, std::tuple<int,int,int> limitation)
{
	if (tableRows.empty())
		fillRows();
	std::vector<std::tuple<int, int, int>> tempRow;
	if (limitation != std::tuple<int, int, int>())
	{
		tempRow = tableRows[limitation];
		tableRows.erase(limitation);
	}
	fillColumns();
	std::vector<std::tuple<int, int, int>> solution;
	std::tuple<int, int, int> tempCell;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (grid[i][j])
			{
				tempCell = { i, j, grid[i][j] };
				solution.push_back(tempCell);
				select(tempCell);
			}
		}
	}
	solution = alghorithmX(solution);
	if (!tempRow.empty())
		tableRows[limitation] = tempRow;
	if (solution.empty())
	{
		return std::vector<std::vector<int>>(gridSize, std::vector<int>(gridSize, 0));
	}
	else
	{
		int row;
		int column;
		int number;
		for (int i = 0; i < size(solution); i++)
		{
			row = std::get<0>(solution[i]);
			column = std::get<1>(solution[i]);
			number = std::get<2>(solution[i]);
			grid[row][column] = number;
		}
	}
	return grid;
}

std::tuple<int, int> SudokuSolver::findCellForHint(std::vector<std::vector<int>> grid)
{
	if (tableRows.empty())
		fillRows();
	fillColumns();
	std::tuple<int, int, int> tempCell;
	for (int i = 0; i < gridSize; i++)
	{
		for (int j = 0; j < gridSize; j++)
		{
			if (grid[i][j])
			{
				tempCell = { i, j, grid[i][j] };
				select(tempCell);
			}
		}
	}
	int amCandidates = 10;
	std::tuple<int, int> cell;
	auto itC = tableColumns.begin();
	for (int i = 0; i < std::size(tableColumns) / 4; i++)
	{
		if (itC->second.size() < amCandidates)
		{
			amCandidates = itC->second.size();
			cell = { std::get<1>(itC->first), std::get<2>(itC->first) };
			if (amCandidates == 1)
				break;
		}
		itC++;
	}
	return cell;
}

void SudokuSolver::fillRows()
{
	std::tuple<int, int, int> rc, rn, cn, bn, rcn;
	std::vector<std::tuple<int, int, int>> limitations;
	for (int number = 1; number < gridSize + 1; number++)
	{
		for (int column = 0; column < gridSize; column++)
		{
			for (int row = 0; row < gridSize; row++)
			{
				int box = (row / boxSize) * boxSize + (column / boxSize);
				rc = { 1, row, column };
				rn = { 2, row, number };
				cn = { 3, column, number };
				bn = { 4, box, number };
				limitations = {rc, rn, cn, bn};
				rcn = { row, column, number };
				tableRows[rcn] = limitations;
			}
		}
	}
}

void SudokuSolver::fillColumns()
{
	tableColumns.clear();
	auto itR = tableRows.begin();
	for (int i = 0; i < std::size(tableRows); i++)
	{
		std::tuple<int, int, int> value = itR->first;
		auto key = itR->second;
		for (int j = 0; j < std::size(key); j++)
		{
			tableColumns[key[j]].insert(value);
		}
		itR++;
	}
}

std::vector<std::set<std::tuple<int, int, int>>> SudokuSolver::select(std::tuple<int, int, int> row)
{
	std::vector<std::set<std::tuple<int, int, int>>> columns;
	std::tuple<int, int, int> xlimitation;
	std::tuple<int, int, int> ylimitation;
	std::tuple<int, int, int> cell;
	for (int i = 0; i < std::size(tableRows[row]); i++)
	{
		xlimitation = tableRows[row][i];
		for (auto number = tableColumns[xlimitation].begin(); number != tableColumns[xlimitation].end(); number++)
		{
			cell = *number;
			for (int j = 0; j < std::size(tableRows[cell]); j++)
			{
				ylimitation = tableRows[cell][j];
				if (xlimitation != ylimitation)
				{
					tableColumns[ylimitation].erase(cell);
				}
			}
		}
		columns.push_back(tableColumns[xlimitation]);
		tableColumns.erase(xlimitation);
	}
	return columns;
}

void SudokuSolver::deselect(std::tuple<int, int, int> row, std::vector<std::set<std::tuple<int, int, int>>> columns)
{
	std::tuple<int, int, int> xlimitation;
	std::tuple<int, int, int> ylimitation;
	std::tuple<int, int, int> cell;
	for (int i = std::size(tableRows[row]) - 1; i > -1; i--)
	{
		xlimitation = tableRows[row][i];
		tableColumns[xlimitation] = columns.back();
		columns.pop_back();
		for (auto number = tableColumns[xlimitation].begin(); number != tableColumns[xlimitation].end(); number++)
		{
			cell = *number;
			for (int j = 0; j < std::size(tableRows[cell]); j++)
			{
				ylimitation = tableRows[cell][j];
				if (xlimitation != ylimitation)
				{
					tableColumns[ylimitation].insert(cell);
				}
			}
		}
	}
}

std::vector<std::tuple<int, int, int>>
SudokuSolver::alghorithmX(std::vector<std::tuple<int, int, int>> cover)
{
	if (tableColumns.empty())
		return cover;
	else
	{
		int min = 10;
		std::tuple<int, int, int> minKey;
		for (auto itX = tableColumns.begin(); itX != tableColumns.end(); itX++)
		{
			if (std::size(itX->second) < min)
			{
				min = std::size(itX->second);
				minKey = itX->first;
			}
		}
		std::vector<std::set<std::tuple<int, int, int>>> temp;
		std::vector<std::tuple<int, int, int>> solution;
		for (int i = 0; i < min; i++)
		{
			auto subset = tableColumns[minKey].begin();
			std::advance(subset, i);
			cover.push_back(*subset);
			temp = select(cover.back());
			solution = alghorithmX(cover);
			if (!solution.empty())
				return solution;
			deselect(cover.back(), temp);
			cover.pop_back();
		}
		return std::vector<std::tuple<int, int, int>>();
	}
}