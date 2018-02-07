#include <vector>
#include <cstdlib>
#include <algorithm>
using std::vector;

// have to think about all cases.
// 1. All cut
// 2. some cut some not
// 3. no need to cut at all
double FindSalaryCap(int target_payroll, vector<int> current_salaries) {
  // Implement this placeholder.
	double sum = 0;
	double thres = -1.0;
	double max_thres = -1.0;
	vector<int> &v = current_salaries;
	std::sort(v.begin(),v.end());

	// all cut
	thres = target_payroll / v.size();
	max_thres = (max_thres > thres) ? max_thres : thres;

  for (size_t i=0; i < v.size();i++) {
	  sum += v[i];
	  if (v.size()-i-1 >0) {
		  thres = (target_payroll - sum) / (v.size() - i - 1);
	  }else {
		  if (target_payroll - sum >0 )
			  return -1.0; //no need to cut at all
		  thres = 0;
	  }
	  max_thres = (max_thres > thres) ? max_thres : thres;

  }

	return  max_thres;// impossible
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"target_payroll", "current_salaries"};
  generic_test_main(argc, argv, param_names, "find_salary_threshold.tsv",
                    &FindSalaryCap);
  return 0;
}
