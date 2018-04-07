#include <vector>
#include <queue>
#include <algorithm>

using std::vector;
using std::priority_queue;
using std::min;

struct unit {
    int index;
    int height;
    unit(int _index, int _height) : index(_index), height(_height) {}
    bool operator <(const unit &rhs) const {
        // make sure the unit that has the same height but smaller index appears bigger in the priority queue
        return ((height < rhs.height )|| ((height == rhs.height) && (index > rhs.index)));
    }
};

struct Compare {
    bool operator()(const unit &one, const unit &two) {
        return (one < two);
    }
};

// use a max heap e to track the height left walls
// if a[j] > max_heap.top() and j > i
// all element between i and j are popped and caculated the trapped amount
// if there is no a[j] > max_heap.top()
// pop max = max_heap.top()  and compute the water trapped between max and max_heap.top()
// O(NlogN)
// each unit get visited at most 2 times and priority queue update takes log(N) time
int CalculateTrappingWater(const vector<int>& heights) {
    // don't bother to calculate
    if (heights.size() <=2)
        return 0;
    
    priority_queue<unit, vector<unit>,Compare > walls;
    walls.emplace(0, heights[0]);
    int area_size = 0;
    for (int i=1; i< heights.size();i++) {
        if (heights[i] > walls.top().height){
            int left = walls.top().index;
            int right = i;
            int area_height = min(heights[i], walls.top().height);
            for (int j=left+1; j<=right-1;j++)
                area_size+= area_height- heights[j];
            // clean up all elements
            walls=priority_queue<unit, vector<unit>,Compare >();
            walls.emplace(i,heights[i]);
            
        }else {
            walls.emplace(i,heights[i]);
        }
    }
    
    while(walls.size()>1) {
        int left = walls.top().index;
        walls.pop();
        if (!walls.empty()) {
            while(!walls.empty() &&walls.top().index <left)
                walls.pop();
            if (!walls.empty()) {
                int right = walls.top().index;
                walls.pop();
                int area_height = min(heights[left], heights[right]);
                for (int j=left+1; j<=right-1;j++)
                    area_size+= area_height- heights[j];
                //pop all element inside queue from left to right
                while(!walls.empty() && walls.top().index < right)
                    walls.pop();
                walls.emplace(right, heights[right]);
            }
        }
    }
  return area_size;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"heights"};
  generic_test_main(argc, argv, param_names, "max_water_trappable.tsv",
                    &CalculateTrappingWater);
  return 0;
}
