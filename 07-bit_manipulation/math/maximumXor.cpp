#include <iostream>
int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(NULL);
  unsigned long long l;
  unsigned long long r;
  unsigned long long res = 0;
  std::cin >> l >> r;
  for (int i = 63; i >= 0; i--) {
    auto bit_l = (l >> i) & 1;
    auto bit_r = (r >> i) & 1;
    if (bit_l != bit_r) {
      res = (1ULL << (i + 1)) - 1;
      break;
    }
  }
  std::cout << res << "\n";
  return 0;
}
