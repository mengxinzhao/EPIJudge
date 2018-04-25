#include <vector>
#include <climits>
#include <iostream>
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::min;
using std::max;

struct HighwaySection {
  int x, y, distance;
};

// run Floyd-Warshall all-pair shortest  for the original H.
// For each proposal, exam the path that passes through either proposal's src or dest
// if that changes the shortest path from i->...src/dest...->j,it's a good proposal and
// we note down the improvement.
// The best one is the one that minimize the original all-pair shortest path the most
vector<vector<int>> construct_graph(const vector<HighwaySection>& H,int n) {
    vector<vector<int>> graph(n, vector<int>(n, INT_MAX));
    
    for (int i = 0; i < H.size();i++) {
        // bi-directional
        graph[H[i].x][H[i].y] = H[i].distance;
        graph[H[i].y][H[i].x] = H[i].distance;
    }
    return graph;
}

// return the shortest total path sum
void Floyd_Warshall(vector<vector<int>> &graph, vector<vector<int>> &paths, int n) {
    // init
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) {
            if (i==j)
                paths[i][j] = 0 ; // reach itself
            else if (graph[i][j] < INT_MAX) // direct reach
                paths[i][j] = graph[i][j];
        }

    for (int k=0; k<n;k++)
        for (int i=0;i <n;i++)
            for (int j=0; j <n;j++) {
                // shortest path from i to j via k is the min one chosen from
                // 1. path from i to j via k-1. k not in the path
                // 2. path from i to k and k to j through one of its internal node
                if (paths [i][k] != INT_MAX && paths[k][j]!= INT_MAX)
                    paths[i][j] = min (paths[i][j], paths[i][k]+ paths[k][j]);
            }
    return ;
}

// check shortest path that passes through proposal's src or dst
// because paths[src][dst] changs from +inf to a number we compare the existing shortest path
// path[i][j][optimal_k] with path[i][src][optimal_k] + distance src->dest + path[dest][j][optimal_k]
int check_proposal( int n, vector<vector<int>> &paths, const HighwaySection &p) {

    int total_imprv=0;
    for (int i=0; i<n;i++)
        for (int j=0; j<n;j++) {
            //  bi-directional
            int src_imprv = paths[i][j] - (paths[i][p.x] + p.distance + paths[p.y][j]) ;
            int dst_imprv = paths[i][j] - (paths[i][p.y] + p.distance + paths[p.x][j]);
            total_imprv += max(max(src_imprv, dst_imprv),0);

        }
    return total_imprv;
}
HighwaySection FindBestProposals(const vector<HighwaySection>& H,
                                 const vector<HighwaySection>& P, int n) {
    vector<vector<int>> graph = construct_graph(H,n);
    vector<vector<int>> paths(n, vector<int>(n, INT_MAX));
    Floyd_Warshall(graph, paths,n);
    int max_imprv = INT_MIN;
    HighwaySection best_p = {0,0,0};
    for (int i=0; i< P.size();i++){
        int imprv =check_proposal(n,paths,P[i]);
        if (max_imprv  < imprv) {
            max_imprv = imprv;
            best_p = P[i];
        }
    }
    return best_p;
}

template <>
struct SerializationTraits<HighwaySection>
    : UserSerTraits<HighwaySection, int, int, int> {};

bool operator==(const HighwaySection& lhs, const HighwaySection& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.distance == rhs.distance;
}

std::ostream& operator<<(std::ostream& out, const HighwaySection& hs) {
  return EpiPrint(out, std::make_tuple(hs.x, hs.y, hs.distance));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"H", "P", "n"};
  generic_test_main(argc, argv, param_names, "road_network.tsv",
                    &FindBestProposals);
  return 0;
}
