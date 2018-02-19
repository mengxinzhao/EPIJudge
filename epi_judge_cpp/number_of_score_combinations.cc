#include <vector>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <set>
using std::vector;

// This is not combination. it is a permuation of all possible scoring sequences
//int NumCombinationsForFinalScore(int final_score,
//                                 const vector<int>& individual_play_scores) {
//    // Implement this placeholder.
//    int max_indiv_score = *std::max_element(individual_play_scores.begin(), individual_play_scores.end());
//    vector<int> combination(std::max(final_score+1,max_indiv_score+1),0);
//    combination[0] = 1;
//    for (auto &indiv_score: individual_play_scores)
//        combination[indiv_score] = 1;
//    vector<int> comb;
//    for (int i =1;i<=final_score;i++) {
//        comb.clear();
//        for (auto &indiv_score:individual_play_scores ) {
//            if (i - indiv_score >0) {
//                combination[i] += (i - indiv_score >0)? combination[i-indiv_score]: 0;
//                comb.push_back(i - indiv_score);
//                std::cout<<"pushing.."<<i-indiv_score<<std::endl;
//            }
//        }
//        std::cout<<i<<", "<<combination[i]<<std::endl;
//    }
//  return combination[final_score];
//}

// score[indiv_score][final_score]
// score[2][final_score]  combiniations of using only 2 to achieve final score
// score[3][final_score]  combintation of using only 2+3 to achieve final score
// score[7][final_score] combintation of using  2+3+7 to achieve final score
// return score[7][final_score]
// traverse along indiv_score.
int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
    // Implement this placeholder.
    int max_indiv_score = *std::max_element(individual_play_scores.begin(), individual_play_scores.end());
    vector<int> combination(std::max(final_score+1,max_indiv_score+1),0);
    combination[0] = 1;
    for (auto &indiv_score:individual_play_scores) {
        for (int j = indiv_score; j<=final_score;j++)
            //std::cout<<"pushing.."<<i-indiv_score<<std::endl;
            combination[j] += combination[j-indiv_score];
    }
    return combination[final_score];
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  generic_test_main(argc, argv, param_names, "number_of_score_combinations.tsv",
                    &NumCombinationsForFinalScore);
  return 0;
}
