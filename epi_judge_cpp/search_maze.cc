#include <istream>
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

#include "test_framework/test_failure_exception.h"
#include "test_framework/test_timer.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::pair;

typedef enum { WHITE, BLACK } Color;

struct Coordinate {
    bool operator==(const Coordinate& that) const {
        return x == that.x && y == that.y;
    }

    int x, y;
    Coordinate(int _x, int _y):x(_x),y(_y) {}
    
};

bool NextStep(vector<vector<Color>>maze, vector<vector<int>>&visited,vector<Coordinate> &path,Coordinate current, const Coordinate &end) {
    
    //std::cout<<"trying..."<<current.x << ", "<< current.y << std::endl;
    if (current == end) {
        return true;
    }
    //look at viable steps and make a choice
    vector<pair<int,int>> options = {{current.x, current.y+1}, {current.x, current.y-1},{current.x+1,current.y},{current.x-1,current.y} };
    for (auto &iter: options){
        int x = iter.first;
        int y = iter.second;
        // the test data requires maze[x][y] instead of usual matrix[row][col] convension
        //if (x>=0 && y>=0 && y<maze.size() &&   x < maze[y].size() && maze[y][x] == WHITE && !visited[y][x]){
        if (x>=0 && y>=0 && x<maze.size() &&   y < maze[x].size() && maze[x][y] == WHITE && !visited[x][y]){
            visited[x][y]= 1;
            if (NextStep(maze,visited,path,{x,y},end)) {
                path.emplace_back(x,y);
                return true;
            }
        }
    }
    return false;
}

vector<Coordinate> SearchMaze(vector<vector<Color>> maze, const Coordinate& s,
                              const Coordinate& e) {
    vector<Coordinate>path;
    vector<vector<int>>visited(maze.size(),vector<int>(maze[0].size(),0));
    if (NextStep(maze,visited,path,s,e))
        path.push_back(s);
    std::reverse(path.begin(), path.end());

    return path;
}

template <>
struct SerializationTraits<Color> : SerializationTraits<int> {
  using serialization_type = Color;

  static serialization_type Parse(const std::string& str) {
    return static_cast<serialization_type>(
        SerializationTraits<int>::Parse(str));
  }

  static serialization_type JsonParse(std::istream& in) {
    return static_cast<serialization_type>(
        SerializationTraits<int>::JsonParse(in));
  }
};

template <>
struct SerializationTraits<Coordinate> : UserSerTraits<Coordinate, int, int> {};

bool PathElementIsFeasible(const vector<vector<Color>>& maze,
                           const Coordinate& prev, const Coordinate& cur) {
  if (!(0 <= cur.x && cur.x < maze.size() && 0 <= cur.y &&
        cur.y < maze[cur.x].size() && maze[cur.x][cur.y] == WHITE)) {
    return false;
  }
  return cur == Coordinate{prev.x + 1, prev.y} ||
         cur == Coordinate{prev.x - 1, prev.y} ||
         cur == Coordinate{prev.x, prev.y + 1} ||
         cur == Coordinate{prev.x, prev.y - 1};
}

bool SearchMazeWrapper(TestTimer& timer, const vector<vector<Color>>& maze,
                       const Coordinate& s, const Coordinate& e) {
  vector<vector<Color>> copy = maze;

  timer.Start();
  auto path = SearchMaze(copy, s, e);
  timer.Stop();

  if (path.empty()) {
    return s == e;
  }

  if (!(path.front() == s) || !(path.back() == e)) {
    throw TestFailureException("Path doesn't lay between start and end points");
  }

  for (size_t i = 1; i < path.size(); i++) {
    if (!PathElementIsFeasible(maze, path[i - 1], path[i])) {
      throw TestFailureException("Path contains invalid segments");
    }
  }

  return true;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"timer", "maze", "s", "e"};
  generic_test_main(argc, argv, param_names, "search_maze.tsv",
                    &SearchMazeWrapper);
  return 0;
}
