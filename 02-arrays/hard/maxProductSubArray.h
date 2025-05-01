#include <bits/stdc++.h>
using namespace std;

int maxProductSubArray_Brute(vector<int> &a)
{
    int n = a.size();
    int maxProduct = INT_MIN;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int product = 1;
            for (int k = i; k <= j; k++)
                product *= a[k];
            maxProduct = max(maxProduct, product);
        }
    }
    return maxProduct;
}

int maxProductSubArray_Better(vector<int> &a)
{
    int n = a.size();
    int maxProduct = INT_MIN;
    for (int i = 0; i < n - 1; i++)
    {
        int product = a[i];
        for (int j = i + 1; j < n; j++)
        {
            maxProduct = max(maxProduct, product);
            product *= a[j];
        }
        maxProduct = max(maxProduct, product);
    }
    return maxProduct;
}

int maxProductSubArray_Opt(vector<int> &a)
{
    int n = a.size();
    int maxProduct = INT_MIN;
    int prefix = 1;
    int suffix = 1;
    for (int i = 0; i < n; i++)
    {
        if (prefix == 0)
            prefix = 1;
        if (suffix == 0)
            suffix = 1;
        prefix = prefix * a[i];
        suffix = suffix * a[n - i - 1];
        maxProduct = max(maxProduct, max(prefix, suffix));
    }
    return maxProduct;
}