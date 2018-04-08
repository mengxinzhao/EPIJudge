#include <vector>
#include <algorithm>
#include <cstddef>
#include <queue>
#include <map>
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::priority_queue;
using std::sort;
using std::multiset;
using std::set;
using std::map;
using std::max;
using std::min;

struct Rectangle {
    int left, right, height;
    Rectangle(int _left,int _right, int _height):left(_left), right(_right),height(_height) {}
    bool operator < (const Rectangle &rhs) const {
        return (left<rhs.left || (left == rhs.left && right < rhs.right));
    }
};


typedef vector<Rectangle> Skyline;

// recursively merge the building contour of left buildings and  right buildings
Skyline merge_skyline(const vector<Rectangle> &buildings, int left,int right) {
    if (left >= right)
        return vector<Rectangle>({buildings[left]});
    
    int mid = left + (right - left)/2;
    Skyline skl_left = merge_skyline(buildings, left, mid);
    Skyline skl_right = merge_skyline(buildings, mid+1, right);
    Skyline merged;
    
    std::cout<<"left: " <<std::endl;
    for (int i= 0; i< skl_left.size();i++)
        std::cout<<"("<<skl_left[i].left<<", "<<skl_left[i].right<<", "<< skl_left[i].height<<") ";
    std::cout<<std::endl;
    std::cout<<"right: " <<std::endl;
    for (int i= 0; i< skl_right.size();i++)
        std::cout<<"("<<skl_right[i].left<<", "<<skl_right[i].right<<", "<< skl_right[i].height<<") ";
    std::cout<<std::endl;
    
    //left and right are not connected
    if (skl_left[skl_left.size()-1].right < skl_right[0].left) {
        merged.insert(merged.begin(),skl_left.begin(),skl_left.end());
        merged.emplace_back(skl_left[skl_left.size()-1].right+1,skl_right[0].left-1,0);
        merged.insert(merged.end(),skl_right.begin(),skl_right.end());

        for (int i= 0; i< merged.size();i++)
            std::cout<<"merged: " <<merged[i].left<<", "<<merged[i].right<<", "<< merged[i].height<<std::endl;
        return merged;
    }
    
    int i=0;
    // merge left till the last rectange. The last one needs to be merged with right ones
    merged.insert(merged.begin(),skl_left.begin(), std::prev(skl_left.end()));
    Rectangle candidate = skl_left[skl_left.size()-1];
    // take care of overlapping areas
    while(i < skl_right.size()  && candidate.right > skl_right[i].right) {
        if (candidate.height < skl_right[i].height ) {
            merged.emplace_back(candidate.left,skl_right[i].left,candidate.height);
            merged.push_back(skl_right[i]);
            candidate.left = skl_right[i].right;
        }
        i++;
    }
    //
    if (i>=skl_right.size()){
        merged.push_back(candidate);
    }
    else {
        if (candidate.height > skl_right[i].height) {
            merged.push_back(candidate);
            merged.emplace_back(candidate.right, skl_right[i].right, skl_right[i].height);
        }else if (candidate.height == skl_right[i].height){
            merged.emplace_back(candidate.left,skl_right[i].right,skl_right[i].height);
        }else {
            merged.emplace_back(candidate.left,skl_right[i].left,candidate.height);
            merged.push_back(skl_right[i]);
        }
        // merge right
        i++;
        if (i<skl_right.size())
            merged.insert(merged.end(),skl_right.begin()+i,skl_right.end());
    }
    for (int i= 0; i< merged.size();i++)
        std::cout<<"merged: " <<merged[i].left<<", "<<merged[i].right<<", "<< merged[i].height<<std::endl;
    
    return merged;
}


Skyline ComputeSkyline(const vector<Rectangle>& buildings) {
    vector<Rectangle> blds = buildings;
    sort(blds.begin(), blds.end());
    for (int i=0;i < blds.size();i++)
        std::cout<<"[ "<<blds[i].left<<", "<<blds[i].right<<", "<< blds[i].height<<"], ";
    std::cout<<std::endl;
    Skyline merged = merge_skyline(blds,0,blds.size()-1);
    return merged;
}


struct point {
    int x;
    int y;
    bool end;
    point(int _x, int _y, bool _end):x(_x), y(_y),end(_end) {}
    bool operator < ( const point &rhs) const {
        // sort by x
        if (x < rhs.x)
            return true;
        else if (x == rhs.x) {
            if (end == false && rhs.end == true)
                // same x the start point is put first
                 return true;
            // same end point the smaller y is put first
            else if (end == true && rhs.end == true && y < rhs.y)
                return true;
            // same start point. the bigger y is put first
            else if (end == false && rhs.end == false && y > rhs.y )
                return true;
            else
                return false;
        }
        else
            return false;
    }
};

struct Compare {
    bool operator() (const point &one, const point &two ){
        return (one.y > two.y );
    }
};


bool isHeightTracked( set<point, Compare> &contour, int height ){
    for (auto & e: contour) {
        if (e.y == height)
            return true;
    }
    return false;
}

void deleteHeight(set<point, Compare> &contour, map<int,int> &height_map, int height) {
    for (auto & iter: contour) {
        if (iter.y == height ) {
            if (height_map[height] == 1) {
                //std::cout<<"delete: " <<iter.x << " "<<iter.y << std::endl;
                contour.erase(iter);
                height_map.erase(height);
                break;
            }
            else
                height_map[height]--;
        }
    }
}

Skyline ComputeSkyline2(const vector<Rectangle > & buildings) {
    vector<point> points;
    
    for (const auto &e: buildings) {
        points.emplace_back(e.left, e.height,false);
        points.emplace_back(e.right,e.height,true);
    }
    // sort the points by left
    sort(points.begin(), points.end());

    vector<point> merged;
    set<point, Compare> contour; // track the current contour point. the biggest one at the top
    map<int,int> height_map;
    contour.emplace(points[0].x,0,false);
    
    for (int i=0; i< points.size();i++) {
        int curr_height = contour.begin()->y;
        //std::cout<<"point: " << points[i].x << " "<<points[i].y<< std::endl;
        // the height is not tracked yet and after inserting it, it
        // becomes the new contour height. add this point
        if (isHeightTracked(contour,points[i].y) == false) {
            contour.emplace(points[i]);
            height_map[points[i].y]++;
            if (contour.begin()->y > curr_height) {
                merged.emplace_back(points[i].x,curr_height,false);
                merged.push_back(points[i]);
            }

        }
        else  {
            if (points[i].end == false ) {
                // already a same height start in the set
                //contour.emplace(points[i]);
                height_map[points[i].y]++;
            }else {
                // if delete a point in the contour causes the contour change
                // add this point

                deleteHeight(contour,height_map,points[i].y);
                if (!contour.empty() &&  contour.begin()->y != curr_height) {
                    merged.push_back(points[i]);
                    merged.emplace_back(points[i].x,contour.begin()->y,false);
                }
                else if (contour.empty()) {
                    // when we have empty space bewteen buildings
                    merged.push_back(points[i]);
                    merged.emplace_back(points[i].x,0,false);
                }
            }
        }
        
    }
    // we have got  the merged points. now stitch together
    Skyline merged_skl;
    for (int i=0; i < merged.size()-1;) {
        int left = merged[i].x;
        //std::cout<<merged[i].x<<","<<merged[i].y<< std::endl;
        while (left == merged[i].x){
            i++;
        }
        merged_skl.emplace_back(left,merged[i].x,merged[i].y);
        i++;
    }

    return merged_skl;

}

bool operator==(const Rectangle& a, const Rectangle& b) {
  return a.left == b.left && a.right == b.right && a.height == b.height;
}

template <>
struct SerializationTraits<Rectangle>
    : UserSerTraits<Rectangle, int, int, int> {};

std::ostream& operator<<(std::ostream& out, const Rectangle& r) {
  return EpiPrint(out, std::make_tuple(r.left, r.right, r.height));
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"buildings"};
  generic_test_main(argc, argv, param_names, "drawing_skyline.tsv",
                    &ComputeSkyline2);
  return 0;
}
