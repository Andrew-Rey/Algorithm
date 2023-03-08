#include "./header/SortFunc.hpp"
#include "./header/utils.hpp"
#include <iostream>
#include <vector>


int main() {
  std::vector<int> vec {3,4, 1, 9 ,2};
  std::vector<int> sorted_vec {};
  SortFunc<int> sort_op {vec};
  sort_op.print_origin_vec();

  std::cout << "select sort: " << " ";
  sorted_vec = sort_op.vec_select_sort();
  print_1dvec(sorted_vec);

  std::cout << "merge sort: "<<" ";
  sorted_vec = sort_op.vec_merge_sort();
  print_1dvec(sorted_vec);
  return 0;
}
