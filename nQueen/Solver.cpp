#include "Solver.h"
#include <sstream>
#include <vector>
#include <cmath>
Solver::Solver(int problemsize)
{
	srand(time(NULL));
	this->size = problemsize;
	this->board = new int[problemsize];
	MAX_NUMBER_OF_TRIES = 2 * problemsize;
}

Solver::~Solver()
{
	if (board != nullptr)
		delete[] board;
}

void Solver::solve()
{
	int numberOfTries = 0;
	int conflictedQueensCount = 0;
	initBoard(this->board, this->size);

	vector<int> candidateQueens;
	candidateQueens.reserve(size);

	getConflictedQueens(candidateQueens, board, size);
	conflictedQueensCount = candidateQueens.size();

	while (conflictedQueensCount)
	{
		arrayPermutation(this->board, this->size);
		numberOfTries = 0;
		conflictedQueensCount = 0;

		while ((conflictedQueensCount = candidateQueens.size()) && numberOfTries < MAX_NUMBER_OF_TRIES)
		{
			auto randomColumn = candidateQueens.at(rand() % candidateQueens.size());
			auto minConflictsIndex = minConflictIndexInColumn(board, randomColumn, size, candidateQueens);
			this->board[randomColumn] = minConflictsIndex;

			getConflictedQueens(candidateQueens, board, size);
			numberOfTries++;
		}
	}

}

string Solver::toString() const
{
	stringstream ss;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (board[j] == i)
				ss << "1";
			else
				ss << "0";
		}
		ss << endl;
	}

	return ss.str();
}

int Solver::conflictsWith(const int* board, int row, int column, int size)
{
	int conflictsCount = 0;
	for (int i = 0; i < size; i++)
	{
		if (i == column)
			continue;
		if (abs(i - column) == abs(board[i] - row) || board[i] == row)
			conflictsCount++;
	}
	return conflictsCount;
}

void Solver::swap(int* array, int i, int j)
{
	auto temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void Solver::arrayPermutation(int* array, int size)
{
	for (int i = 0; i < size; i++)
	{
		swap(array, i, rand() % size);
	}
}

void Solver::initBoard(int* board, int size)
{
	for (int i = 0; i < size; i++)
	{
		board[i] = i;
	}

	arrayPermutation(board, size);
}

void Solver::getConflictedQueens(vector<int>& list, const int *board, int boardSize)
{
	list.clear();
	int conflictsCount = 0;
	for (int i = 0; i < boardSize; i++)
	{
		if (conflictsCount = conflictsWith(board, board[i], i, boardSize))
		{
			list.push_back(i);
		}
	}
}

int Solver::minConflictIndexInColumn(const int* board, int column, int size, vector<int> &list)
{
	list.clear();
	int minConflict = conflictsWith(board, 0, column, size);
	int conflict = minConflict;
	list.push_back(0);

	for (int r = 1; r < size; r++)
	{
		conflict = conflictsWith(board, r, column, size);
		if (conflict == minConflict)
		{
			list.push_back(r);
		}
		else if (conflict < minConflict)
		{
			list.clear();
			minConflict = conflict;
			list.push_back(r);
		}
	}

	return list.at(rand() % list.size());
}

