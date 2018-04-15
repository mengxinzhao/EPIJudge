#include <stdexcept>
#include <vector>
#include <set>
#include <iostream>
#include "test_framework/test_timer.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::set;

struct GraphVertex {
  enum Color { white, gray, black } color = white;
  vector<GraphVertex*> edges;
};

// DFS travel and if encountering  one vertex already seen
// that is deadlock
bool IsDeadlocked_DFS(GraphVertex *graph,   set<GraphVertex*> &visited){
    visited.insert(graph);
    
    for (auto &vertex: graph->edges) {
        if (visited.find(vertex)== visited.end()){
            if (IsDeadlocked_DFS(vertex,visited))
                return true;
        }else
            return true;
    }
    
    return false;
}

bool IsDeadlocked(vector<GraphVertex>* graph) {
    GraphVertex last_vertex = graph->back();
    set<GraphVertex*> visited;
    for (auto &vertex: *graph) {
        if ( visited.find(&vertex)== visited.end() &&  IsDeadlocked_DFS(&vertex,visited))
            return true;
    }
    return false;
}

struct Edge {
  int from;
  int to;
};

template <>
struct SerializationTraits<Edge> : UserSerTraits<Edge, int, int> {};

bool HasCycleWrapper(TestTimer& timer, int num_nodes,
                     const vector<Edge>& edges) {
  vector<GraphVertex> graph;
  if (num_nodes <= 0) {
    throw std::runtime_error("Invalid num_nodes value");
  }
  graph.reserve(num_nodes);

  for (int i = 0; i < num_nodes; i++) {
    graph.push_back(GraphVertex{});
  }

  for (const Edge& e : edges) {
    if (e.from < 0 || e.from >= num_nodes || e.to < 0 || e.to >= num_nodes) {
      throw std::runtime_error("Invalid vertex index");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }

  timer.Start();
  bool result = IsDeadlocked(&graph);
  timer.Stop();
  return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "num_nodes", "edges"};
  generic_test_main(argc, argv, param_names, "deadlock_detection.tsv",
                    &HasCycleWrapper);
  return 0;
}
