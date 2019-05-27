#include <iostream>
#include "Solver.h"
#include <chrono>
using namespace std;

int main()
{
	int n = 500;

	Solver solver(n);

	auto start = chrono::high_resolution_clock::now();

	solver.solve();

	auto end = chrono::high_resolution_clock::now();

	cout << chrono::duration_cast<chrono::milliseconds>(end - start).count() << endl << endl;
	//cout << solver.toString() << endl;

}
