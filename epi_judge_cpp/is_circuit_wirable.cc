#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <iostream>
#include <functional>
#include <queue>
#include "test_framework/test_timer.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::queue;
using std::hash;
using std::unordered_set;

struct GraphVertex {
  int d = -1;
  vector<GraphVertex*> edges;
};

struct PinPlacement {
    GraphVertex *vertex;
    bool left;
    PinPlacement (GraphVertex *_v, bool _left):vertex(_v),left(_left) {}
    bool operator == (const PinPlacement &p) const {
        return (vertex == p.vertex && left ==p.left);
    }
};

struct PinPlacementComapre {
    bool operator ()(const PinPlacement &p1, const PinPlacement &p2){
        return (p1.vertex == p2.vertex && p1.left ==p2.left);
    }
};

struct PinPlacementHasher{
    size_t operator()(const PinPlacement &pin) const {
        auto addr = reinterpret_cast<uintptr_t>(pin.vertex);
        // hash poiter.
        return addr ^ (1021 * pin.left );
    }
};

// this is a hard BFS traversal question
// a pair pin can be made to the spec when they are from BFS invoking u --> discovery v
// if there is a wire connection  between vertices both in u's adjacement list it is not feasible
// to place the pin.
bool IsAnyPlacementFeasible(vector<GraphVertex>* graph) {
    unordered_set<PinPlacement,PinPlacementHasher, PinPlacementComapre> placed;
    queue<PinPlacement>graph_q;
    graph_q.emplace(&(*graph)[0],true);
    placed.emplace(&(*graph)[0], true);
    int i=1;
    while (i< graph->size()) {
        while(!graph_q.empty()) {
            PinPlacement u = graph_q.front();
            graph_q.pop();
            for (GraphVertex * v: u.vertex->edges) {
                // both vertices are seen but there is an edge between. check the placement.
                // in order to have cross edge between left and right, it needs v->left= !u->left
                // if we find {v,u->left} in the placed set that shows the pin already placed
                // and can't satisfy the current request.
                if (placed.find({v,u.left }) != placed.end())
                    return false;
                else if (placed.find({v,!u.left}) == placed.end()) {
                    placed.emplace(v, !u.left);
                    graph_q.emplace(v, !u.left);
                }
            }
        }
        if (placed.find({&(*graph)[i], true})!= placed.end()
            || placed.find({&(*graph)[i], false })!= placed.end())
            i++;
        else {
            // this node is isolated doesn't matter where it is put.
            graph_q.emplace( &(*graph)[i], true);
            placed.emplace(&(*graph)[i], true);
            
        }
        
    }
    return true;
}

struct Edge {
  int from;
  int to;
};

template <>
struct SerializationTraits<Edge> : UserSerTraits<Edge, int, int> {};

bool IsAnyPlacementFeasibleWrapper(TestTimer& timer, int k,
                                   const vector<Edge>& edges) {
  vector<GraphVertex> graph;
  if (k <= 0) {
    throw std::runtime_error("Invalid k value");
  }
  graph.reserve(k);

  for (int i = 0; i < k; i++) {
    graph.push_back(GraphVertex{});
  }

  for (auto& e : edges) {
    if (e.from < 0 || e.from >= k || e.to < 0 || e.to >= k) {
      throw std::runtime_error("Invalid vertex index");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }

  timer.Start();
  bool result = IsAnyPlacementFeasible(&graph);
  timer.Stop();
  return result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "k", "edges"};
  generic_test_main(argc, argv, param_names, "is_circuit_wirable.tsv",
                    &IsAnyPlacementFeasibleWrapper);
  return 0;
}
