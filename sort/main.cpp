#include "./header/SortFunc.hpp"
#include "./header/utils.hpp"
#include <iostream>
#include <vector>


int main() {
  SortFunc<int, false> sort_op;
  std::vector<int> vec {3,4, 1, 9 ,2};
  print_1dvec(vec);
  sort_op.vec_select_sort(&vec);
  print_1dvec(vec);
  return 0;
}
