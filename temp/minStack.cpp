#include <iostream>
#include <vector>

using namespace std;

class MinStack {
public:
    MinStack() {

    }

    void push(int val) {
        nums.emplace_back(val);
        if (maintain.empty() || val <= maintain.back())
            maintain.emplace_back(val);
    }

    void pop() {
        if (nums.back() == maintain.back())
            maintain.pop_back();
        nums.pop_back();
    }

    int top() {
        return nums.back();
    }

    int getMin() {
        return maintain.back();
    }

private:
    vector<int> nums;
    vector<int> maintain;
};