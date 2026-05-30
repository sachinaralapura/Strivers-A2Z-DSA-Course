#include <cstddef>
#include <cstdlib>
#include <unordered_map>
#include <vector>

// -------------- FIBONACCI ----------------
size_t fib_recursion(size_t, std::unordered_map<size_t, size_t>&);

size_t fib_bottom_up(size_t, std::unordered_map<size_t, size_t>&);

size_t fib_bottom_up_optimized(size_t);

size_t climbing_stairs(size_t n);

// Given a number of stairs and a frog, the frog wants to climb from the 0th stair to the (N-1)th
// stair. At a time the frog can climb either one or two steps. A height[N] array is also given.
// Whenever the frog jumps from a stair i to stair j, the energy consumed in the jump is
// abs(height[i]- height[j]). We need to return the minimum energy
// that can be used by the frog to jump from stair 0 to stair N-1..
int frog_jump_recursion(std::vector<int>& height);

// Given a number of stairs and a frog, the frog wants to climb from the 0th stair to the (N-1)th
// stair. At a time the frog can climb either one or two steps. A height[N] array is also given.
// Whenever the frog jumps from a stair i to stair j, the energy consumed in the jump is
// abs(height[i]- height[j]). We need to return the minimum energy
// that can be used by the frog to jump from stair 0 to stair N-1..
int frog_jump_tabulation(std::vector<int>& height);
