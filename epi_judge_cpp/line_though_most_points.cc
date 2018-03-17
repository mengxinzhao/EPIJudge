#include <vector>
#include <unordered_map>
#include <cmath>
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::unordered_map;
using std::pair;
using std::make_pair;
using std::hash;

struct Point {
  int x, y;
};

// ax + by + c = 0
struct Line {
    float a;
    float b;
    float c;
    Line(float _a, float _b, float _c):a(_a),b(_b),c(_c) {
        //std::cout<<"line "<< _a <<", "<<_b<<", "<<_c<<std::endl;
    }
};

struct LineHash {
  size_t operator()(const Line &l) const {
      // Compute individual hash values for first,
      // second and third and combine them using XOR
      // and bit shifting:
      return ((hash<float>()(l.a) ^ (hash<float>()(l.b) << 1)) >> 1)^ (hash<int>()(l.c) << 1);;
  }
};

struct LineCompare
{
    bool operator()(const Line &l1, const Line &l2) const
    {
        return (l1.a == l2.a && l1.b == l2.b);
        
    }
};

// ax + by + c = 0
// iterate through all pairs of points and
// select the most voted a,b,c
int FindLineWithMostPoints(const vector<Point>& points) {
    unordered_map<Line,int,LineHash,LineCompare> votes;  // map <a,b> to number of votes
    
    float a = 0;
    float b = 0;
    float c = 0;
    vector<Point> dup;
    for (int i=0;i<points.size();i++) {
        for (int j=0; j<i;j++) {
            if (points[i].x!=points[j].x || points[i].y!=points[j].y) {
                if (points[i].x != points[j].x) {
                    //y = ax + c
                    //
                    a = (float(points[i].y) - float(points[j].y))/(float(points[i].x) - float(points[j].x));
                    b = -1;
                    c = points[j].y - a *points[j].x;
                } else {
                    b = 0;
                    a = 1;
                    c = -points[i].x ;
                }
                 votes[Line(a,b,c)]++;
            }else {
                // all lines passing this points gets one
                //std::cout<<points[i].x <<" "<<points[i].y<<std::endl;
                dup.push_back(points[i]);
            }
        }
    }
    for (auto &line: votes) {
        for (auto &p: dup) {
            //std::cout<<line.first.a<< ", "<<line.first.b<<", "<<line.first.c<<"," << line.second<<std::endl;
            if (line.first.a * p.x +line.first.b * p.y+ line.first.c == 0 ) {
                //std::cout<<"+1" << std::endl;
                line.second +=1;
            }
        }
    }
    
    int max = -1;
    for (auto &line: votes) {
        //std::cout<<line.first.a<< ", "<<line.first.b<<", "<<line.first.c<<"," << line.second<<std::endl;
        if (max < line.second)
            max = line.second;
    }
    // max = C(n,n-1)  n number of pairs in a line n^2- n - 2*max = 0
    // n=[1± sqrt(1+8*max)]/2. drop the negative one
    return (int) (1 + sqrt(1 + 8*max))/2;
}

template <>
struct SerializationTraits<Point> : UserSerTraits<Point, int, int> {};

bool operator==(const Point& lhs, const Point& rhs) {
  return std::tie(lhs.x, lhs.y) == std::tie(rhs.x, rhs.y);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"points"};
  generic_test_main(argc, argv, param_names, "line_though_most_points.tsv",
                    &FindLineWithMostPoints);
  return 0;
}
