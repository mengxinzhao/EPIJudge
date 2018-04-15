#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>
#include <set>
#include <queue>
#include <iostream>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::queue;
using std::unordered_set;
using std::set;
using std::vector;

struct GraphVertex {
  int label;
  vector<GraphVertex*> edges;
  GraphVertex(int _label) : label(_label),edges({}) {}
};

// DFS  clone vertex and its vertexes reachable
// This would ensure that a sink node gets cloned after all
// its predecessor nodes are cloned first. This would eliminate double cloning a sink
// when there are multiple source nodes pointing to it
GraphVertex* CloneVertex(GraphVertex* graph, set<GraphVertex*> &visited) {
    
    GraphVertex *cloned_u = new GraphVertex(graph->label);
    visited.insert(graph);
    for (auto &to_v: graph->edges) {
        auto iter = visited.find(to_v);
        if (iter==visited.end()){
            GraphVertex *cloned_v = CloneVertex(to_v, visited);
            cloned_u->edges.push_back(cloned_v);
        }else {
            cloned_u->edges.push_back(*iter);
        }
    }
    
    return cloned_u;
}

void DeleteVertex(GraphVertex *graph,set<GraphVertex*> &deleted) {
    deleted.insert(graph);
    while(!graph->edges.empty()){
        GraphVertex *to_v = graph->edges.back();
        auto iter = deleted.find(to_v);
        if (iter == deleted.end()){
            // delete the vertex first
            DeleteVertex(to_v,deleted);
        }
        graph->edges.pop_back();

    }
    if (deleted.find(graph) == deleted.end()) {
        // might have been deleted already when this node is a source node to other sinks
        // along the path
        delete graph;
    }
}

void DeleteGraph(GraphVertex *entrance) {
    set<GraphVertex *> deleted;
    return DeleteVertex(entrance, deleted);
}
GraphVertex* CloneGraph(GraphVertex* graph) {
    set<GraphVertex *> visited;
    return CloneVertex(graph, visited);
}


vector<int> CopyLabels(const vector<GraphVertex*>& edges) {
  vector<int> labels;
  transform(begin(edges), end(edges), back_inserter(labels),
            [](const auto& e) { return e->label; });
  return labels;
}

void CheckAndDeallocateGraph(GraphVertex* node,
                             const vector<GraphVertex>& graph) {
  if (node == &graph[0]) {
    throw TestFailureException("Graph was not copied");
  }

  unordered_set<GraphVertex*> vertex_set;
  queue<GraphVertex*> q;
  q.emplace(node);
  vertex_set.emplace(node);
  while (!q.empty()) {
    auto vertex = q.front();
    q.pop();
    if (vertex->label > graph.size()) {
      throw TestFailureException("Invalid vertex label1");
    }
    vector<int> label1 = CopyLabels(vertex->edges),
                label2 = CopyLabels(graph[vertex->label].edges);
    sort(begin(label1), end(label1)), sort(begin(label2), end(label2));
      
    if (label1 != label2) {
      throw TestFailureException("Invalid vertex label2");
    }
    for (GraphVertex* e : vertex->edges) {
      if (!vertex_set.count(e)) {
        vertex_set.emplace(e);
        q.emplace(e);
      }
    }
  }

    GraphVertex *v = *vertex_set.begin();
    DeleteGraph(v);
}

struct Edge {
  int from;
  int to;
};

template <>
struct SerializationTraits<Edge> : UserSerTraits<Edge, int, int> {};

void CloneGraphTest(int k, const vector<Edge>& edges) {
  vector<GraphVertex> graph;
  if (k <= 0) {
    throw std::runtime_error("Invalid k value");
  }
  graph.reserve(k);

  for (int i = 0; i < k; i++) {
    graph.push_back(GraphVertex{i});
  }

  for (const Edge& e : edges) {
    if (e.from < 0 || e.from >= k || e.to < 0 || e.to >= k) {
      throw std::runtime_error("Invalid vertex index3");
    }
    graph[e.from].edges.push_back(&graph[e.to]);
  }
  GraphVertex* result = CloneGraph(&graph[0]);
  CheckAndDeallocateGraph(result, graph);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"k", "edges"};
  generic_test_main(argc, argv, param_names, "graph_clone.tsv",
                    &CloneGraphTest);
  return 0;
}
