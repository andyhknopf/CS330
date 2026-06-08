#include "knapsack_brute_force_minchange.h"
//#include <iostream>

GreyCode::GreyCode(int s)
{
}

////////////////////////////////////////////////////////////////////////////////
std::pair< bool, std::pair< bool, int > > GreyCode::Next() {
    
    
    
    
    
  int  pos = 0;// which position is modified 
    bool add = true; // is true if new value is 1 (add item), false otherwise 
    bool last = true; // is this the last permutation 
    return std::make_pair( !last, std::make_pair( add, pos ) );
}

////////////////////////////////////////////////////////////////////////////////
std::vector<bool> knapsack_brute_force( std::vector<Item> const& items, Weight const& W )
{
  return std::vector<bool>();
}
