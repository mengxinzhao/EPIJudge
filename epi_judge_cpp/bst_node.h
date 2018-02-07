
#pragma once

#include <memory>

#include "test_framework/binary_tree_utils.h"
#include "test_framework/test_utils_serialization_traits.h"

using std::unique_ptr;

template <typename T>
struct BstNode {
  T data;
  unique_ptr<BstNode<T>> left, right;

  explicit BstNode(const T& data) : data(data) {}

  BstNode(T data, unique_ptr<BstNode<T>> left, unique_ptr<BstNode<T>> right)
      : data(data), left(std::move(left)), right(std::move(right)) {}
};

template <typename KeyT>
struct SerializationTraits<std::unique_ptr<BstNode<KeyT>>>
    : BinaryTreeSerializationTraits<std::unique_ptr<BstNode<KeyT>>, false> {};
