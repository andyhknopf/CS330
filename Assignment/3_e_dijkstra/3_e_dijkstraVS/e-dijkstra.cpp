#include "e-dijkstra.h" // e_dijkstra
#include <iostream>     // std::cerr
#include <fstream>      // std::fstream, std::getline
#include <vector>       // std::vector
#include <limits>       // IDK YET
#include <string>       // std::string
#include <sstream>      // std::stringstream, operator>>
#include <map>          // std::map

// Edge class definition
class Edge
{
  public:

    // Used to mark open and closed list
    typedef enum NodeStatus
    {
      OPEN,
      CLOSED,
      UNVISITED
    };

    // Big 4
    Edge(int toNode = 0, int fromNode = 0, int edgeWeight = 0);
    Edge(const Edge& other);
    Edge& operator=(Edge& other);
    ~Edge();
  
    // Getters & setters
    int To() const;
    void To(int);
    int From() const;
    void From(int);
    int Weight() const;
    void Weight(int);
  
  private:

    // Edge data
    int _to;
    int _from;
    int _weight;
};

// Forward declarations
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

  // Map of nodes, key is location #, value is list status (open list, closed list, or unvisited)
  std::map<int, Edge::NodeStatus> nodeList;
   
  // Note: Check path to every node from every node
  // 3. For each vertex, add first node to open list
  for (auto edge : *graph)
  {
    // Start at 0
    std::cout << "To " << edge.To() << ", From" << edge.From() << std::endl;
    // 4. While the open list isn't empty
    // while (true)
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
  }

  // All tests passed
  return true;
}

// Creates an undirect waypoint graph using edges
std::vector<Edge> * CreateEdgeGraph(char const * file, int * locationCount, int * rechargeCount, int * edgeCount)
{   
  // NOTE:
  // Input file format (in0):
  // 4 2 4    // N (number of location) K (maximum recharges) M(number of edges)
  // 0 1 100  // edge from 0 to 1 weight 100
  // 1 2 200
  // 2 3 300
  // 3 0 400

  // Create and open a text file
  std::fstream graphFile(file);

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
  std::getline(graphFile, line);
  std::stringstream lineStream(line);
  std::string token;

  // Set the graph parameters
  lineStream >> token;
  *locationCount = std::stoi(token);
  lineStream >> token;
  *rechargeCount = std::stoi(token);
  lineStream >> token;
  *edgeCount = std::stoi(token);

  // Now read the rest of the graph data
  int toNode = -1, fromNode = -1, edgeWeight = -1;
  while (std::getline(graphFile, line))
  {
    // Make a new lineStream
    lineStream = std::stringstream(line);

    // Read in the edge data (expected format: from, to, weight)
    lineStream >> token;
    fromNode = std::stoi(token);
    lineStream >> token;
    toNode = std::stoi(token);
    lineStream >> token;
    edgeWeight = std::stoi(token);

    // Construct the edge and add it to the graph
    graph->push_back(Edge(toNode, fromNode, edgeWeight));
  }

  // Close the file
  graphFile.close();

  return graph;
}

// Constructor
Edge::Edge(int toNode, int fromNode, int edgeWeight)
  : _to(toNode), 
    _from(fromNode), 
    _weight(edgeWeight)
{

}

// Copy constructor
Edge::Edge(const Edge& other)
  : _to(other._to),
    _from(other._from),
    _weight(other._weight)
{

}

// Operator =
Edge& Edge::operator=(Edge& other)
{
  // Shallow copy
  _to = other._to;
  _from = other._from;
  _weight = other._weight;
  return *this;
}

// Blank destructor
Edge::~Edge()
{
}

int Edge::To() const
{
  return _to;
}

void Edge::To(int to)
{
  _to = to;
}

int Edge::From() const
{
  return _from;
}

void Edge::From(int from)
{
  _from = from;
}

int Edge::Weight() const
{
  return _weight;
}

void Edge::Weight(int weight)
{
  _weight = weight;
}
