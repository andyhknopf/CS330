#ifndef MERGESORT_H
#define MERGESORT_H

// Merge two sorted sub-arrays: [low, mid) and [mid, high)
void merge(int a[], int low, int mid, int high) {
    int n1 = mid - low;
    int n2 = high - mid;

    // Create temporary arrays
    int* left = new int[n1];
    int* right = new int[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i) {
        left[i] = a[low + i];
    }
    for (int j = 0; j < n2; ++j) {
        right[j] = a[mid + j];
    }

    // Merge the temporary arrays back into a[low..high-1]
    int i = 0;    // Initial index of first sub-array
    int j = 0;    // Initial index of second sub-array
    int k = low;  // Initial index of merged sub-array

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            a[k] = left[i];
            ++i;
        } else {
            a[k] = right[j];
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements of left[], if there are any
    while (i < n1) {
        a[k] = left[i];
        ++i;
        ++k;
    }

    // Copy the remaining elements of right[], if there are any
    while (j < n2) {
        a[k] = right[j];
        ++j;
        ++k;
    }

    // Free allocated memory
    delete[] left;
    delete[] right;
}

// Merge Sort function using [low, high) index bounds
void mergesort(int * a, unsigned int low, unsigned int high) {
    // Base case: 1 or 0 elements are already sorted
    if (high - low <= 1) {
        return;
    }

    // Calculate mid point safely
    int mid = low + (high - low) / 2;

    // Sort first and second halves
    mergesort(a, low, mid);
    mergesort(a, mid, high);

    // Merge the sorted halves
    merge(a, low, mid, high);
}

#endif // MERGESORT_H
