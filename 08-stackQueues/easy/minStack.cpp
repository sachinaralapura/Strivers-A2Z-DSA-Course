#include <bits/stdc++.h>
#include <iostream>
#include <stdexcept>
#include <utility>
using namespace std;

class MinStack {
  private:
    vector<pair<int, int>> ds;
    int Top;
    int curMin;

  public:
    MinStack() {
        Top = -1;
    }
    void push(int data) {
        if (Top == -1) {
            Top = 0;
            ds.push_back({data, data});
            curMin = data;
            return;
        }
        Top++;
        if (data < curMin) {
            curMin = data;
            ds.push_back({data, data});
        } else {
            ds.push_back({data, curMin});
        }
    }
    void pop() {
        if (Top == -1) {
            return;
        }
        ds.pop_back();
        Top--;
        curMin = ds.back().second;
    }

    int top() {
        if (Top == -1) {
            exit(1);
        }
        return ds[Top].first;
    }
    int getMin() {
        if (Top == -1) {
            exit(-1);
        }
        return ds[Top].second;
    }
};
// ================================================================================
template <typename T> class minStackOptimal {
  private:
    vector<T> ds;
    int Top;
    T currMin;

  public:
    minStackOptimal() {
        Top = -1;
    }
    void push(T data) {
        if (Top == -1) {
            currMin = data;
            ds.push_back(data);
            Top++;
            return;
        }
        Top++;
        if (data < currMin) {
            T val = 2 * data - currMin;
            ds.push_back(val);
            currMin = data;
        } else {
            ds.push_back(data);
        }
    }
    void pop() {
        if (Top == -1)
            throw out_of_range("stack is empty");
        T el = ds.pop_back();
        if (el < currMin)
            currMin = 2 * currMin - el;
        Top--;
    }
    T top() {
        if (Top == -1)
            throw out_of_range("stack is empty");

        T ele = ds[Top];
        if (ele < currMin)
            return currMin;
        return ele;
    }
    T getMin() {
        return currMin;
    }
};

int main() {
    minStackOptimal<int> ms;
    for (int i = 0; i < 10; i++) {
        ms.push(i + 1);
    }
    cout << ms.getMin() << endl;
    cout << ms.top() << endl;
}
