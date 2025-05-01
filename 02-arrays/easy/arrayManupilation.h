#include <bits/stdc++.h>
#include <iostream>
using namespace std;
template <typename T> void zeroToLeft(vector<T> &arr);
// {
//     int n = arr.size();
//     int j = -1;
//     int i = 0;
//     for (int k = 0; k < n; k++)
//     {
//         if (arr[k] == 0)
//         {
//             j = k;
//             break;
//         }
//     }

//     if (j == -1)
//         return;

//     for (int i = j + 1; i < n; i++)
//     {
//         if (arr[i] != 0)
//         {
//             T t = arr[i];
//             arr[i] = arr[j];
//             arr[j] = t;
//             j++;
//         }
//     }
// }

// // Problem Statement : Given an array that contains only 1 and 0
// // return the count of maximum consecutive ones in the array.
int findMaxConsecutiveOnes(vector<int> &arr);
// {
//     int maxi = 0;
//     int cnt = 0;
//     for (int i = 0; i < arr.size(); i++)
//     {
//         if (arr[i] == 1)
//             cnt++;
//         else
//             cnt = 0;

//         maxi = max(maxi, cnt);
//     }
//     return maxi;
// }

// // Problem Statement: Given a non-empty array of integers arr,
// // every element appears twice except for one. Find that single one
int getSingleElement(vector<int> &arr);
// {
//     for (int i = 0; i < arr.size(); i++)
//     {
//         int num = arr[i]; // selected element
//         int cnt = 0;
//         // find the occurrence using linear search:
//         for (int j = 0; j < arr.size(); j++)
//         {
//             if (arr[j] == num)
//                 cnt++;
//         }
//         // if the occurrence is 1 return ans:
//         if (cnt == 1)
//             return num;
//     }
//     return -1;
// }
int getSingleElement_hash(vector<int> &arr);
// {
//     int N = arr.size();
//     // Find the maximum element:
//     int maxi = arr[0];
//     for (int i = 0; i < N; i++)
//     {
//         maxi = max(maxi, arr[i]);
//     }
//     vector<int> hash(maxi + 1, 0);
//     for (int i = 0; i < N; i++)
//     {
//         hash[arr[i]]++;
//     }
//     for (int i = 0; i < N; i++)
//     {
//         if (hash[arr[i]] == 1)
//             return arr[i];
//     }

//     // This line will never execute
//     // if the array contains a single element.
//     return -1;
// }

int getSingleElement_hashMap(vector<int> &arr) {
    // size of the array:
    int n = arr.size();

    // Declare the hashmap.
    // And hash the given array:
    unordered_map<int, int> mpp;
    for (int i = 0; i < n; i++) {
        mpp[arr[i]]++;
    }
    // Find the single element and return the answer:
    for (auto it : mpp) {
        if (it.second == 1)
            return it.first;
    }
    // This line will never execute
    // if the array contains a single element.
    return -1;
}

int getSingleElement_XOR(vector<int> &arr);
// {
//     // size of the array:
//     int n = arr.size();
//     int xorr = 0;
//     for (int i = 0; i < n; i++)
//     {
//         xorr = xorr ^ arr[i];
//     }
//     return xorr;
// }

// // Problem Statement : Given an array and a sum k, we need to print the
// //  length of the longest subarray that sums to k.
int getLongestSubarray(vector<int> &arr, long long k);
// {
//     int n = arr.size();
//     int len = 0;
//     for (int i = 0; i < n; i++)
//     {
//         long long sum = 0;
//         for (int j = i; j < n; j++)
//         {
//             sum += arr[j];
//             if (sum == k)
//                 len = max(len, j - i + 1);
//         }
//     }
//     return len;
// }

int getLongestSubarray_PrifixSum(vector<int> &arr, long long k);
// {
//     int n = arr.size();
//     int maxLen = 0;
//     long long sum = 0;
//     map<long long, int> prefixSum;

//     for (int i = 0; i < n; i++)
//     {
//         // calculate the prefix sum till index i:
//         sum += arr[i];
//         if (sum == k)
//             maxLen = max(maxLen, i + 1);

//         long long rem = sum - k;
//         if (prefixSum.find(rem) != prefixSum.end())
//         {
//             int len = i - prefixSum[rem];
//             maxLen = max(maxLen, len);
//         }

//         if (prefixSum.find(sum) != prefixSum.end())
//             prefixSum[sum] = i;
//     }
//     return maxLen;
// }

int getLongestSubarray_LRPointer(vector<int> &arr, long long k);
// {
//     int n = arr.size();
//     int left = 0;
//     int right = 0;
//     int maxLen = 0;
//     long long sum = arr[0];

//     while (right < n)
//     {
//         while (sum > k && left <= right)
//         {
//             sum = sum - arr[left];
//             left++;
//         }
//         if (sum == k)
//             maxLen = max(maxLen, right - left + 1);

//         right++;
//         if (right < n)
//             sum += arr[right];
//     }
//     return maxLen;
// }

// Problem Statement : Given an array of integers arr[] and an integer target.
// 1st variant : Return YES if there exist two numbers such that their sum is equal to the
// target.Otherwise, return NO. 2nd variant : Return indices of the two numbers such that their sum
// is equal to the target.Otherwise, we will return {-1, -1}. Note : You are not allowed to use the
// same element twice.Example : If the target is equal to 6 and num[1] = 3, then nums[1] + nums[1] =
// target is not a solution. first variant
string twoSum1_brute(vector<int> &arr, int k);
// {
//     int n = arr.size();
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             if (arr[i] + arr[j] == k)
//                 return "YES";
//         }
//     }
//     return "NO";
// }

// // second variant
vector<int> twoSum2(vector<int> &arr, int target);
// {
//     int n = arr.size();
//     vector<int> ans;
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             if (arr[i] + arr[j] == target)
//             {
//                 ans.push_back(i);
//                 ans.push_back(j);
//                 return ans;
//             }
//         }
//     }
//     return {-1, -1};
// }

string twoSum_hash(vector<int> &arr, int target);
// {
//     int n = arr.size();
//     unordered_map<int, int> mpp;
//     for (int i = 0; i < n; i++)
//     {
//         int num = arr[i];
//         int needed = target - num;
//         if (mpp.find(needed) != mpp.end())
//         {
//             return "YES";
//         }
//         mpp[num] = i;
//     }
//     return "NO";
// }

// 3 Sum : Find triplets that add up to a zero
// Problem Statement : Given an array of N integers, your task is to find unique triplets
// that add up to give a sum of zero.In short, you need to return an array of all the
// unique triplets[arr[a], arr[b], arr[c]] such that i != j, j != k, k != i, and their sum is equal
// to zero.
vector<vector<int>> threeSum_brute(vector<int> &arr);
// {
//     int n = arr.size();
//     set<vector<int>> st;
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             for (int k = j + 1; k < n; k++)
//             {
//                 if (arr[i] + arr[j] + arr[k] == 0)
//                 {
//                     vector<int> temp = {arr[i], arr[j], arr[k]};
//                     sort(temp.begin(), temp.end());
//                     st.insert(temp);
//                 }
//             }
//         }
//     }
//     vector<vector<int>> ans(st.begin(), st.end());
//     return ans;
// }

vector<vector<int>> threeSum_better(vector<int> &arr);
// {
//     int n = arr.size();
//     set<vector<int>> st;
//     for (int i = 0; i < n; i++)
//     {
//         set<int> hashset;
//         for (int j = i + 1; j < n; j++)
//         {
//             int third = -(arr[i] + arr[j]);
//             if (hashset.find(third) != hashset.end())
//             {
//                 vector<int> temp = {arr[i], arr[j], third};
//                 sort(temp.begin(), temp.end());
//                 st.insert(temp);
//             }
//             hashset.insert(arr[j]);
//         }
//     }
//     vector<vector<int>> ans(st.begin(), st.end());
//     return ans;
// }

// vector<vector<int>> threeSum_Opt(vector<int> &arr)
// {
//     int n = arr.size();
//     sort(arr.begin(), arr.end());

//     vector<vector<int>> ans;

//     for (int i = 0; i < n; i++)
//     {
//         if (i != 0 && arr[i - 1] == arr[i])
//             continue;
//         int j = i + 1;
//         int k = n - 1;
//         while (j < k)
//         {
//             int sum = arr[i] + arr[j] + arr[k];
//             if (sum > 0)
//                 k--;
//             else if (sum < 0)
//                 j++;
//             else
//             {
//                 vector<int> temp = {arr[i], arr[j], arr[k]};
//                 ans.push_back(temp);
//                 j++;
//                 k--;
//                 while (j < k && arr[j - 1] == arr[j])
//                     j++;
//                 while (j < k && arr[k + 1] == arr[k])
//                     k--;
//             }
//         }
//     }
//     return ans;
// }

// 4 Sum | Find Quads that add up to a target value
// Problem Statement : Given an array of N integers,
//  your task is to find unique quads that add up to give a target value.
//  In short, you need to return an array of all the unique quadruplets[arr[a], arr[b], arr[c],
//  arr[d]] such that their sum is equal to a given target.
vector<vector<int>> fourSum_Opt(vector<int> &arr, int target) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    vector<vector<int>> ans;

    for (int i = 0; i < n; i++) {
        if (i > 0 && arr[i - 1] == arr[i])
            continue;
        for (int j = i + 1; j < n; j++) {
            if (j > i + 1 && arr[j - 1] == arr[j])
                continue;
            int k = j + 1;
            int l = n - 1;
            while (k < l) {
                long long sum = (long long)arr[i] + arr[j] + arr[k] + arr[l];
                if (sum == target) {
                    vector<int> temp = {arr[i] + arr[j] + arr[k] + arr[l]};
                    ans.push_back(temp);
                    k++;
                    l--;
                    while (k < l && arr[k - 1] == arr[k])
                        k++;
                    while (k < l && arr[l + 1] == arr[l])
                        l--;
                } else if (sum < target)
                    k++;
                else
                    l--;
            }
        }
    }
    return ans;
}

// Kadane's Algorithm : Maximum Subarray Sum in an Array
// Problem Statement : Given an integer array arr, find the contiguous
// subarray(containing at least one number) which has the largest sum and returns its sum and prints
// the subarray.
long long maxSubarraySum(vector<int> &arr);
// {
//     int n = arr.size();
//     long long maxi = LONG_MIN;
//     long long sum = 0;
//     int start = 0;
//     int maxStart = -1;
//     int maxEnd = -1;
//     for (int i = 0; i < n; i++)
//     {
//         if (sum == 0)
//             start = i;
//         sum += arr[i];
//         if (sum > maxi)
//         {
//             maxStart = start;
//             maxEnd = i;
//             maxi = sum;
//         }
//         if (sum < 0)
//             sum = 0;
//     }
//     for (int i = maxStart; i <= maxEnd; i++)
//         cout << arr[i] << ",";
//     cout << endl;
//     return maxi;
// }

// Length of the longest subarray with zero Sum
// Problem Statement : Given an array containing both positive and negative integers,
// we have to find the length of the longest subarray with the sum of all elements equal to zero.
int maxLen(vector<int> &arr);
// {
//     int n = arr.size();
//     unordered_map<int, int> mpp;
//     int maxi = 0;
//     int sum = 0;
//     int startIndex = 0;
//     int endIndex = 0;
//     for (int i = 0; i < n; i++)
//     {
//         sum += arr[i];
//         if (sum == 0)
//         {
//             startIndex = 0;
//             endIndex = i;
//             maxi = i + 1;
//         }
//         else if (mpp.find(sum) != mpp.end())
//         {
//             startIndex = mpp[sum] + 1;
//             endIndex = i;
//             maxi = max(maxi, i - mpp[sum]);
//         }
//         else
//             mpp[sum] = i;
//     }
//     cout << startIndex << " " << endIndex << endl;
//     return maxi;
// }

// Count the number of subarrays with given xor K
// Problem Statement : Given an array of integers A and an integer B.
// Find the total number of subarrays having bitwise XOR of all elements equal to k.
int subarraysWithXorKOpt(vector<int> arr, int k) {
    int n = arr.size();
    unordered_map<int, int> mpp;
    mpp[0] = 1;
    int cnt = 0;
    int totalXor = 0;
    for (int i = 0; i < n; i++) {
        totalXor = totalXor ^ arr[i];
        int x = totalXor ^ k;
        cnt = cnt + mpp[x];
        mpp[totalXor]++;
    }
    return cnt;
}

// Merge Overlapping Sub - intervals
// Problem Statement : Given an array of intervals,
//  merge all the overlapping intervals and return an array of non - overlapping intervals.
vector<vector<int>> mergeOverlappingIntervalsOpt(vector<vector<int>> &arr) {
    int n = arr.size();
    vector<vector<int>> ans;
    sort(arr.begin(), arr.end());
    for (int i = 0; i < n; i++)
        if (ans.empty() || ans.back()[1] < arr[i][0])
            ans.push_back(arr[i]);
        else
            ans.back()[1] = max(ans.back()[1], arr[i][1]);

    return ans;
}

// Merge two Sorted Arrays Without Extra Space
// Problem statement: Given two sorted arrays arr1[] and arr2[] of sizes n and m
// in non-decreasing order. Merge them in sorted order. Modify arr1 so that it contains
// the first N elements and modify arr2 so that it contains the last M elements.
void merge(vector<long long> &arr1, vector<long long> &arr2) {
    int n = arr1.size();
    int m = arr2.size();
    int left = n - 1;
    int right = 0;
    while (left >= 0 && right < m) {
        if (arr1[left] > arr2[right]) {
            swap(arr1[left], arr2[right]);
            left--;
            right++;
        } else
            break;
    }
    sort(arr1.begin(), arr1.end());
    sort(arr2.begin(), arr2.end());
}

void swapIfGreater(vector<long long> &arr1, vector<long long> &arr2, int index1, int index2) {
    if (arr1[index1] > arr2[index2])
        swap(arr1[index1], arr2[index2]);
}

void Merge_gap(vector<long long> &arr1, vector<long long> &arr2) {
    int n = arr1.size();
    int m = arr2.size();
    int len = (n + m);
    int gap = (len / 2) + (len % 2);

    while (gap > 0) {
        int left = 0;
        int right = left + gap;
        while (right < len) {
            // arr1 && arr2
            if (left < n && right >= n)
                swapIfGreater(arr1, arr2, left, right - n);
            // arr2 && arr2
            else if (left >= n)
                swapIfGreater(arr2, arr2, left - n, right - n);
            // arr1 && arr1
            else
                swapIfGreater(arr1, arr1, left, right);
            left++;
            right++;
        }
        if (gap == 1)
            break;
        gap = (gap / 2) + (gap % 2);
    }
}
// // Stock Buy And Sell
// // Problem Statement : You are given an array of prices where prices[i] is the price of a given
// stock on an ith day.
int BuySell(vector<int> &arr);
// {
//     int n = arr.size();
//     int maxDiff = 0;
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = i + 1; j < n; j++)
//         {
//             if (arr[j] > arr[i])
//             {
//                 maxDiff = max(maxDiff, arr[j] - arr[i]);
//             }
//         }
//     }
//     return maxDiff;
// }

// int BuySell_Opt(vector<int> &arr)
// {
//     int n = arr.size();
//     int maxProfit = 0;
//     int minPrice = INT_MAX;
//     for (int i = 0; i < n; i++)
//     {
//         minPrice = min(arr[i], minPrice);
//         maxProfit = max(maxProfit, arr[i] - minPrice);
//     }
//     return maxProfit;
// }

// // Rearrange Array Elements by Sign
// // Problem Statement :
// // There’s an array ‘A’ of size ‘N’ with an equal number of positive and negative elements.
// // Without altering the relative order of positive and negative elements,
// // you must return an array of alternately positive and negative values.
vector<int> RearrangebySign(vector<int> &arr);
// {
//     vector<int> ans;
//     int n = arr.size();
//     int posIndex = 0;
//     int negIndex = 1;
//     for (int i = 0; i < n; i++)
//     {
//         if (arr[i] < 0)
//         {
//             ans[negIndex] = arr[i];
//             negIndex += 2;
//         }
//         else
//         {
//             ans[posIndex] = arr[i];
//             posIndex += 2;
//         }
//     }
//     return ans;
// }

// // next_permutation : find next lexicographically greater permutation
// // Problem Statement : Given an array Arr[] of integers, rearrange the numbers of the given array
// into the
// //  lexicographically next greater permutation of numbers.If such an arrangement is not possible,
// // it must rearrange to the lowest possible order(i.e., sorted in ascending order).
// // Input format :
// //  Arr[] = {1, 3, 2}
// // Output:
// //  Arr[] = {2, 1, 3}

// // Explanation : All permutations of{1, 2, 3} are{{1, 2, 3}, {1, 3, 2}, {2, 13}, {2, 3, 1}, {3,
// 1, 2}, {3, 2, 1}}.So,
// // the next permutation just after{1, 3, 2} is{2, 1, 3}.
// bool Next_permutation(vector<int> &arr);
// template <typename T>
// void printVector(vector<T> &arr)
// {
//     cout << "{ ";
//     for (int i = 0; i < arr.size(); i++)
//         cout << arr[i] << ",";
//     cout << " }" << endl;
// }

// template <typename T>
// void AllPermutations(vector<T> &arr)
// {
//     do
//     {
//         printVector(arr);
//     } while (Next_permutation(arr));
// }

// bool Next_permutation(vector<int> &arr)
// {
//     int n = arr.size();
//     int breakIndex = -1;
//     // find the break point
//     for (int i = n - 2; i >= 0; i--)
//     {
//         if (arr[i] < arr[i + 1])
//         {
//             breakIndex = i;
//             break;
//         }
//     }
//     if (breakIndex == -1)
//     {
//         reverse(arr.begin(), arr.end());
//         return false;
//     }

//     // swap breakIndex element with least great element to the right of the breakIndex
//     for (int i = n - 1; i > breakIndex; i--)
//     {
//         if (arr[i] > arr[breakIndex])
//         {
//             swap(arr[i], arr[breakIndex]);
//             break;
//         }
//     }
//     reverse(arr.begin() + breakIndex + 1, arr.end());
//     return true;
// }

// // Leaders in an Array
// // Problem Statement : Given an array,print all the elements which are leaders.
// // A Leader is an element that is greater than all of the elements on its right side in the
// array. vector<int> printLeadersBruteForce(vector<int> &arr)
// {
//     int n = arr.size();
//     vector<int> ans;
//     for (int i = 0; i < n; i++)
//     {
//         bool flag = true;
//         for (int j = i + 1; j < n; j++)
//             if (arr[i] < arr[j])
//             {
//                 flag = false;
//                 break;
//             }
//         if (flag)
//             ans.push_back(arr[i]);
//     }
//     return ans;
// }

// vector<int> printLeadersOptimal(vector<int> &arr)
// {
//     int n = arr.size();
//     vector<int> ans;
//     int maxi = arr[n - 1];
//     ans.push_back(arr[n - 1]);
//     for (int i = n - 2; i >= 0; i--)
//     {
//         if (arr[i] > maxi)
//         {
//             ans.push_back(arr[i]);
//             maxi = max(maxi, arr[i]);
//         }
//     }

//     return ans;
// }

// Longest Consecutive Sequence in an Array
// Problem Statement : You are given an array of ‘N’ integers.
// You need to find the length of the longest sequence which contains the consecutive elements.
// int longestSuccessiveElements(vector<int> &arr)
// {
//     unordered_set<int> st;
//     int maxCnt = 0;
//     for (auto i : arr)
//         st.insert(i);
//     for (auto it : st)
//     {
//         if (st.find(it - 1) == st.end())
//         {
//             int count = 1;
//             int x = it;
//             while (st.find(x + 1) != st.end())
//             {
//                 x = x + 1;
//                 count++;
//             }
//             maxCnt = max(maxCnt, count);
//         }
//     }
//     return maxCnt;
// }

// Set Matrix Zero
// Problem Statement : Given a matrix if an element in the matrix is 0
// then you will have to set its entire column and row to 0 and then return the matrix.
// vector<vector<int>> zeroMatrix(vector<vector<int>> &matrix)
// {
//     int rowSize = matrix.size();
//     int colSize = matrix[0].size();

//     vector<int> rows(rowSize, 0);
//     vector<int> cols(colSize, 0);

//     for (int i = 0; i < rowSize; i++)
//     {
//         for (int j = 0; j < colSize; j++)
//         {
//             if (matrix[i][j] == 0)
//             {
//                 rows[i] = 1;
//                 cols[j] = 1;
//             }
//         }
//     }

//     for (int i = 0; i < rowSize; i++)
//     {
//         for (int j = 0; j < colSize; j++)
//         {
//             if (rows[i] || cols[j])
//                 matrix[i][j] = 0;
//         }
//     }
//     return matrix;
// }

// vector<vector<int>> zeroMatrixOpt(vector<vector<int>> &matrix)
// {
//     int rowSize = matrix.size();
//     int colSize = matrix[0].size();

//     // vector<int> rows(rowSize, 0); -> matrix[...][0]
//     // vector<int> cols(colSize, 0); -> matrix[0][...]
//     int cols0 = 1;
//     for (int i = 0; i < rowSize; i++)
//     {
//         for (int j = 0; j < colSize; j++)
//         {
//             if (matrix[i][j] == 0)
//             {
//                 matrix[i][0] = 0;
//                 if (j != 0)
//                     matrix[0][j] = 0;
//                 else
//                     cols0 = 0;
//             }
//         }
//     }

//     for (int i = 1; i < rowSize; i++)
//     {
//         for (int j = 1; j < colSize; j++)
//         {
//             if (matrix[i][j] != 0)
//                 if (matrix[i][0] == 0 || matrix[0][j] == 0)
//                     matrix[i][j] = 0;
//         }
//     }

//     if (matrix[0][0] == 0)
//         for (int j = 1; j < colSize; j++)
//             matrix[0][j] = 0;

//     if (cols0 == 0)
//         for (int i = 0; i < rowSize; i++)
//             matrix[i][0] = 0;

//     return matrix;
// }

// Rotate Image by 90 degree
// Problem Statement : Given a matrix, your task is to rotate the matrix 90 degrees clockwise.
// vector<vector<int>> rotateMatrix(vector<vector<int>> &matrix)
// {
//     int n = matrix.size();
//     int m = matrix[0].size();
//     // transpose the matrix
//     for (int i = 0; i < n; i++)
//         for (int j = 0; j < i; j++)
//             swap(matrix[i][j], matrix[j][i]);

//     // reverse the
//     for (int i = 0; i < n; i++)
//         reverse(matrix[i].begin(), matrix[i].end());
//     return matrix;
// }

// Spiral Traversal of Matrix
// vector<int> SpiralTraversal(vector<vector<int>> &matrix)
// {
//     int n = matrix.size();
//     int m = matrix[0].size();
//     vector<int> ans;
//     int left = 0;       // left 0 to m;
//     int right = m - 1;  // right m to 0;
//     int top = 0;        // top 0 to n;
//     int bottom = n - 1; // botton n to 0;

//     while (top <= bottom && left <= right)
//     {
//         // For moving left to right
//         for (int i = left; i <= right; i++)
//             ans.push_back(matrix[top][i]);

//         top++;

//         // For moving top to bottom
//         for (int i = top; i <= bottom; i++)
//             ans.push_back(matrix[i][right]);

//         right--;

//         // For moving right to left
//         if (top <= bottom)
//         {
//             for (int i = right; i >= left; i--)
//                 ans.push_back(matrix[bottom][i]);

//             bottom--;
//         }

//         if (left <= right)
//         {
//             for (int i = bottom; i >= top; i--)
//                 ans.push_back(matrix[i][left]);

//             left++;
//         }
//     }
//     return ans;
// }

// Count Subarray sum Equals K
// Problem Statement : Given an array of integers and an integer k,
// return the total number of subarrays whose sum equals k.
// A subarray is a contiguous non - empty sequence of elements within an array.
int findAllSubarraysWithGivenSum(vector<int> &arr, int k);
// {
//     int n = arr.size();
//     map<int, int> mpp;
//     mpp[0] = 1;
//     int count = 0;
//     int PrefixSum = 0;
//     for (int i = 0; i < n; i++)
//     {
//         PrefixSum += arr[i];
//         int remove = PrefixSum - k;
//         count += mpp[remove];
//         mpp[PrefixSum] += 1;
//     }
//     return count;
// }

// Program to generate Pascal's Triangle
// Variation 1 : Given row number r and column number c.Print the element at position(r, c) in
// Pascal’s triangle. int nCr(int n, int r); int pascalTriangle(int r, int c)
// {
//     int element = nCr(r - 1, c - 1);
//     return element;
// }

int nCr(int n, int r) {
    long long res = 1;
    for (int i = 0; i < r; i++) {
        res = res * (n - i);
        res = res / (i + 1);
    }
    return (int)(res);
}

// Variation 2:  Print the n - th row of Pascal’s triangle.
// void pascalTriangleRow(int n)
// {
//     for (int i = 1; i <= n; i++)
//     {
//         cout << nCr(n - 1, i - 1) << " ";
//     }
// }

// Variation 3 : Given the number of rows n.Print the first n rows of Pascal’s triangle.
vector<vector<int>> pascalTriangle(int n) {
    vector<vector<int>> ans;
    // Store the entire pascal's triangle:
    for (int row = 1; row <= n; row++) {
        vector<int> tempLst; // temporary list
        for (int col = 1; col <= row; col++)
            tempLst.push_back(nCr(row - 1, col - 1));

        ans.push_back(tempLst);
    }
    return ans;
}