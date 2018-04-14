#include <stdexcept>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include "test_framework/test_timer.h"

using std::string;
using std::vector;
using std::set;

struct Cell {
    int y;
    int x;
    Cell(int _y, int _x):y(_y),x(_x){}
};
struct Compare
{
    bool operator()(const Cell& lhs, const Cell& rhs)
    {
        return (lhs.x < rhs.x || ((lhs.x == rhs.x) && (lhs.y<rhs.y)));
    }
    
};

bool IsFeasible(vector<vector<char>> &board,set<Cell,Compare> &cells_to_visit,Cell cand) {
    return (cand.y>= 0 && cand.y < board.size() && cand.x>=0
            && cand.x<board[cand.y].size() && board[cand.y][cand.x] =='W'
            && cells_to_visit.find(cand)!=cells_to_visit.end());
}

void DFS(vector<vector<char>> &board,set<Cell,Compare> &cells_to_visit,
         Cell current,vector<Cell> &region) {
    cells_to_visit.erase(current);
    region.push_back(current);
    vector<Cell>candidates = {{current.y+1, current.x}, {current.y-1,current.x}, {current.y, current.x+1}, {current.y,current.x-1}};
    
    for (auto &cand: candidates) {
        if (IsFeasible(board,cells_to_visit, cand) ) {
            DFS( board, cells_to_visit, cand,region);
        }
    }
    return;
}

void FillSurroundedRegions(vector<vector<char>>* board_ptr) {
    set<Cell,Compare> cells_to_visit;
    vector<Cell> white_region;
    vector<vector<Cell>> white_regions;
    for (size_t i=0; i< (*board_ptr).size();i++) {
        for (size_t j=0; j <(*board_ptr)[i].size();j++) {
            if ((*board_ptr)[i][j] == 'W'){
                cells_to_visit.emplace(i,j);
            }
        }
    }
    //DFS to find the white region
    // each call of DFS will discover all the nodes in the white connected region
    while(!cells_to_visit.empty()){
        auto  iter = cells_to_visit.begin();
        Cell current = *iter;
        white_region.clear();
        DFS(*board_ptr,cells_to_visit, current,white_region);
        if (!white_region.empty())
            white_regions.push_back(white_region);
    }
    
    // for each white regions
    // if there is one node at the boundary the region is connected to the boundary
    // if not the entire region will set to 'B'
    int width = (*board_ptr)[0].size();
    int height = board_ptr->size();
    for (size_t i=0; i< white_regions.size();i++) {
        bool outlet = false;
        for (size_t j=0; j< white_regions[i].size();j++) {
            Cell loc = white_regions[i][j];
            if ((loc.y ==0 || loc.y== height -1 || loc.x==0 || loc.x == width-1 )
                &&( *board_ptr )[loc.y][loc.x] == 'W') {
                outlet = true;
                break;
            }
        }
        if (!outlet) {
            //fill the region
            for (size_t j=0; j< white_regions[i].size();j++) {
                Cell loc = white_regions[i][j];
                ( *board_ptr )[loc.y][loc.x] = 'B';
            }
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
