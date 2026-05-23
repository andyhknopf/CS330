#include "perm-lexicographical.h"
#include <algorithm>
#include <iostream>


// NOTES
// find smallest suffix that is NOT in decreasing order(it will be like 2641, a number, then larger number, then decreasing numbers)
// change the first digit of the suffix to the smallest digit in the suffix that is larger than it(in the example 2641, leading 2 will be changed to 4)
// sort the rest of the numbers in increasing order(i.e.make the smallest possible number with the remaining digits, in the example 261 will be changed to 126), resulting in the next larger number 4126
// if there is no such suffix, then we are at the largest possible number and there is no next larger number(in the example 654321 has no such suffix, since it is in decreasing order)

constexpr auto ALREADY_AT_LARGEST = -1;
constexpr auto TOO_BIG = 100000;

// Helper functions
static int findSmallestIncreasing(std::vector<int>& p);
static int findSmallestIncreaseIndex(std::vector<int>& p, const int suffixFront);

bool nextPermLexicographical (std::vector<int> & p) 
{
  // find smallest suffix that is NOT in decreasing order (it will be like 2641, a number, then larger number, then decreasing numbers)
  int suffixFront = findSmallestIncreasing(p);

  // if there is no such suffix, then we are at the largest possible number and there is no next larger number (in the example 654321 has no such suffix, since it is in decreasing order)
  if (suffixFront == ALREADY_AT_LARGEST)
    return false;

  // Value of the beginning of the suffix
  int val = p[suffixFront];

  // Find smallest value that's larger than the first digit
  int smallestIncreaseIndex = findSmallestIncreaseIndex(p, suffixFront);
  if (smallestIncreaseIndex == ALREADY_AT_LARGEST)
    return false;
  
  // Swap smallest larger value with the front
  std::swap(p[suffixFront], p[smallestIncreaseIndex]);

  // Sort the rest of the array
  int back = p.size() - 1;
  std::sort(&p[suffixFront + 1], &p[back]);

  // NOTE: I don't know what im supposed to be returning here?
  return true;
}

// Returns the index of the value that's the smallest larger number than the value indexed at 'suffixFront'
int findSmallestIncreaseIndex(std::vector<int>& p, const int suffixFront)
{
  // Track the smallest increase in the array and where it is
  int smallestIncrease = TOO_BIG;
  int smallestIncreaseIndex = -1;

  // Loop the suffix from back to front
  int back = p.size() - 1;
  int index = back;
  for (int i = back; i > suffixFront; --i)
  {
    // If the value is smaller than the smallest found value
    if (p[i] < smallestIncrease && p[i] > p[suffixFront])
    {
      smallestIncreaseIndex = i;
      smallestIncrease = p[smallestIncreaseIndex];
    }
  }
  
  return smallestIncreaseIndex;
}

// Returns the leftmost index of the smallest non-decreasing suffix in the given vector,
int findSmallestIncreasing(std::vector<int>&p)
{
  int back = p.size(); // Back index of the vector

  // Loop bakcwards through the vector
  int index = back;
  for (index > 0; --index;)
  {
    // Splitting up for readability + debugging
    int thisDigit = p[index];
    int nextDigit = p[index - 1];

    // Check for the first occurrence of a decrease in value starting from p.end() to p.begin()
    if (nextDigit < thisDigit)
      return index - 1;
  }

  return ALREADY_AT_LARGEST; // Code for 
}


