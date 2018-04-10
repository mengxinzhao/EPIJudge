#include <string>
#include <vector>
#include <queue>
#include <functional>
#include <cstddef>
#include <iostream>
#include "test_framework/test_utils_serialization_traits.h"

using std::string;
using std::vector;
using std::priority_queue;
using std::greater;
using std::queue;

namespace huffman {

struct CharWithFrequency {
  char c;
  double freq;
};

struct BST {
    double freq;
    BST *left;
    BST *right;
    BST(double _freq, BST *_left, BST *_right):freq(_freq),left(_left), right(_right) {}
    bool operator<( const BST &rhs) const {
        return freq < rhs.freq;
    }
};

struct Compare {
    bool operator()( const BST *one, const BST *two) const {
        return one->freq > two->freq;
    }
};

void delete_tree(BST *root){
    if (root == nullptr)
        return;
    else {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}
double HuffmanEncoding(vector<CharWithFrequency>* symbols) {
    priority_queue<BST*,vector<BST *>,Compare> freq_table;
    
    for (size_t i=0; i< symbols->size();i++) {
        freq_table.push(new BST((*symbols)[i].freq,nullptr,nullptr));
    }
    
    //each take 2 smallest freq and put them as leave nodes and return a root with freq combined from the two
    // build the tree from bottom up
    while(freq_table.size()>1) {
        BST *first = freq_table.top();
        freq_table.pop();
        BST *second = freq_table.top();
        freq_table.pop();
        //std::cout<<"select: "<< first->freq<<", "<< second->freq <<std::endl;
        // tree formation
        BST *new_root = nullptr;
        if (first < second)
            new_root = new BST(first->freq + second->freq, first, second) ;
        else
            new_root = new BST(first->freq + second->freq, second, first) ;
        //std::cout<<"insert: "<< new_root->freq<<std::endl;
        freq_table.push(new_root);
    }
    
    BST *root = freq_table.top();
    // a level travel and caculate the average length on the leave node
    queue<BST*> tree_q;
    tree_q.push(root);
    size_t count = tree_q.size();
    size_t depth = 0;
    double avg_length = 0.0;
    while(!tree_q.empty()) {
        if (tree_q.front()->left == nullptr && tree_q.front()->right == nullptr) {
            //std::cout<<"freq: "<< tree_q.front()->freq<< " depth : "<< depth<<std::endl;
            avg_length += tree_q.front()->freq * depth/100;
        }
        if (tree_q.front()->left) {
            tree_q.push(tree_q.front()->left);
        }
        if (tree_q.front()->right){
            tree_q.push(tree_q.front()->right);
        }
        tree_q.pop();
        if (--count ==0) {
            // next level
            depth++;
            //std::cout<<"depth : "<< depth<<std::endl;
            count = tree_q.size();
        }
    }
    
    // delete the tree
    delete_tree(root);
    return avg_length;
}

}  // namespace huffman

template <>
struct SerializationTraits<huffman::CharWithFrequency>
    : UserSerTraits<huffman::CharWithFrequency, std::string, double> {
  static huffman::CharWithFrequency FromTuple(
      const std::tuple<std::string, double>& values) {
    if (std::get<0>(values).size() != 1) {
      throw std::runtime_error(
          "CharWithFrequency parser: string length is not 1");
    }
    return huffman::CharWithFrequency{std::get<0>(values)[0],
                                      std::get<1>(values)};
  }
};

double HuffmanEncodingWrapper(vector<huffman::CharWithFrequency> symbols) {
  return huffman::HuffmanEncoding(&symbols);
}

#include "test_framework/test_utils_generic_main.h"

int main(int argc, char* argv[]) {
  std::vector<std::string> param_names{"symbols"};
  generic_test_main(argc, argv, param_names, "huffman_coding.tsv",
                    &HuffmanEncodingWrapper);
  return 0;
}
