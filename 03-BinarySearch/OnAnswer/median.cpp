#include <bits/stdc++.h>
using namespace std;

double median(vector<int> a, vector<int> b) {
    int n1 = a.size();
    int n2 = b.size();
    int n = (n1 + n2);
    int ind2 = n / 2;
    int ind1 = ind2 - 1;

    int cnt = 0;
    int ind1Ele = -1;
    int ind2Ele = -1;

    int i = 0, j = 0;
    while (i < n1 && j < n2) {
        if (a[i] < b[j]) {
            if (cnt == ind1)
                ind1Ele = a[i];
            if (cnt == ind2)
                ind2Ele = a[i];
            cnt++;
            i++;
        } else {
            if (cnt == ind1)
                ind1Ele = b[j];
            if (cnt == ind2)
                ind2Ele = b[j];
            cnt++;
            j++;
        }
    }

    while (i < n1) {
        if (cnt == ind1)
            ind1Ele = a[i];
        if (cnt == ind2)
            ind2Ele = a[i];
        cnt++;
        i++;
    }
    while (j < n2) {
        if (cnt == ind1)
            ind1Ele = b[j];
        if (cnt == ind2)
            ind2Ele = b[j];
        cnt++;
        j++;
    }
    if (n % 2 == 1)
        return (double)ind2Ele;

    return (double)((double)(ind1Ele + ind2Ele)) / 2.0;
}
