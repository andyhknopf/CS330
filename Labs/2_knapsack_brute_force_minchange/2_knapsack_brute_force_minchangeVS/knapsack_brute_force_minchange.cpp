// Andrew Knopf
// CS330 - Algorithm Analysis
// Summer 2026 
// DigiPen Institute of Technology 2026 (C)
#include "knapsack_brute_force_minchange.h"
#include <iostream> // std::cout for testing

// For testing the extra credit in visual studio
#if defined(_MSC_VER)
#include <intrin.h> // For MSVC C++ compilers

#elif defined(__GNUC__) || defined(__clang__)

// Just covering all my bases to be sure (thanks stack overflow)
#elif defined(__unix__) || defined(__APPLE__) || defined(_POSIX_VERSION)
#include <strings.h> // For POSIX systems only

#else
#include <strings.h> // Fallback standard C header

#endif

// ctor
GreyCode::GreyCode(int s) : _numElements(s), _iterations(0)
{
}

////////////////////////////////////////////////////////////////////////////////
std::pair< bool, std::pair< bool, int > > GreyCode::Next() 
{
  // Increase iterations at the start
  ++_iterations;

  // NOTE: Gray code is last position when msb = 1 and all other bits = 0
  bool last = true; // is this the last permutation 

  // NOTE: I think we turn off bits every 3rd iteration, 0th = 000, 1st = 001, 2nd = 011, 3rd = 010
  bool add = true; // is true if new value is 1 (add item), false otherwise 
  int  pos = 0; // which position is modified 

  // Lowest set bit
  int lowest_set_bit = _iterations & -_iterations;

  //int gray = i ^ (i >> 1); // convert to the corresponding Gray code value
  int grayValue = (_iterations ^_iterations >> 1);

  // Count how many times we shift right to find the 0-indexed position
  #if defined (_MSC_VER)
  {
    // Find the first bit (testing for Windows)
    unsigned long bitPosition;
    _BitScanForward(&bitPosition, (unsigned long)lowest_set_bit);
    pos = (int)bitPosition;
  }
  #else
  {
    pos = __builtin_ctz(lowest_set_bit);
  }
  #endif

  // Check if we are turning a bit off or on
  add = (grayValue & (1 << pos)) != 0;

  // The final value must equal 1 shifted left by (n - 1)
  last = (_iterations < ( (1 << _numElements) - 1));

  return std::make_pair(last, std::make_pair( add, pos ) );
}

////////////////////////////////////////////////////////////////////////////////
std::vector<bool> knapsack_brute_force( std::vector<Item> const& items, Weight const& W )
{
  // Initialize the graycode
  int itemCount = items.size();
  GreyCode gray(itemCount);

  // Weight of the current knapsack combination (inits to zero)
  Weight weight;

  // Track current knapsack
  std::vector<bool> knapsack(itemCount, false);
  int value = 0;

  // Track best so far knapsack
  std::vector<bool> bsfKnapsack(itemCount, false);
  int bsfValue = 0;


  // PrintStoreDebug(items); // Testing

  // Copied from driver
  bool hasNextPermutation = true;
  while (hasNextPermutation)
  {
    // Generate the next possible permutation (how does this coincide with the knapsack value?)
    std::pair< bool, std::pair< bool, int > > permutation = gray.Next();
    hasNextPermutation = permutation.first;
    bool add = permutation.second.first;
    int  pos = permutation.second.second;

    // Skip if given an invalid index
    if (pos >= itemCount)
      continue;

    // If gray.Next() spit out a valid permutation add = true, else false
    if (add)
    {
      // Add to the knapsack, and calculate the current weight
      knapsack[pos] = true;
      value += items[pos].GetValue();
      weight += items[pos].GetWeight();
    }
    else
    {
      // Don't add to the knapsack, and recalculate the current weight
      knapsack[pos] = false;
      value -= items[pos].GetValue();
      weight -= items[pos].GetWeight();
    }

    // Update the best permutation found if it fits within the constraints
    if (weight <= W && value > bsfValue) 
    {
      bsfValue = value;
      bsfKnapsack = knapsack;
    }
  }

  // From HW #1
  //max_value = 0
  //  for all subsets of items
  //  {
  //     if (sum of weights of items in the subset > capacity)
  //       continue;
  //     if (sum of values of items in the subset > max_value)
  //       max_value = sum of values of items in the subsets;
  //  }
  // return max_value;

  return bsfKnapsack;
}

void PrintStoreDebug(const std::vector<Item>& items)
{
  int itemCount = items.size();
  std::cout << "Printing store: " << std::endl;
  for (int i = 0; i < itemCount; ++i)
  {
    std::cout << "Item #" << i << ": ";
    std::cout << "Value: " << items[i].GetValue();
    std::cout << " Weight: " << items[i].GetWeight() << std::endl;
  }
}


