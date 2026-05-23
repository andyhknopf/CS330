// Author: Andrew Knopf
// CS330 - Algorithm Analysis Summer 2026
// Lab 1 - Lexicographical Permutation
// DigiPen Insitute of Technology (C) 2026
#include "perm-lexicographical.h"
#include <algorithm>
#include <iostream>
#include <vector>

// Forward declarations
static int findSmallestNonDecreasingSuffix(std::vector<int>& p);
static int findSmallestIncreaseIndex(std::vector<int>& p, const int suffixFront);

bool nextPermLexicographical(std::vector<int>& p) 
{
  // Find the smallest non-decreasing suffix
  int suffixFront = findSmallestNonDecreasingSuffix(p);
  
  // If no such index exists, we are at the last permutation
  if (suffixFront == -1) 
    return false; 

  // Find the smallest larger number than the suffix front
  int smallestIncreaseIndex = findSmallestIncreaseIndex(p, suffixFront);
  if (smallestIncreaseIndex == -1) 
    return false;

  // Swap suffix front with smallest larger number
  std::swap(p[suffixFront], p[smallestIncreaseIndex]);

  // If suffix was decreasing, you can just reverse them to sort in increasing order
  std::reverse(p.begin() + suffixFront + 1, p.end()); 

  // Successfully generated the next permutation
  return true; 
}

// Returns the index of the smallest number in the suffix sub-array that's larger than the front of the suffix
static int findSmallestIncreaseIndex(std::vector<int>& p, const int suffixFrontIndex) 
{
  // NOTE:
  //  I know this is not a professional way to do this but what do you want?
  //  I'd rather have INFINITY, but that compiled to 0 for some reason.
  int smallestIncrease = 100000;
  int smallestIncreaseIndex = -1;

  // Loop from the back of the suffix to the front
  int back = p.size() - 1;
  for (int i = back; i > suffixFrontIndex; --i) 
  {
    // Look for the smallest number that's also larger than the suffix front
    if (!(p[i] < smallestIncrease && p[i] > p[suffixFrontIndex]))
      continue;

    // Update the value and index
    smallestIncreaseIndex = i;
    smallestIncrease = p[smallestIncreaseIndex];
  }

  return smallestIncreaseIndex;
}

// Returns the front index of the smallest increasing suffix
static int findSmallestNonDecreasingSuffix(std::vector<int>& p) 
{
  // Loop the vector from back to front
  int back = p.size() - 1;
  for (int i = back; i > 0; --i) 
  {
    // If the value in front of the current index is decreasing
    if (p[i - 1] < p[i])
      return i - 1;   
  }

  // Return a failure code
  return -1;
}