#include <iostream>
#include <vector>
#include <ctime>
#include "large_number.h"

using std::vector;  using std::cout;
using std::endl;    using std::cin;
using std::cerr;

int main()
{
	large_number no1, no2;
	ll times;
	cerr << "Input x, y, times:" << endl;

	double _start = clock() * 0.1 / CLOCKS_PER_SEC;
	cin >> no1 >> no2 >> times;
	cerr << "cin: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "no1 + no2 = " << (no1 + no2) << endl;
	cerr << "+: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "no1 - no2 = " << (no1 - no2) << endl;
	cerr << "-: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "no1 > no2 = " << (no1 > no2) << endl;
	cerr << ">: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "no1 < no2 = " << (no1 < no2) << endl;
	cerr << "<: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "no1 >= no2 = " << (no1 >= no2) << endl;
	cerr << ">=: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "no1 <= no2 = " << (no1 <= no2) << endl;
	cerr << "<=: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "no1 != no2 = " << (no1 != no2) << endl;
	cerr << "!=: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "no1 == no2 = " << (no1 == no2) << endl;
	cerr << "==: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "no1 * no2 = " << (no1 * no2) << endl;
	cerr << "*: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	large_number q = no1 / no2;
	cout << "no1 / no2 = " << (q) << endl;
	cout << "no1 % no2 = " << (no1 - q * no2) << endl;
	cerr << "/,%: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;

	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "nth_root(no1) = " << (nth_root(no1, times)) << endl;
	cerr << "nth_root: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;
	
	_start = clock() * 0.1 / CLOCKS_PER_SEC;
	cout << "no1 ^ times = " << (nth_pow(no1, times)) << endl;
	cerr << "times: " << clock() * 0.1 / CLOCKS_PER_SEC - _start << " s" << endl;

	return 0;
}