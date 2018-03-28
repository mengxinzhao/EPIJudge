#include <vector>
#include <algorithm>
#include <cstddef>
#include "test_framework/test_utils_serialization_traits.h"

using std::vector;
using std::sort;
using std::max;
using std::min;

struct Rectangle {
    int left, right, height;
    Rectangle(int _left,int _right, int _height):left(_left), right(_right),height(_height) {}
    bool operator < (const Rectangle &rhs) const {
        return left<rhs.left;
    }
};

struct Compare {
    bool operator() (const Rectangle &lh, const Rectangle &rh) const {
        return lh.height < rh.height;
    }
};

typedef vector<Rectangle> Skyline;

// recursively merge the building contour of building left and building right
Skyline merge(const vector<Rectangle> &buildings, int left,int right) {
    if (left >= right)
        return vector<Rectangle>({buildings[left]});
    
    int mid = left + (right - left)/2;
    Skyline skl_left = merge(buildings, left, mid);
    Skyline skl_right = merge(buildings, mid+1, right);
    Skyline merged;
    int i = 0, j=0;
    // merge to union areas. At this point, all rectangles are already sorted by their left coordinates.
    while (i <skl_left.size() && j < skl_right.size()) {
//         std::cout<<"left: " <<skl_left[i].left<<", "<<skl_left[i].right<<", "<< skl_left[i].height<<std::endl;
//         std::cout<<"right: " <<skl_right[j].left<<", "<<skl_right[j].right<<", "<< skl_right[j].height<<std::endl;
        if (skl_left[i].right < skl_right[j].left){
            merged.push_back(skl_left[i]);
            i++;
        }
        // left rectangle x range doesn't over all right rectangle
        else if (skl_left[i].right > skl_right[j].left && skl_left[i].right < skl_right[j].right ){
            if (skl_left[i].height >skl_right[j].height) {
                merged.emplace_back(skl_left[i].left,skl_left[i].right, skl_left[i].height);
                merged.emplace_back(skl_left[i].right,skl_right[j].right, skl_right[j].height);
            } else if (skl_left[i].height ==skl_right[j].height) {
                merged.emplace_back(skl_left[i].left,skl_right[j].right, skl_left[i].height);
            }else {
                merged.emplace_back(skl_left[i].left,skl_right[j].left, skl_left[i].height);
                merged.emplace_back(skl_right[j].left,skl_right[j].right, skl_right[j].height);
            }
            i++;
            j++;
        }else {
            if (skl_left[i].height > skl_right[j].height)
                merged.emplace_back(skl_left[i].left,skl_left[i].right, skl_left[i].height);
            else if  (skl_left[i].height ==skl_right[j].height) {
                merged.emplace_back(skl_left[i].left,skl_left[i].right, skl_left[i].height);
            }else {
                merged.emplace_back(skl_left[i].left,skl_right[j].left, skl_left[i].height);
                merged.emplace_back(skl_right[j].left,skl_right[j].right, skl_right[j].height);
                merged.emplace_back(skl_right[j].right,skl_left[i].right, skl_left[i].height);
            }
            j++;
        }
    }
    if (i >=skl_left.size() && j< skl_right.size()) {
        merged.emplace_back(skl_left[skl_left.size()-1].right+1,skl_right[j].left-1, 0);
        while (j < skl_right.size()){
            merged.push_back(skl_right[j]);
            j++;
        }
    }
//    if (i <  skl_left.size() && j>=skl_right.size()) {
//        while (i < skl_left.size()) {
//            merged.push_back(skl_left[i]);
//            i++;
//        }
//    }

    return merged;
}

Skyline ComputeSkyline(const vector<Rectangle>& buildings) {
    vector<Rectangle> blds = buildings;
    sort(blds.begin(), blds.end());
    for (int i=0;i < blds.size();i++)
        std::cout<<"[ "<<blds[i].left<<", "<<blds[i].right<<", "<< blds[i].height<<"], ";
    std::cout<<std::endl;
    Skyline merged = merge(blds,0,blds.size()-1);
    return merged;
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
                    &ComputeSkyline);
  return 0;
}
