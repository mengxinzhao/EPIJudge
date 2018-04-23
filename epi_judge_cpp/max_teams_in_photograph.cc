#include <stdexcept>
#include <vector>
#include <algorithm>
#include "test_framework/test_timer.h"
#include "test_framework/test_utils_serialization_traits.h"
#include <climits>
#include <iostream>
using std::vector;
using std::min;
using std::max;
struct GraphVertex {
  vector<GraphVertex*> edges;
  // Set max_distance = 0 to indicate unvisited vertex.
  int max_distance = 0;
};

// topological sort and return max_distance to be the order number
// consider team 0 ... team k
// start from team 0 [0], DFS to team1[0]...team i[0] till either all teams are visited or
// the condition front height < back height not met. the last visited team gets 1..
// back to the team 0, the max_distance = k. the source node has the highest order number

int DFS (GraphVertex * u) {
    // mark u visited
    u->max_distance=1;
    
    for (GraphVertex * v: u->edges) {
        // if v not visitd
        if (v->max_distance == 0) {
            u->max_distance = max(u->max_distance, 1+DFS(v));
        }else
            // back edge
            u->max_distance = max(u->max_distance,v->max_distance+1);
    }
    return u->max_distance;
}

int FindLargestNumberTeams(vector<GraphVertex>* graph) {
    vector<GraphVertex > g = *graph;
    int max_team = 1;
    for (size_t i=0; i < g.size();i++){
        if (g[i].max_distance == 0) {
            int depth= DFS(&g[i]);
            max_team = max(g[i].max_distance, max_team);
        }
    }
  return max_team;
}

struct Edge {
  int from;
  int to;
};

template <>
struct SerializationTraits<Edge> : UserSerTraits<Edge, int, int> {};

int FindLargestNumberTeamsWrapper(TestTimer& timer, int k,
                                  const vector<Edge>& edges) {
  if (k <= 0) {
    throw std::runtime_error("Invalid k value");
  }

  vector<GraphVertex> graph(k, GraphVertex{});

  for (const Edge& e : edges) {
    if (e.from < 0 || e.from >= k || e.to < 0 || e.to >= k) {
      throw std::runtime_error("Invalid vertex index");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }

  timer.Start();
  int result = FindLargestNumberTeams(&graph);
  timer.Stop();
  return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "k", "edges"};
  generic_test_main(argc, argv, param_names, "max_teams_in_photograph.tsv",
                    &FindLargestNumberTeamsWrapper);
  return 0;
}
