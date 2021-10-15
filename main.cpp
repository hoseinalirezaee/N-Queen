#include <iostream>
#include "Solver.h"
#include <chrono>
#include <cstdlib>

using namespace std;

int main(int argc, char* args[])
{
	int n = 8;
	int times = 1;

	if (argc >= 2)
	{
		n = atoi(args[1]);
	}
	if (argc == 3)
	{
		times = atoi(args[2]);
	}

	Solver solver(n);

	auto start = chrono::high_resolution_clock::now();
	for (int i = 0; i < times; i++)
	{
		solver.solve();
	}
	auto end = chrono::high_resolution_clock::now();

	string unit = " (ms)";
	auto duration = end - start;
	long long time = chrono::duration_cast<chrono::milliseconds>(duration).count();
	if (time == 0)
	{
		time = chrono::duration_cast<chrono::microseconds>(duration).count();
		unit = " (us)";
	}
	if (time == 0)
	{
		time = chrono::duration_cast<chrono::nanoseconds>(duration).count();
		unit = " (ns)";
	}
	
	cout << "Total elapsed time: " << time << unit << endl;
	cout << "Average elapsed time: " << 1.0 * time / times << unit << endl;
	cout << solver.toString() << endl;

	return 0;
}