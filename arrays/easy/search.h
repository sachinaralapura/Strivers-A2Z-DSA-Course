#include <iostream>
#include <bits/stdc++.h>
using namespace std;

template <typename T>
bool Linear_search(vector<T> &arr, int num)
{
    int i;
    int n = arr.size();
    for (i = 0; i < n; i++)
    {
        if (arr[i] == num)
            return true;
    }
    return false;
}

template <typename T>
vector<T> Union_brute(vector<T> &arr1, vector<T> &arr2)
{
    vector<T> temp = arr1;
    for (auto i : arr2)
    {
        if (!Linear_search(temp, i))
        {
            temp.push_back(i);
        }
    }
    return temp;
}

template <typename T>
vector<T> Union_map(vector<T> &arr1, vector<T> &arr2)
{
    map<T, int> freq;
    vector<T> Union;
    for (int i = 0; i < arr1.size(); i++)
        freq[arr1[i]]++;
    for (int i = 0; i < arr2.size(); i++)
        freq[arr2[i]]++;
    for (auto i : freq)
        Union.push_back(i.first);
    return Union;
}

template <typename T>
vector<int> Union_set(vector<T> &arr1, vector<T> &arr2)
{
    set<T> s;
    vector<T> Union;
    for (int i = 0; i < arr1.size(); i++)
        s.insert(arr1[i]);
    for (int i = 0; i < arr2.size(); i++)
        s.insert(arr2[i]);
    for (auto &i : s)
        Union.push_back(i);
    return Union;
}

// Problem Statement: Given an integer N and an array of size N-1 containing N-1 numbers between 1 to N.
// Find the number(between 1 to N), that is not present in the given array.

int Missing_brute(vector<int> &arr)
{
    for (int i = 1; i <= arr.size(); i++)
    {
        int flag = 0;
        for (int j = 0; j < arr.size(); j++)
        {
            if (arr[j] == i)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            return i;
        }
    }
    return -1;
}

int Missing_Opt(vector<int> &arr)
{
    int N = arr.size();
    int sum = (N * (N + 1)) / 2;
    int sum2 = 0;
    for (int i = 0; i < N - 1; i++)
        sum2 += arr[i];
    int missingNum = sum - sum2;
    return missingNum;
}

int Missing_XOR(vector<int> &arr)
{
    int N = arr.size();
    int xor1 = 0, xor2 = 0;
    for (int i = 0; i < N; i++)
    {
        xor1 = xor1 ^ (i + 1);
        xor2 = xor2 ^ arr[i];
    }
    xor1 = xor1 ^ N + 1;
    return (xor1 ^ xor2);
}

// Problem Statement : Given an array of N integers,
//  write a program to return an element that occurs more than N / 2 times in the given array.
//  You may consider that such an element always exists in the array.
int majorityElement(vector<int> &arr)
{
    int n = arr.size();
    map<int, int> mpp;
    for (int i = 0; i < n; i++)
    {
        mpp[arr[i]]++;
    }
    for (auto i : mpp)
    {
        if (i.second > floor(n / 2))
            return i.first;
    }
}

// Optimal Approach : Moore’s Voting Algorithm:
// https://takeuforward.org/data-structure/find-the-majority-element-that-occurs-more-than-n-2-times/
int majorityElement_moore(vector<int> &arr)
{
    int n = arr.size();
    int element = arr[0];
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == element)
            count++;
        else
            count--;

        if (count == 0)
        {
            count = 1;
            element = arr[i];
        }
    }
    int cnt1 = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == element)
            cnt1++;
    }
    if (cnt1 > (n / 2))
        return element;
    return -1;
}

// Find the elements that appears more than N / 3 times in the array
// Problem Statement : Given an array of N integers.Find the elements that appear more than N / 3 times in the array.
// If no such element exists, return an empty vector.
// Extended Boyer Moore’s Voting Algorithm
vector<int> n3majorityElement_morre(vector<int> &arr)
{
    int n = arr.size();
    int el1 = INT_MIN;
    int el2 = INT_MIN;
    int cnt1 = 0;
    int cnt2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (cnt1 == 0 && el2 != arr[i])
        {
            cnt1 = 1;
            el1 = arr[i];
        }
        else if (cnt2 == 0 && el1 != arr[i])
        {
            cnt2 = 1;
            el2 = arr[i];
        }
        else if (arr[i] == el1)
            cnt1++;
        else if (arr[i] == el2)
            cnt2++;
        else
        {
            cnt1--;
            cnt2--;
        }
    }
    vector<int> ls; // list of answers
    cnt1 = 0, cnt2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == el1)
            cnt1++;
        if (arr[i] == el2)
            cnt2++;
    }
    int mini = int(n / 3) + 1;
    if (cnt1 >= mini)
        ls.push_back(el1);
    if (cnt2 >= mini)
        ls.push_back(el2);

    return ls;
}