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
//using std::pair;

struct GraphVertex {
  int label;
  vector<GraphVertex*> edges;
    GraphVertex(int _label) : label(_label),edges({}) {}
//    GraphVertex(GraphVertex *lh) {
//      if (lh!= nullptr) {
//          label = lh->label;
//          for (auto &iter: lh->edges) {
//              edges.emplace_back(iter->label);
//          }
//      }
//  }
};

struct pair {
    GraphVertex *orig;
    GraphVertex *cloned;
    pair(GraphVertex *_org, GraphVertex *_cloned):orig(_org),cloned(_cloned){}
};

// BFS fashion to clone vertex and its vertexes reachable
GraphVertex* CloneGraph(GraphVertex* graph) {
    set<GraphVertex *> visited;
    queue<pair> clone_q;
    
    GraphVertex *cloned_root = new GraphVertex(graph->label);
    clone_q.emplace(graph,cloned_root);

    while(!clone_q.empty()) {
        pair  orig_cloned = clone_q.front();
        clone_q.pop();
        if (visited.find(orig_cloned.orig) == visited.end()) {
            visited.insert(orig_cloned.orig);
            //std::cout<<"copying vertex: "<< orig_cloned.cloned->label<<std::endl;
            for(auto &to_v: orig_cloned.orig->edges) {
                // a new node discovered. create it and add the edge to the cloned  edges
                GraphVertex *cloned_root = nullptr;
                //std::cout<<"copying edge "<<orig_cloned.orig->label<<"->"<< to_v->label<<std::endl;
                auto v_iter = visited.find(to_v);
                if (v_iter==visited.end()){
                    cloned_root = new GraphVertex(to_v->label);
                    //std::cout<<"enqueue: "<<to_v->label<<std::endl;
                    clone_q.emplace(to_v, cloned_root);    // insert the new node pair v, cloned_v
                }else {
                    cloned_root = *v_iter;
                }
                orig_cloned.cloned->edges.push_back(cloned_root); // add the edge
            }
            
        }
    }
    
  return cloned_root;
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
      throw TestFailureException("Invalid vertex label");
    }
    vector<int> label1 = CopyLabels(vertex->edges),
                label2 = CopyLabels(graph[vertex->label].edges);
    sort(begin(label1), end(label1)), sort(begin(label2), end(label2));

    if (label1 != label2) {
      throw TestFailureException("Invalid vertex label");
    }
    for (GraphVertex* e : vertex->edges) {
      if (!vertex_set.count(e)) {
        vertex_set.emplace(e);
        q.emplace(e);
      }
    }
  }
  for (auto& v : vertex_set) {
    delete v;
  }
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
      throw std::runtime_error("Invalid vertex index");
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
