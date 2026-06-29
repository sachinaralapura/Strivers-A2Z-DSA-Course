#ifndef DP_UTILS
#define DP_UTILS
#include <iostream>
#include <vector>

struct Point {
	int x; // row
	int y; // col
};

enum class T_USED { RECURSION, RECURSION_MEMO, TABULATION };
inline std::ostream& operator<<(std::ostream& os, T_USED t_used)
{
	switch (t_used) {
	case T_USED::RECURSION:
		os << "Recursion";
		break;
	case T_USED::RECURSION_MEMO:
		os << "Recursion memoization";
		break;
	case T_USED::TABULATION:
		os << "Tabulation";
		break;
	}
	return os;
}
template <typename T> using Vecvec = std::vector<std::vector<T>>;
inline std::ostream& operator<<(std::ostream& os, const Vecvec<int>& matrix)
{
	if (matrix.empty()) {
		os << "[ ] (Empty Matrix)\n";
		return os;
	}
	std::streamsize user_width = os.width();
	if (user_width == 0)
		user_width = 4;

	// os << "[\n";
	for (const auto& row : matrix) {
		os << "[ ";
		for (const auto& element : row) {
			// 2. Explicitly apply the captured width to every element
			os.width(user_width);
			os << element << " ";
		}
		os << "]\n";
	}
	// os << "]\n";
	return os;
}
using cube = std::vector<std::vector<std::vector<int>>>;
#endif
