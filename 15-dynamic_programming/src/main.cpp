#include "1d.hpp"
#include <iostream>
using namespace std;
int main()
{
	vector<int> arr = {2, 1, 4, 9};
	int res = max_sum_tabulated(arr , true);
	cout << res << endl;
	return 0;
}
