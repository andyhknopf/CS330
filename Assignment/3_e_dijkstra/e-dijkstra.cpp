// Andrew Knopf
// Assignment #3 - e_dijkstra
// CS330 - Summer 2026
// DigiPen Institute of Technology (C)
#include "e-dijkstra.h" // e_dijkstra
#include <iostream>     // cerr
#include <fstream>      // fstream, getline
#include <vector>       // vector, push back, etc...
#include <limits>       // max
#include <string>       // string
#include <sstream>      // stringstream
#include <map>          // map
#include <queue>        // priority queue

// Forward declarations
class Edge;
class Node;

static bool CreateEdgeGraph(char const*, int&, int&, int&, int, std::map<int, Node*>&);
static int ShortestPath(int, int, int, std::map<int, Node*>&); // Returns distance to the shortest 
static void DeleteGraph(std::map<int, Node*>&);

// Macros
static const int DIST_PER_RECHARGE = 350;

// Edge helper class
class Edge
{
public:
  Edge(int, int, int);

  // Getters
  int To() const;
  int From() const;
  int Weight() const;

private:
  int _from;
  int _to;
  int _weight;
};

// Node helper class
class Node
{
public:
  Node(int);
  ~Node();

  int ID() const;

  // List of edges this 
  std::vector<Edge*> edges;

private:
  int _locationID;
};

//eturns true if all valid node pairs can reach each other within range constraints
bool e_dijkstra(char const* file, int range)
{
  int numLocations = 0, maximumRecharges = 0, numEdges = 0;
  std::map<int, Node*> nodeMap;

  // Create an edge graph, and check for failures
  if (!CreateEdgeGraph(file, numLocations, maximumRecharges, numEdges, range, nodeMap))
    return false;

  // Find every path from every other path
  for (int i = 0; i < numLocations; ++i)
  {
    for (int j = 0; j < numLocations; ++j)
    {
      // Skip checking path towards yourself, we are already there
      if (i == j)
        continue;

      // Get the distance to the path
      int pathDistance = ShortestPath(i, j, maximumRecharges, nodeMap);

      // If a node pair is entirely disconnected
      if (pathDistance == std::numeric_limits<int>::max())
      {
        DeleteGraph(nodeMap);
        return false;
      }

      if (pathDistance > range)
      {
        DeleteGraph(nodeMap);
        return false;
      }
    }
  }

  DeleteGraph(nodeMap);
  return true;
}

// Clean up helper to prevent memory leaks
void DeleteGraph(std::map<int, Node*>& nodeMap)
{
  for (auto& pair : nodeMap)
  {
    delete pair.second;
  }

  nodeMap.clear();
}

// Parses graph and populates nodes safely regardless of entry order
bool CreateEdgeGraph(char const* file, int& locationCount, int& rechargeCount, int& edgeCount, int range, std::map<int, Node*>& nodeMap)
{
  // Attempt to open the input file and check for errors
  std::ifstream graphFile(file);
  if (!graphFile.is_open())
  {
    std::cerr << "Error opening file!" << std::endl;
    return false;
  }

  // If the file is empty something when wrong
  std::string line;
  if (!std::getline(graphFile, line))
    return false;

  // Store the graph data 
  std::stringstream lineStream(line);
  lineStream >> locationCount >> rechargeCount >> edgeCount;

  // Check if the vehicle has enough capacity
  int battery = (rechargeCount) * DIST_PER_RECHARGE; // Hardc
  if (battery < range)
    return false;

  // Initialize all expected nodes up front to prevent missing IDs
  for (int i = 0; i < locationCount; ++i)
    nodeMap[i] = new Node(i);

  // Now read in the rest of the file
  int fromNode = -1, toNode = -1, edgeWeight = -1;
  while (std::getline(graphFile, line))
  {
    // Read in a line of edge data
    std::stringstream edgeStream(line);
    if (!(edgeStream >> fromNode >> toNode >> edgeWeight))
      break;

    // Check for errors
    if (edgeWeight < 0)
      break;

    // Have edges for both directions since it is an undirected graph, (high memory draw)
    Edge* forwardEdge = new Edge(fromNode, toNode, edgeWeight);
    Edge* backwardEdge = new Edge(toNode, fromNode, edgeWeight);

    nodeMap[fromNode]->edges.push_back(forwardEdge);
    nodeMap[toNode]->edges.push_back(backwardEdge);
  }

  // Close the file
  graphFile.close();
  return true;
}

// Djikstra's algorithm to find the shortest path between startId and endId
int ShortestPath(int startId, int endId, int rechargeCount, std::map<int, Node*>& nodeMap)
{
  // Skip early if attempting to pathfind to yourself
  if (startId == endId)
    return 0;

  // Map the weights from startId to different nodes. 
  // Key is node ID, value is distance weight
  std::map<int, int> weights;
  for (const auto& pair : nodeMap)
    weights[pair.first] = std::numeric_limits<int>::max();

  // Open list
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> openList;

  // Push the first node onto the list
  weights[startId] = 0;
  openList.push({ 0, startId });

  // Battery (remember to recharge once before the trip)
  const int DIST_PER_RECHARGE = 350;
  int battery = (rechargeCount) * DIST_PER_RECHARGE;

  // While the open list isn't empty
  while (!openList.empty())
  {
    // Pop a node off of the list
    int currentDist = openList.top().first;
    int parentNode = openList.top().second;
    openList.pop();

    // If parent node is the end 
    if (parentNode == endId)
      return currentDist;

    // Search through all the neighbors of the parent node
    for (Edge* edge : nodeMap[parentNode]->edges)
    {
      // Node ID, and weight
      int neighbor = edge->To();
      int weight = edge->Weight();
      int addedWeight = weights[parentNode] + weight;
      int batteryDraw = battery - addedWeight;

      // Skip if the we're revisiting a node and its not cheaper from this direction
      // OR the battery can't handle it
      if (addedWeight > weights[neighbor] || batteryDraw <= 0)
        continue;
      
      // If there is a cheaper path available
      weights[neighbor] = weights[parentNode] + weight;
      openList.push({ weights[neighbor], neighbor });

      // Deplete the battery if c
      battery -= addedWeight;
    }
  }

  return weights[endId];
}

// Edge implementations
Edge::Edge(int fromNode = 0, int toNode = 0, int edgeWeight = 0)
  : _from(fromNode),
  _to(toNode),
  _weight(edgeWeight)
{

}

int Edge::To() const
{
  return _to;
}

int Edge::From() const
{
  return _from;
}

int Edge::Weight() const
{
  return _weight;
}

// Node implementations
Node::Node(int id)
  : edges(std::vector<Edge*>()),
  _locationID(id)
{
  // Empty constructor
}

// Destructor
Node::~Node()
{
  // Clean up dynamically allocated edges owned by this node
  for (Edge* e : edges)
    delete e;
}

int Node::ID() const
{
  return _locationID;
}