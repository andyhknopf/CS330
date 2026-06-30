// Andrew Knopf
// Lab #4 - Quicksort
// CS330 - Summer 2026
// DigiPen Institute of Technology (C) 2026
#include "quicksort.h" // quicksort, partition
#include <iostream> // cerr
// #include <vector>
// Returns the pivot index of the new subarray
static int partition(int*, unsigned, unsigned);
// Swaps the two given values
// static void swap(int*, int*);

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
  int pivotIndex = partition(a, begin, end);
  // std::cout << pivotIndex << std::endl;

  // 2. Recursively sort left and right subarrays
  quicksort(a, pivotIndex + 1, end - 1);
  quicksort(a, begin, pivotIndex - 1);
}

// Helper function
int partition(int* a, unsigned begin, unsigned end)
{
  // Start at the end of the array
  unsigned pivotIndex = end;
  int i = begin;

  // Find first element larger than pivot, from beginning to end
  // Find first element smaller than pivot, from end to beginning
  for (unsigned j = begin; j < end; ++j)
  {
    // Skip if the pivot is smaller than the current element
    if (a[j] >= a[pivotIndex])
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

// Swaps two values, swapA, and swapB
// void swap(int* swapA, int* swapB)
// {
//   // Safety case: values are null
//   if (!swapA || !swapB)
//   {
//     std::cerr << "Attempted to dereference nullptr!" << std::endl;
//     return;
//   }
// 
//   // Hold a temporary variable
//   int temp = *swapB;
// 
//   *swapB = *swapA;
//   *swapA = temp;
// }
