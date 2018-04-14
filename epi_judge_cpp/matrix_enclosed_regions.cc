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


bool CanReachBoundary(vector<vector<char>> &board,set<Cell,Compare> &cells_to_visit,Cell cand) {
    return (cand.y>= 0 && cand.y < board.size() && cand.x>=0
            && cand.x<board[cand.y].size() && board[cand.y][cand.x] =='W'
            && cells_to_visit.find(cand)!=cells_to_visit.end());
}

bool AtBoundary(vector<vector<char>> &board,Cell cand) {
    return (((cand.y==0 || cand.y==board.size()-1 ) &&(cand.x >=0 && cand.x < board[cand.y].size()))
            ||(cand.y >=0  && cand.y < board.size() && ( cand.x==0 || cand.x == board[cand.y].size()-1)));
}

bool ReachNext(vector<vector<char>> &board, set<Cell,Compare> &cells_to_visit, Cell current) {
    // mark as visited and also black
    cells_to_visit.erase(current);
    
    if (AtBoundary(board, current)) {
        //std::cout<<"visiting boudary..."<<current.x<<","<<current.y<<std::endl;
        if (board[current.y][current.x] == 'W')
            return true;
        else
            return false;
    }
    
    vector<Cell>candidates = {{current.x+1, current.y}, {current.x-1,current.y}, {current.x, current.y+1}, {current.x,current.y-1}};
    
    for (auto &cand: candidates) {
        if (CanReachBoundary(board,cells_to_visit, cand) ) {
           if (!ReachNext(board,cells_to_visit,cand)){
                // fill black
                board[cand.y][cand.x] = 'B';
           }
            else
                return true;
        }
    }
    // should never go here
    return false;
}


void FillSurroundedRegions(vector<vector<char>>* board_ptr) {
    set<Cell,Compare> cells_to_visit;
    //mark all white cell as not visited yet and only start from the white region
    for (size_t i=0; i< (*board_ptr).size();i++) {
        for (size_t j=0; j <(*board_ptr)[i].size();j++) {
            if ((*board_ptr)[i][j] == 'W'){
                cells_to_visit.emplace(i,j);
            }
        }
    }
    //
    while(!cells_to_visit.empty()){
        auto  iter = cells_to_visit.begin();
        Cell current = *iter;
        //std::cout<<"visiting..."<<current.x<<","<<current.y<<std::endl;
        if (!ReachNext(*board_ptr, cells_to_visit, current))
            (*board_ptr)[current.y][current.x] = 'B';
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
