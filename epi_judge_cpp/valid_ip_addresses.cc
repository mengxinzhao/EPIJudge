#include <algorithm>
#include <string>
#include <vector>
#include <cstddef>
#include <iostream>

using std::string;
using std::vector;
using std::stoi;

void GetValidIpAddressHelper (const string &s, vector<string> & result,
                              int start, int num_parts, string current ) {

    if (start == s.length() && num_parts == 4) {
        result.push_back(current);
    }else if (start < s.length() && num_parts >=4 )
        return;
    else {
        // from start of the string, grab a validated IP part, insert a dot
        // append to the current
        int _start =start, _end = _start ;

        while(s.begin()+_end != s.end()&& 255>=stoi(string(s.begin()+_start, s.begin()+_end+1))) {
            string _current(current);
            _current.insert(_current.end(), s.begin()+_start, s.begin()+_end+1);
            if (num_parts<3)
                _current.insert(_current.end(),'.');
            //std::cout<<current<<std::endl;
            GetValidIpAddressHelper(s, result,_end+1,num_parts+1,_current);
            _end++;
        }
    }
}

vector<string> GetValidIpAddress(const string& s) {
    vector<string>  result;
    string current;
    GetValidIpAddressHelper(s, result,0, 0,current);
    return result;
}

bool comp(vector<string> expected, vector<string> result) {
  std::sort(begin(expected), end(expected));
  std::sort(begin(result), end(result));
  return expected == result;
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"s"};
  generic_test_main(argc, argv, param_names, "valid_ip_addresses.tsv",
                    &GetValidIpAddress, &comp);
  return 0;
}
