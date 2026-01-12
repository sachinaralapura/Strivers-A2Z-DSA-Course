#ifndef SORT_BUBBLE
#define SORT_BUBBLE
template <typename T> void bubble_sort(T arr[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        bool didSwap = false;
        for (int j = 0; j < i; j++)
            if (arr[j] > arr[j + 1]) {
                T temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                didSwap = true;
            }

        if (!didSwap)
            break;
    }
}

#endif
