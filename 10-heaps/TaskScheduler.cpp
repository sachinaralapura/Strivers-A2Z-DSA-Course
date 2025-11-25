#include "heap.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Task {
    char name;
    unsigned int time;
    bool operator<(const Task &other) const {
        return time < other.time;
    }
    string toString() const {
        return "Task " + string(1, name) + ": " + to_string(time);
    }
    friend ostream &operator<<(ostream &os, const Task &task) {
        os << task.toString();
        return os;
    }
};

using TaskMaxHeap = BinaryHeap<Task, less<Task>>;

vector<Task> countFrequencies(vector<char> tasks) {
    int freq[26] = {0};
    for (char ch : tasks) {
        if (ch >= 'A' && ch <= 'Z')
            freq[ch - 'A']++;
        else
            throw std::invalid_argument("Invalid character in tasks: must be A-Z");
    }
    vector<Task> results;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > 0) {
            Task t;
            t.name = 'A' + i;
            t.time = freq[i];
            results.push_back(t);
        }
    }
    return results;
}

unsigned int TaskSchedulerOptimized(vector<char> tasks, int interval) {
    int freq[26] = {0};
    for (char ch : tasks) {
        freq[ch - 'A']++;
    }
    int maxFreq = 0;
    for (int i = 0; i < 26; i++) {
        maxFreq = max(maxFreq, freq[i]);
    }
    int maxFreqCount = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] == maxFreq) {
            maxFreqCount++;
        }
    }
    int result = (maxFreq - 1) * (interval + 1) + maxFreqCount;
    return max((unsigned int)tasks.size(), (unsigned int)result);
}

vector<Task> scheduledTasks;

unsigned int TaskScheduler(vector<char> tasks, int interval = 2) {
    vector<Task> taskList;
    try {
        taskList = countFrequencies(tasks);
    } catch (const std::invalid_argument &e) {
        cerr << e.what() << endl;
        return 0;
    }

    TaskMaxHeap taskHeap = TaskMaxHeap();
    vector<Task> tempTasks;

    for (const Task &T : taskList) {
        taskHeap.insertNode(T);
    }
    unsigned int maxTime = 0;
    while (!taskHeap.isEmpty()) {
        int n = interval;
        tempTasks.clear();
        int workDone = 0;
        // Try to execute n + 1 tasks
        for (int i = 0; i <= n; i++) {
            if (!taskHeap.isEmpty()) {
                Task t = taskHeap.removeRootNode();
                t.time -= 1;
                tempTasks.push_back(t);
                workDone++;
                scheduledTasks.push_back(t);
            }
        }
        
        bool anyRemaining = false;
        for (const Task &t : tempTasks) {
            if (t.time > 0) {
                anyRemaining = true;
                taskHeap.insertNode(t);
            }
        }
        
        if (anyRemaining) {
            maxTime += (n + 1); // We must wait for the full cycle
            // Add idle tasks for visualization if needed
            for(int i=0; i < (n + 1 - workDone); ++i) scheduledTasks.push_back(Task{'_', 0});
        } else {
            maxTime += workDone; // Last batch, only count actual work
        }
    }
    return maxTime;
}

int main() {
    vector<char> tasks = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B', 'C', 'C', 'C'};
    int interval = 2;
    
    cout << "--- Simulation Approach ---" << endl;
    int totalTime = TaskScheduler(tasks, interval);
    cout << "Total time: " << totalTime << endl;
    cout << "Schedule: ";
    for (const Task &t : scheduledTasks) {
        cout << t.name << " ";
    }
    cout << endl << endl;
    
    cout << "--- Optimized Math Approach ---" << endl;
    cout << "Total time: " << TaskSchedulerOptimized(tasks, interval) << endl;

    return 0;
}
