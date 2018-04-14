#include <deque>
#include <vector>
#include <queue>
#include <iostream>

#include "test_framework/test_timer.h"

using std::deque;
using std::vector;
using std::queue;

struct Cell {
    int x;
    int y;
    Cell(int _x, int _y):x(_x),y(_y) {}
};
bool GoodChoice(const Cell &loc, bool color, vector<deque<bool>> &image) {
    if (loc.x < image.size() && loc.x >=0 && loc.y < image[loc.x].size() && loc.y >=0 && image[loc.x][loc.y]== color)
        return true;
    else
        return false;
}

// BFS travel to flip all connected cells
// O(N*M) //N image width, M image height
void FlipColor(int x, int y, vector<deque<bool>>* image_ptr) {
    bool color_to_flip = (*image_ptr)[x][y];
    queue<Cell> curr_q;
    curr_q.emplace(x,y);
    (*image_ptr)[x][y]= !color_to_flip; // flip also marked as visited
    while(!curr_q.empty()) {
        Cell curr = curr_q.front();
        //visit and flip the color
        (*image_ptr)[curr.x][curr.y] = !color_to_flip;
        curr_q.pop();
        
        vector<Cell> candidates = { {curr.x-1,curr.y},{curr.x+1,curr.y},{curr.x,curr.y+1},{curr.x,curr.y-1} };
        for (const auto &cand: candidates) {
            if (GoodChoice(cand, color_to_flip, *image_ptr)){
                curr_q.emplace(cand.x,cand.y);
            }
        }
    }
    return;
}

vector<vector<int>> FlipColorWrapper(TestTimer& timer, int x, int y,
                                     vector<vector<int>> image) {
  vector<deque<bool>> b;
  b.reserve(image.size());
  for (const vector<int>& row : image) {
    deque<bool> tmp;
    tmp.resize(row.size());
    for (int i = 0; i < row.size(); ++i) {
      tmp[i] = static_cast<bool>(row[i]);
    }
    b.push_back(tmp);
  }

  timer.Start();
  FlipColor(x, y, &b);
  timer.Stop();

  image.resize(b.size());

  for (int i = 0; i < image.size(); ++i) {
    image[i].resize(b.size());
    for (int j = 0; j < image[i].size(); ++j) {
      image[i][j] = b[i][j];
    }
  }
  return image;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "x", "y", "image"};
  generic_test_main(argc, argv, param_names, "painting.tsv", &FlipColorWrapper);
  return 0;
}
