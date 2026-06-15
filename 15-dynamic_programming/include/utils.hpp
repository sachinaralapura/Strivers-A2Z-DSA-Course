#ifndef DP_UTILS
#define DP_UTILS
#include <iomanip> // For pretty formatting alignment
#include <iostream>
#include <vector>
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
using Vecvec = std::vector<std::vector<int>>;
inline std::ostream& operator<<(std::ostream& os, const Vecvec& matrix)
{
	if (matrix.empty()) {
		os << "[ ] (Empty Matrix)\n";
		return os;
	}

	os << "[\n";
	for (const auto& row : matrix) {
		os << "  [ ";
		for (const auto& element : row) {
			// std::setw(4) ensures columns line up beautifully if numbers have different digits
			os << std::setw(6) << element << " ";
		}
		os << "]\n";
	}
	os << "]\n";

	return os;
}

#endif
