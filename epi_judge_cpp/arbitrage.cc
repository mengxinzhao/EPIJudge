#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cmath>
#include <climits>
using std::vector;
using std::max;
using std::min;

// an edge represents rate exchange from u->v with weight= -log(rate)
// the problem converts to bellman-ford shortest path negative cycle detection
// u --> v --> w exchange sum = 1 dollar of u * rate(u->v) * rate(v->w)
// convert to -log(u --> v --> w exchange sum) = -log(rate u->v) - log (rate v->w)
// the shortest path of bellman-ford  under this construction equals to max of exchange rate result
// if there is arbitrag at w, there is a higher rate  w->u from w back  to u, meaning
// a negative cycle w->v with smaller weight -log(rate(w->u))


// path(i,v) min length of a s->v path with <=i edges i = [1, V-1]
// path (i,v) = min(path(i-1,v)  + argmin<w> (path(i-1,v)  - log_rate(w->v) )
// the graph is dense. running time O(n^3)
bool IsArbitrageExist(vector<vector<double>> graph) {
    int V = graph.size();
    vector<vector<double>> paths(graph.size(), vector<double>(graph.size(),INT_MAX));

    // fix source to be 0. calculate shortest path from 0 to all destinations
    paths[0][0] = 0.0 ;// -log(1.0);

     // without cycle the max edge number in a path is num_vertex-1
    for (int i = 1; i<=V-1;i++) {
        for (int v = 0; v< graph.size();v++) {
            for (int w =0; w < graph[v].size(); w++) {
                    paths[i][v] = min(paths[i][v],  min(paths[i-1][v], paths[i-1][w]- log(graph[w][v])));
            }
        }
    }
    // one more iteration, if path[i][v] becomes even smaller that is arbitrage due to negative cycles
    int min_length = V-1;
    for (int v = 0; v< graph.size();v++) {
        double temp_path_i_v =paths[min_length][v] ;
        for (int w =0; w < graph[v].size(); w++){
            temp_path_i_v = min(temp_path_i_v, min(paths[min_length][v], paths[min_length][w]- log(graph[w][v])));
        }
        if (temp_path_i_v != paths[min_length][v])
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
