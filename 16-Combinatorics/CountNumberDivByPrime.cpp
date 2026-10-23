#include <iostream>
#include <ostream>
#include <vector>

template <typename T> using Vecvec = std::vector<std::vector<T>>;
template <typename T>
std::ostream &operator<<(std::ostream &os, const Vecvec<T> &matrix) {
  if (matrix.empty()) {
    os << "[ ] (Empty Matrix)\n";
    return os;
  }
  std::streamsize user_width = os.width();
  if (user_width == 0)
    user_width = 4;

  // os << "[\n";
  for (const auto &row : matrix) {
    os << "[ ";
    for (const auto &element : row) {
      // 2. Explicitly apply the captured width to every element
      os.width(user_width);
      os << element << " ";
    }
    os << "]\n";
  }
  // os << "]\n";
  return os;
}

void recursion(int ind, std::vector<int> &nums, std::vector<int> &temp, int n,
               long long mul, int &count) {
  if (ind < 0) {
    if (temp.size() == 0)
      return;
    if (temp.size() & 1) {
      count = count + (n / mul);
    } else {
      count = count - (n / mul);
    }
    return;
  }

  // not take
  recursion(ind - 1, nums, temp, n, mul, count);
  // take
  long long res_mul = mul * nums[ind];
  if (res_mul <= n) {
    temp.push_back(nums[ind]);
    recursion(ind - 1, nums, temp, n, res_mul, count);
    temp.pop_back();
  }
}

int main() {
  int n = 100;
  std::vector<int> nums = {2, 3, 5, 7, 11, 13 , 17 , 19};
  std::vector<int> temp = {};
  int count = 0;
  recursion(nums.size() - 1, nums, temp, n, 1, count);
  std::cout << count << "\n";
}
