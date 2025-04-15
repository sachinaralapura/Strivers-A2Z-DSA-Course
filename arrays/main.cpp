
#include "hard/maxProductSubArray.h"
int main(int argc, char const *argv[])
{
    vector<int> nums = {1, 2, -3, 0, -4, -5};
    cout << "The maximum product subarray: " << maxProductSubArray_Opt(nums);
    return 0;
}
