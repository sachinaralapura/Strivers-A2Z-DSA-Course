#ifndef COMMON
#define COMMON
#include <string>
#include <vector>

namespace common {
using Matrix = std::vector<std::vector<int>>;
class MyError : public std::exception {
  private:
    std::string message;

  public:
    MyError(const std::string &msg) : message(msg) {}
    const char *what() const noexcept override { return message.c_str(); }
};
}; // namespace common
// using Matrix = std::vector<std::vector<int>>;
// class MyError : public std::exception {
//   private:
//     std::string message;

//   public:
//     MyError(const std::string &msg) : message(msg) {}
//     const char *what() const noexcept override { return message.c_str(); }
// };

#endif
