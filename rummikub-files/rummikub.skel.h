#ifndef RUMMIKUB_H
#define RUMMIKUB_H
#include <fstream>
#include <vector>
#include <iostream>

enum Color { Red, Green, Blue, Yellow };


struct Tile {
    int     denomination;
    Color   color;
};

std::ostream& operator<<(std::ostream& os, Tile const& t) {
    os << "{ "<< t.denomination << ",";
    switch ( t.color ) {
        case Red:      os << "R"; break;
        case Green:    os << "G"; break;
        case Blue:     os << "B"; break;
        case Yellow:   os << "Y"; break;
    }
    os << " }";
    return os;
}

class RummiKub {
    public:
        RummiKub(); // empty hand
        void Add( Tile const& ); // add a tile to hand

        void Solve(); // solve

        // get solution - groups
        std::vector< std::vector< Tile > > GetGroups() const;
        // get solution - runs
        std::vector< std::vector< Tile > > GetRuns() const;
        // if both vectors are empty - no solution possible
    private:
};

#endif
