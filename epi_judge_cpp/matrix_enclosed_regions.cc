#include <stdexcept>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <queue>
#include <cassert>
#include <functional>
#include <cassert>
#include "test_framework/test_timer.h"

using std::string;
using std::vector;
using std::queue;
struct Cell {
    int y;
    int x;
    Cell(int _y, int _x):y(_y),x(_x){}
    bool operator==(const Cell &rhs) {
        return y == rhs.y && x == rhs.x;
    }
    bool operator!= (const Cell&rhs) {
        return !( *this == rhs);
    }
};

bool Is_feasible(vector<vector<char>> &board,vector<vector<int>> &visited,Cell cand) {
    return (cand.y>= 0 && cand.y < board.size() && cand.x>=0
            && cand.x<board[cand.y].size() && board[cand.y][cand.x] =='W'
            && visited[cand.y][cand.x] == false);
}


bool is_at_boundary(Cell loc, vector<vector<char>> &grid) {
    return ((loc.y ==0 || loc.y== grid.size() -1 || loc.x==0 || loc.x == grid[0].size()-1 ));
}

// DFS + union to get the connected component
// the problem is the stack might run too deep and cause stack overflow
void DFS(Cell loc, Cell parent,vector<vector<char>> &grid,vector<vector<Cell>> &A, vector<vector<int>> &visited) {
    visited[loc.y][loc.x] = true;

    if (is_at_boundary(loc, grid)&& is_at_boundary(parent,grid)==false &&  grid[loc.y][loc.x] == 'W') {
        A[parent.y][parent.x] = loc;
        A[loc.y][loc.x] = loc;
    }else {
        A[loc.y][loc.x] = A[parent.y][parent.x];
    }
    
    vector<Cell>candidates = {{loc.y+1, loc.x}, {loc.y-1,loc.x}, {loc.y, loc.x+1}, {loc.y,loc.x-1}};
    for (auto &cand: candidates) {
        if (Is_feasible(grid,visited, cand) ) {
            DFS(cand,parent, grid, A, visited);
        }
    }
}

// BFS + union to get the connected component
// the parent pointer is set to be the initial node that invokes the BFS
// and later changed to the 1st boundary cell in the BFS discovery

void BFS(Cell loc, Cell parent,vector<vector<char>> &grid,vector<vector<Cell>> &A, vector<vector<int>> &visited) {
    
    queue<Cell> graph_q;
    graph_q.push(loc);
    visited[loc.y][loc.x] = true;
    
    while(!graph_q.empty()) {
        Cell curr = graph_q.front();
        if (is_at_boundary(curr, grid)&& is_at_boundary(parent,grid)==false &&  grid[curr.y][curr.x] == 'W') {
            // change the parent pointer of the group
            A[parent.y][parent.x] = curr;
            A[curr.y][curr.x] = curr;
            parent = curr;
        }else {
            A[curr.y][curr.x] = A[parent.y][parent.x];
        }
        
        graph_q.pop();
        
        vector<Cell>candidates = {{curr.y+1, curr.x}, {curr.y-1,curr.x}, {curr.y, curr.x+1}, {curr.y,curr.x-1}};
        
        for (auto cand: candidates) {
            if (Is_feasible(grid,visited, cand) ) {
                visited[cand.y][cand.x] = true;
                graph_q.push(cand);
            }
        }
    }
}


void FillSurroundedRegions(vector<vector<char>>* board_ptr) {
    vector<vector<char>> &board = *board_ptr;
    vector<vector<Cell>>A(board.size(),vector<Cell>(board[0].size(),{-1,-1}) );
    vector<vector<int>>visited(A.size(),vector<int>(A[0].size(),false) );

    for (int i=0; i< board_ptr->size();i++)
        for (int j=0; j< board[i].size();j++)
            if (board[i][j] == 'W' && visited[i][j] == false){
                A[i][j] = {i,j};
                BFS({i,j},{i,j},board,A,visited);
            }
    
    Cell black = {-1,-1};
    for (int i=0; i< A.size();i++)
        for (int j=0; j< A[i].size();j++) {
            if (A[i][j]!= black ) {
                // check if it has a parent at the boundary or itself is located at the boundary
                // at most have 2 loops in the while.
                // for the nodes that are discovered before the 1st boundary node discovered,their parent pointer
                // is set to the 1st node invoking the BFS.For the nodes that are discovered after 1st boundary node
                // discoverd A[i][j] directly points to boundary node.
                // worst case :2 hops to the boundary node. one hop to a node a enclosed in the matrix that is invoking BSF, second hop from a to the boundary node
                int y = i;
                int x = j;
                Cell root = {i,j};
                while(A[y][x]!= root ) {
                    root = A[y][x];
                    y  = root.y;
                    x =  root.x;
                }
                if (is_at_boundary({y,x},board) == false)
                    board[i][j]= 'B';
            }
        }
     return;
}


vector<vector<string>> FillSurroundedRegionsWrapper(
    TestTimer& timer, vector<vector<string>> board) {
  vector<vector<char>> char_vector;
  char_vector.resize(board.size());
  for (int i = 0; i < board.size(); i++) {
    for (const string& s : board[i]) {
      if (s.size() != 1) {
        throw std::runtime_error("String size is not 1");
      }
      char_vector[i].push_back(s[0]);
    }
  }

  timer.Start();
  FillSurroundedRegions(&char_vector);
  timer.Stop();

  board.clear();
  board.resize(char_vector.size(), {});
  for (int i = 0; i < board.size(); i++) {
    for (char c : char_vector[i]) {
      board[i].emplace_back(1, c);
    }
  }

  return board;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "board"};
  generic_test_main(argc, argv, param_names, "matrix_enclosed_regions.tsv",
                    &FillSurroundedRegionsWrapper);
  return 0;
}
