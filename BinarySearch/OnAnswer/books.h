// Allocate Minimum Number of Pages
// Problem Statement : Given an array ‘arr of integer numbers, ‘ar[i]’ represents the number of
// pages in the ‘i - th’ book.There are a ‘m’ number of students, and the task is
//  to allocate all the books to the students.Allocate books in such a way that:

// Each student gets at least one book.
// Each book should be allocated to only one student.
// Book allocation should be in a contiguous manner

// You have to allocate the book to ‘m’ students such that the maximum number of pages assigned to
// a student is minimum.If the allocation of books is not possible.return -1
#include <bits/stdc++.h>
using namespace std;
int countStudents(vector<int> &a, int pages) {
    int student = 1;
    long long pagesCnt = 0;
    for (int i = 0; i < a.size(); i++) {
        if (pagesCnt + a[i] <= pages) {
            pagesCnt += a[i];
        } else {
            student++;
            pagesCnt = a[i];
        }
    }
    return student;
}

int findMinMaxPages(vector<int> a, int student) {
    int n = a.size();
    if (student > n)
        return -1;
    int low = *max_element(a.begin(), a.end());
    int high = accumulate(a.begin(), a.end(), 0);

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (countStudents(a, mid) <= student) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return low;
}