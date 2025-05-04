#include "ll.h"
#include "sll.h"
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
    vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Sll<int> *sll = new Sll<int>(v1);
    STARTHERE START_TIMER;
    // ------------------ RUN MAIN CODE HERE --------------------

    sll->rotate(9);
    sll->printAll();

    // ----------------------------------------------------------
    ENDHERE END_TIMER;

    return 0;
}
