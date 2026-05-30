#include "1d.hpp"
#include <iostream>
using namespace std;
int main()
{
	vector<int> height = {2, 1, 3, 5, 4};
	int res = frog_jump_tabulation(height);
	cout << res << endl;
}
