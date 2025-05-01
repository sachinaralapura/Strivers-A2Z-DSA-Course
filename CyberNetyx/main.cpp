// run all program here
// #include the required header in this directory
// timers are added to know the time taken by the code to run.

#include "trie.h"
#include <chrono>

#define START_TIMER auto timer_start = std::chrono::high_resolution_clock::now();
#define END_TIMER                                                                                  \
    auto timer_end = std::chrono::high_resolution_clock::now();                                    \
    auto timer_duration =                                                                          \
        std::chrono::duration_cast<std::chrono::microseconds>(timer_end - timer_start);            \
    std::cout << "Time taken : " << timer_duration.count() << " microseconds" << std::endl;

#define STARTHERE cout << "PROGRAM START" << endl;
#define ENDHERE cout << "PROGRAM END" << endl;

int main(int argc, char const *argv[]) {
    START_TIMER
    STARTHERE
    // ------------------ RUN MAIN CODE HERE --------------------
    Trie *t = new Trie();

    t->Insert("sachin");
    t->Insert("apple");
    t->Insert("apps");
    t->Insert("alphine");
    if (t->Search("sachin")) {
        cout << "exist" << endl;
    }
    if (t->StartWith("appd")) {
        cout << "true" << endl;
    }

    t->PrintTrie();
    // ----------------------------------------------------------
    ENDHERE END_TIMER return 0;
}
