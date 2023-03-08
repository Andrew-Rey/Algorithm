#pragma once

#include <iostream>
#include <vector>

/**
 * @brief print 1 dim vector
 */
template <typename T1> void print_1dvec(const std::vector<T1> vec);

template <typename T1> void print_1dvec(const std::vector<T1> vec) {
  if (!vec.empty()) {
    for (unsigned i{}; i < vec.size(); ++i) {
      std::cout << vec.at(i) << " ";
    }
    std::cout << std::endl;
  }
}