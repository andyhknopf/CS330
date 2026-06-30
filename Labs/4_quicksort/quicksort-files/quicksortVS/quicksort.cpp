// Andrew Knopf
// Lab #4 - Quicksort
// CS330 - Summer 2026
// DigiPen Institute of Technology (C) 2026
#include "quicksort.h" // quicksort, partition
#include <iostream> // cerr, swap

// Returns the pivot index of the new subarray
static int partition(int*, int, int);

// Basic quicksort algorithm
// TODO: What to do with 2 arguments
void quicksort(int* a, unsigned begin, unsigned end)
{
  // Safety case: array is empty or null
  if (!a)
  {
    std::cerr << "Array is empty!" << std::endl;
    return;
  }

  // 1. Base Case: one element left in sub-array
  if (end < begin)
    return;

  // 1. Split the array in half, f
  int pivotIndex = partition(a, (int)begin, (int)end);
  std::cout << pivotIndex << ", " << begin << ", " << end << std::endl;

  // 2. Recursively sort left and right subarrays
  quicksort(a, begin, pivotIndex - 1);
  quicksort(a, pivotIndex + 1, end);
}

// Helper function
int partition(int* a, int begin, int end)
{
  // Start at the end of the array
  int pivotIndex = end;
  int i = begin - 1;

  // Find first element larger than pivot, from beginning to end
  // Find first element smaller than pivot, from end to beginning
  for (unsigned j = begin; j <= end - 1; ++j)
  {
    // Skip if the pivot is smaller than the current element
    if (pivotIndex < 0 || a[j] >= a[pivotIndex])
      continue;

    // Increment the pivot and swap it
    ++i;
    std::swap(a[i], a[j]);
  }

  // Increment the pivot index and place it at the end of the array
  std::swap(a[i + 1], a[end]);

  // Returns the new pivot index
  return i + 1;
}