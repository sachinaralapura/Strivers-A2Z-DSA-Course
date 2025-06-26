#include <cstdlib>
#include <string>
using namespace std;

inline int atoi(string &str, int n) {
    if (n == 0) {
        return str[n] - '0';
    }
    return 10 * atoi(str, n - 1) + (str[n] - '0');
}
