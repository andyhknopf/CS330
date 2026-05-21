#include "perm-lexicographical.h"
#include <algorithm>
#include <iostream>
#include <algorithm> // std::iterator
#include <cassert> // assert

std::vector<int>::iterator findSmallestNonDecreasing(std::vector<int>& p) const;

bool nextPermLexicographical (std::vector<int> & p) 
{
  // find smallest suffix that is NOT in decreasing order (it will be like 2641, a number, then larger number, then decreasing numbers)
  std::vector<int>::iterator firstDigit = findSmallestNonDecreasing(p);
  assert(firstDigit != nullptr, "This should never be null!");

  int nextLargest = *firstDigit; // First digit

  for (std::vector<int>::iterator it = p.end; it != firstDigit; --it)
  {
    // change the first digit of the suffix to the smallest digit in the suffix that is larger than it (in the example 2641, leading 2 will be changed to 4)

    // Find smallest value that's larger than the first digit
    if (*it < nextLargest && *it > *firstDigit)
    {
      nextLargest =

    }

    // sort the rest of the numbers in increasing order (i.e. make the smallest possible number with the remaining digits, in the example 261 will be changed to 126), resulting in the next larger number 4126
  }

  // if there is no such suffix, then we are at the largest possible number and there is no next larger number (in the example 654321 has no such suffix, since it is in decreasing order)
}

// Returns the leftmost index of the smallest non-decreasing suffix in the given vector,
std::vector<int>::iterator findSmallestNonDecreasing(std::vector<int>&p) const
{
  std::vector<int>::iterator it;   // Current index to check
  std::vector<int>::iterator left; // Index to the left of current index

  // Start at the rightmost value
  for (it = p.end; left != p.begin; --it, left = it - 1)
  {
    // If left value isn't bigger than the right value, you've found smallest non-decreasing suffix
    if (*it >= *left)
      return left;
  }
 
  // Failure case, decreasing suffix not found
  return nullptr;
}


