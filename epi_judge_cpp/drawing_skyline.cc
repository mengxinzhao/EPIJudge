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
        return (left<rhs.left || (left == rhs.left && right < rhs.right));
    }
};


typedef vector<Rectangle> Skyline;

// recursively merge the building contour of building left and building right
Skyline merge_skyline(const vector<Rectangle> &buildings, int left,int right) {
    if (left == right)
        return vector<Rectangle>({buildings[left]});
    
    int mid = left + (right - left)/2;
    Skyline skl_left = merge_skyline(buildings, left, mid);
    Skyline skl_right = merge_skyline(buildings, mid+1, right);
    Skyline merged;
    
//    std::cout<<"left: " <<std::endl;
//    for (int i= 0; i< skl_left.size();i++)
//        std::cout<<"("<<skl_left[i].left<<", "<<skl_left[i].right<<", "<< skl_left[i].height<<") ";
//    std::cout<<std::endl;
//    std::cout<<"right: " <<std::endl;
//    for (int i= 0; i< skl_right.size();i++)
//        std::cout<<"("<<skl_right[i].left<<", "<<skl_right[i].right<<", "<< skl_right[i].height<<") ";
//    std::cout<<std::endl;
    
    //left and right are not connected
    if (skl_left[skl_left.size()-1].right < skl_right[0].left) {
        merged.insert(merged.begin(),skl_left.begin(),skl_left.end());
        merged.emplace_back(skl_left[skl_left.size()-1].right+1,skl_right[0].left-1,0);
        merged.insert(merged.end(),skl_right.begin(),skl_right.end());

//        for (int i= 0; i< merged.size();i++)
//            std::cout<<"merged: " <<merged[i].left<<", "<<merged[i].right<<", "<< merged[i].height<<std::endl;
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
//    for (int i= 0; i< merged.size();i++)
//        std::cout<<"merged: " <<merged[i].left<<", "<<merged[i].right<<", "<< merged[i].height<<std::endl;
    
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
