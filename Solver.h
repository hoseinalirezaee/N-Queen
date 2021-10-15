#pragma once
#include <string>
#include <vector>
using namespace std;

class Solver
{
private:
	int* board;
	int size;
	int MAX_NUMBER_OF_TRIES;

public:
	Solver(int problemsize);
	~Solver();
	void solve();
	string toString() const;

private:
	int conflictsWith(const int* board, int row, int column, int size);
	inline void swap(int* array, int i, int j);
	inline void arrayPermutation(int* array, int size);
	void initBoard(int* board, int size);
	inline void getConflictedQueens(vector<int>& list, const int *board, int boardSize);
	inline int minConflictIndexInColumn(const int* board, int column, int size, vector<int> &list);
};