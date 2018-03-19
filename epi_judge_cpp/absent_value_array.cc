#include <stdexcept>
#include <vector>
#include <cstdint>
#include <unordered_map>
#include <iostream>
#include <iomanip>
#include <climits>
#include "test_framework/test_failure_exception.h"

using std::invalid_argument;
using std::vector;
using std::unordered_map;

// uint32_t range  [0,2^32-1] ~ 4 billion
// bit for counting each uint32_t 2^32/8 = 512M
// problem statement has memory restriction <  2 MB ram
// use method similar to page address
// address =  page_index * page_size + offset_in_the_page
// page_size = 2^16
// use 2^16 * 4byte to count = 1MB
// offset_in_the_page = 2^16
// if one address is missing, one page_index would be less than others
//
// the test data is not billion files
int FindMissingElement(vector<int>::const_iterator stream_begin,
                       const vector<int>::const_iterator& stream_end) {
    const int page_size = 1024 * 64;
    vector<int> count(page_size,0);
    std::cout<<*stream_begin<<std::endl;
    auto _stream_begin = stream_begin;
    while(_stream_begin!=stream_end){
        //std::cout<<*_stream_begin<<std::endl;
        count[(*_stream_begin)>>16]++;
        _stream_begin++;
    }
    int missing_page = *(std::min_element(count.begin(),count.end()));
    std::cout<<"missing_page: " << missing_page<<std::endl;
    // now to find offset
    vector<int> offset_count(page_size,0);
    _stream_begin = stream_begin;
    while(_stream_begin!=stream_end){
        if ((*_stream_begin >> 16 )== missing_page) {
            offset_count[*_stream_begin & (page_size-1)]++;
        }
        _stream_begin++;
    }
    int missing_offset = *(std::min_element(offset_count.begin(),offset_count.end()));
//    for( auto & iter: offset_count)
//        std::cout<<iter<<std::endl;
    std::cout<<"missing_offset: " << missing_offset<<std::endl;
    return (missing_page << 16) + missing_offset;
}

int FindMissingElementWrapper(const vector<int>& stream) {
  try {
    return FindMissingElement(cbegin(stream), cend(stream));
  } catch (invalid_argument&) {
    throw TestFailureException("Unexpected no_missing_element exception");
  }
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"stream"};
  generic_test_main(argc, argv, param_names, "absent_value_array.tsv",
                    &FindMissingElementWrapper);
  return 0;
}
