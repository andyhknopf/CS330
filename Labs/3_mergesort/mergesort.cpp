#ifndef MERGESORT_H
#define MERGESORT_H

// Forward declarations
static void merge(int *a, unsigned int low, unsigned int mid, unsigned int high);

// Merge Sort function using [low, high) index bounds
void mergesort(int * a, unsigned int p, unsigned int r) 
{
  // 1. Divide the array in half recursively
  // 2. When you can't divide recursively anymore,
  //      Merge sorted subarrays

  // Base case: Array has < 2 elements to sort
  if (r - p <= 1) 
      return;
  
  // Calculate midpoint
  int mid = p + (r - p) / 2;

  // Divide and conquer
  mergesort(a, p, mid);
  mergesort(a, mid, r);

  // Merge the sorted halves
  merge(a, p, mid, r);
}

// Helper function Merge both subarrays, final recursive step
void merge(int * a, unsigned int low, unsigned int mid, unsigned int high) 
{
  unsigned int lowerBoundIndex = mid - low;
  unsigned int upperBoundIndex = high - mid;

  // Create temporary left and right subarrays
  unsigned int* left = new unsigned int[lowerBoundIndex];
  unsigned int* right = new unsigned int[upperBoundIndex];

  // Copy data to temporary arrays
  for (unsigned int i = 0; i < lowerBoundIndex; ++i) 
      left[i] = a[low + i];
  for (unsigned int i = 0; i < upperBoundIndex; ++i)
      right[i] = a[mid + i];

  // First indices of the subarrays
  unsigned int i = 0, j = 0, k = low;  

  // Loop through each subarray starting from the bottom
  while (i < lowerBoundIndex && j < upperBoundIndex) 
  {
    // Compare left and right sides of the subarrays
    if (left[i] <= right[j]) 
    {
      a[k] = left[i];
      ++i;
    } 
    else 
    {
      a[k] = right[j];
      ++j;
    }

    // Increment the counter for the 
    ++k;
  }

  // Copy elements from the left side of subarray
  while (i < lowerBoundIndex) 
  {
    a[k] = left[i];
    ++i;
    ++k;
  }

  // Do the same with the right side
  while (j < upperBoundIndex) 
  {
    a[k] = right[j];
    ++k;
    ++j;
  }

  // Remember to delete
  delete[] left;
  delete[] right;
}

#endif // MERGESORT_H
