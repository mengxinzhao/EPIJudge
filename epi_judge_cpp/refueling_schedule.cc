#include <vector>
#include <cstddef>
#include <algorithm>
#include <iostream>
using std::vector;
using std::sort;

// gallons[i] is the amount of gas in city i, and distances[i] is the distance
// city i to the next city.
struct Candidate{
    int index;
    float ratio;
    Candidate (int _index,  float _ratio): index(_index), ratio(_ratio) {}
    bool operator < (const Candidate &rhs) const {
        return ratio > rhs.ratio;
    }
};
// sort the city by gallons/cost cost = distance/mile_per_gallon
// and pick up the one that has the  gallon/distance ratio >= 1 as the start city
// check path way that sum (gallons[i])/sum(cost[i]) >=1 for every i in the path
// O(n^2)
int FindAmpleCity(const vector<int>& gallons, const vector<int>& distances) {

    vector<Candidate> candidates;
    for (size_t i=0; i < gallons.size();i++)
        candidates.emplace_back(i,float(gallons[i])/(float(distances[i])/20));
    
    sort(candidates.begin(),candidates.end());

    int i = 0;
    while( i< candidates.size() && candidates[i].ratio >=1) {
        int gallon_sum =0;
        float cost_sum =0;
        int start_index = candidates[i].index;
        int index =start_index;
        bool visited = false;   // if a circle has been made
        while(!visited) {
            gallon_sum+= gallons[index];
            cost_sum += (float)distances[index]/20;
            if (gallon_sum/cost_sum >=1) {
                index = (index+1)%gallons.size();
                if (index == start_index)
                    visited = true;
            }else{
                // not gonna make it
                break;
            }
        }
        // complete the circle
        if (index == start_index)
            return start_index;
        i++;
    }
    return -1;//no such city
}


#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"gallons", "distances"};
  generic_test_main(argc, argv, param_names, "refueling_schedule.tsv",
                    &FindAmpleCity);
  return 0;
}
