#include "sub_seq.hpp"
#include <algorithm>

int AssignCookie::optimal(std::vector<int>& students, std::vector<int>& cookie)
{
	const int n = students.size();
	const int m = cookie.size();

	int cookie_index = 0;
	int student_index = 0;

	std::sort(students.begin(), students.end());
	std::sort(cookie.begin(), cookie.end());

	while (cookie_index < m && student_index < n) {
		if (cookie[cookie_index] >= students[student_index])
			student_index++;
		cookie_index++;
	}

	return 0;
}
