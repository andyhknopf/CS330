#include "e-dijkstra.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>
#include <stringstream>

// Input file format (in0):
// 4 2 4    // N (number of location) K (maximum recharges) M(number of edges)
// 0 1 100  // edge from 0 to 1 weight 100
// 1 2 200
// 2 3 300
// 3 0 400


struct Edge
{
    int to;
    int from;
    int weight;
};

static std::vector<Edge> * CreateEdgeGraph(char const * file, int * locationCount, int * rechargeCount, int * edgeCount);


// Returns true if the path is possible in the given range, 
bool e_dijkstra( char const * file, int range)
{
    // Note: Remember to recharge at the beginning of the trip

    // Vector of edges (from, to, weight)
    std::vector<Edge> * graph = nullptr;
    
    // 1. Read the input file
    // 2. Create edge list or other search space representation
    int numLocations = 0, maximumRecharges = 0, numEdges = 0;
    graph = CreateEdgeGraph(file, &numLocations, &maximumRecharges, &numEdges);
    
    // Note: Check path to every node from every node
    // 3. For each vertex, add first node to open list
    for (auto edge : graph)
    {
        // 4. While the open list isn't empty
        {
            // 5. Pop the cheapest parent node off the list
        
            // 6. For all the neighboring children of the parent
            {
                // 7. If child neighbor isn't on open or closed list
                {
                    // Add to open list
                }
    
                // 8. Else if child node is on either list AND new this new one is cheaper
                {
                    // Take old expensive one off both lists and put new cheaper one on open list
                }
            }
    
            // 9. Place parent node on closed list
        }

        // Open list is empty, path is impossible
        return false;
    }

    // All tests passed
    return true;
}

static std::vector<Edge> * CreateEdgeGraph(char const * file, int * locationCount, int * rechargeCount, int * edgeCount)
{   
    // Create and open a text file
    std::fstream graphFile("filename.txt");

    // Check for errors
    if (!graphFile.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        return nullptr;
    }

    // Allocate memory for the graph
    std::vector<Edge> * graph = new std::vector<Edge>();
  
    // Read the first line from the file
    std::string line;
    std::stringstream lineStream(line);
    std::getline(graphFile, line);
    std::token;

    // Set the graph parameters
    lineStream >> token;
    *locationCount = std::stoi(token);
    lineStream >> token;
    *rechargeCount = std::stoi(token);
    lineStream >> token;
    *edgeCount = std::stoi(token);

    // std::cout << *locationCount << ' ' << *rechargeCount << ' ' << *edgeCount << std::endl; // TESTING

    // Now read the rest of the graph

    // Close the file
    graphFile.close();
}