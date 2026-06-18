#include "tsp.h"
#include <iostream>
#include <vector>
#include <limits>
#include <numeric>
#include <fstream>
#include <queue>
#include <algorithm>

const int INF = std::numeric_limits<int>::max();

// Forward declaration: tells the compiler read() is defined in driver.obj
void read(char const* filename, MAP& map, int& TotalCity);

// State node for Best-First exploration search tree
struct Node {
  std::vector<int> path;
  std::vector<bool> visited;
  int current_cost;
  int lower_bound;

  // Evaluates min-heap structure sorting by lowest lower bound estimate
  bool operator>(const Node& other) const {
    return lower_bound > other.lower_bound;
  }
};

// Computes the lower bound using the relaxed 2-cheapest-edges formula
int CalculateLowerBound(const Node& node, const MAP& map, int num_cities) {
  int bound = node.current_cost * 2;
  int curr_city = node.path.back();

  // 1. Handle incoming/outgoing bounds for the absolute start city (0)
  if (node.path.size() == 1) {
    int min1 = INF, min2 = INF;
    for (int j = 0; j < num_cities; ++j) {
      if (j != 0 && map[0][j] < min1) { min2 = min1; min1 = map[0][j]; }
      else if (j != 0 && map[0][j] < min2) { min2 = map[0][j]; }
    }
    if (min1 != INF) bound += min1;
    if (min2 != INF) bound += min2;
  }
  else {
    int min_to_zero = INF;
    for (int j = 0; j < num_cities; ++j) {
      if (!node.visited[j] && map[j][0] < min_to_zero) {
        min_to_zero = map[j][0];
      }
    }
    if (min_to_zero != INF) bound += min_to_zero;
  }

  // 2. Handle outbound edge constraints for the current active end path node
  if (node.path.size() > 1 && node.path.size() < static_cast<size_t>(num_cities)) {
    int min_out = INF;
    for (int j = 0; j < num_cities; ++j) {
      if (!node.visited[j] && map[curr_city][j] < min_out) {
        min_out = map[curr_city][j];
      }
    }
    if (min_out != INF) bound += min_out;
  }

  // 3. Relaxed boundary calculations across remaining unvisited cities
  for (int i = 1; i < num_cities; ++i) {
    if (!node.visited[i]) {
      int min1 = INF, min2 = INF;
      for (int j = 0; j < num_cities; ++j) {
        if (i != j && map[i][j] < min1) { min2 = min1; min1 = map[i][j]; }
        else if (i != j && map[i][j] < min2) { min2 = map[i][j]; }
      }
      if (min1 != INF) bound += min1;
      if (min2 != INF) bound += min2;
    }
  }

  // Divide by two since paths reflect paired connected edge costs
  return (bound + 1) / 2;
}

std::vector<int> SolveTSP(char const* filename) {
  MAP map;
  int num_cities = 0;

  // Calls the function natively provided by driver.obj
  read(filename, map, num_cities);

  if (num_cities <= 0) {
    return std::vector<int>();
  }

  // Best-First Search Queue
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

  int best_total_cost = INF;
  std::vector<int> best_path;

  // Build the structural Root node starting from city index 0
  Node root;
  root.path.push_back(0);
  root.visited.assign(num_cities, false);
  root.visited[0] = true;
  root.current_cost = 0;
  root.lower_bound = CalculateLowerBound(root, map, num_cities);

  pq.push(root);

  while (!pq.empty()) {
    Node curr = pq.top();
    pq.pop();

    // Branch-and-bound pruning optimization 
    if (curr.lower_bound >= best_total_cost) {
      continue;
    }

    // Base case: check complete tours
    if (curr.path.size() == static_cast<size_t>(num_cities)) {
      int final_edge = map[curr.path.back()][0];
      if (final_edge != INF) {
        int complete_cost = curr.current_cost + final_edge;
        if (complete_cost < best_total_cost) {
          best_total_cost = complete_cost;
          best_path = curr.path;
          best_path.push_back(0); // Complete loop back to start node
        }
      }
      continue;
    }

    // Branching strategy out to adjacent unvisited paths
    for (int next_city = 0; next_city < num_cities; ++next_city) {
      if (!curr.visited[next_city] && map[curr.path.back()][next_city] != INF) {
        Node next_node;
        next_node.path = curr.path;
        next_node.path.push_back(next_city);
        next_node.visited = curr.visited;
        next_node.visited[next_city] = true;
        next_node.current_cost = curr.current_cost + map[curr.path.back()][next_city];
        next_node.lower_bound = CalculateLowerBound(next_node, map, num_cities);

        // Queue branch only if its lower estimate could beat the current local minimum
        if (next_node.lower_bound < best_total_cost) {
          pq.push(next_node);
        }
      }
    }
  }

  return best_path;
}