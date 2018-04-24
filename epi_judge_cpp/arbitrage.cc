#include <vector>
#include <algorithm>
#include <utility>
using std::vector;
using std::max;
using std::pair;


#include <iostream>
bool DFS(vector<vector<double>> &graph, vector<double> & weights, int u) {
    weights[u] = 1.0;
    //std::cout<<"checking u: "<< u<<std::endl;
    for (int v =0; v < graph[u].size();v++){
        if (v!=u){
            if (weights[v] == 0.0) {
                if (DFS(graph, weights,v)== false) {
                    weights[u] = max(weights[u], weights[v] * 1/ graph[u][v]);
                    //std::cout<<"updating u: "<< u <<"=" << weights[u] << "from v: "<<v<<", "<<graph[u][v]<<std::endl;
                }
                else
                    return true;
            }else {
                // (v visited before and form a cycle)
                if (weights[u]* graph[u][v] > weights[v])
                    return true;
            }
        }
    }
    return false;
}

bool IsArbitrageExist(vector<vector<double>> graph) {
    vector<double>weights (graph.size(),0.0);
    for (int u=0; u< graph.size();u++){
        if (weights[u] == 0.0  && DFS(graph,weights,u))
            return true;
    }
  return false;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"graph"};
  generic_test_main(argc, argv, param_names, "arbitrage.tsv",
                    &IsArbitrageExist);
  return 0;
}
