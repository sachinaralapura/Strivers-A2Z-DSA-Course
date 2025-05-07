#include "ll.h"
// #include "sll.h"
#include <chrono>
#define START_TIMER                                                            \
    auto timer_start = std::chrono::high_resolution_clock::now();
#define END_TIMER                                                              \
    auto timer_end = std::chrono::high_resolution_clock::now();                \
    auto timer_duration =                                                      \
        std::chrono::duration_cast<std::chrono::microseconds>(timer_end -      \
                                                              timer_start);    \
    std::cout << "Time taken : " << timer_duration.count() << " microseconds"  \
              << std::endl;

#define STARTHERE cout << "PROGRAM START" << endl;
#define ENDHERE cout << "PROGRAM END" << endl;

int main(int argc, char const *argv[]) {

    STARTHERE START_TIMER;
    // ------------------ RUN MAIN CODE HERE --------------------

    // ----------------------------------------------------------
    ENDHERE END_TIMER;

    return 0;
}
