#include "medium/sumofBeauty.h"
#include <chrono>
#include <iostream>

#define START_TIMER auto timer_start = std::chrono::high_resolution_clock::now();
#define END_TIMER                                                                                  \
    auto timer_end = std::chrono::high_resolution_clock::now();                                    \
    auto timer_duration =                                                                          \
        std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer_start);            \
    std::cout << "Time taken : " << timer_duration.count() << " microseconds" << std::endl;

#define STARTHERE cout << "PROGRAM START" << endl;
#define ENDHERE cout << "PROGRAM END" << endl;

int main(int argc, char const *argv[]) {
    string str = "aabcbaa";
    START_TIMER STARTHERE
    // ------------------ RUN MAIN CODE HERE --------------------
            cout << SumOfBeauty(str) << endl;
    // ----------------------------------------------------------
    ENDHERE END_TIMER

        return 0;
}
