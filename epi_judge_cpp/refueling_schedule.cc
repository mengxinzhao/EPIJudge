#include <vector>
#include <cstddef>
#include <algorithm>
#include <iostream>
#include <utility>
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
        float gallon_sum =0;
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

//gallons:[4, 2, 6, 6, 4, 5, 3]
//cost  : [2, 2, 6, 7, 6, 5, 2]
//start:  0
//remains  0  2  2  2  1  -1 -1 ==> 0
//start 1     0  0  0  -1 -3 -3 -2  ==> 0
//start 2        0  0  -1 -3 -3 -2  0 ==> 0
//start 5                  0  0  1  3  3  3  2  == > 0
//start 6                     0  1  3  3  3  2  0  ==> 0
//the worst point that is running short of the gas the must be the starting point if it
//can make the move,then every point will be at least >=that point's gas
struct CityAndRemainingGas {
    int city = 0, remaining_gallons = 0;
};

int FindAmpleCity_Greedy(const vector<int>& gallons, const vector<int>& distances) {
    int remaining_gallons = 0;
    
    CityAndRemainingGas city_remaining_gallons_pair;
    const int num_cities = gallons.size();
    for (int i = 1; i < num_cities; ++i) {
        remaining_gallons += gallons[i - 1] - distances[i - 1] / 20;
        if (remaining_gallons < city_remaining_gallons_pair.remaining_gallons) {
            city_remaining_gallons_pair = {i, remaining_gallons};
            //std::cout<<"gallons: "<< remaining_gallons << std::endl;
        }
        
    }
    //at this point the city has the lowest remaining gas before filling up the tank
    if (gallons[city_remaining_gallons_pair.city] >= distances[city_remaining_gallons_pair.city]/20)
        return city_remaining_gallons_pair.city;
    else
        return -1;
}
#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"gallons", "distances"};
  generic_test_main(argc, argv, param_names, "refueling_schedule.tsv",
                    &FindAmpleCity);
  return 0;
}
