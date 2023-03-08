#pragma once
#include <algorithm>

#include "../header/utils.hpp"
#include <cassert>
#include <vector>

template <typename T1, bool ascend = true> class SortFunc {
private:
  std::vector<T1> unorder_vec_{};
  int prefix_find(std::vector<T1> *vec_p, int loc);
  void vec_meta_select_sort(std::vector<T1> *vec_p, int loc);

  void vec_merge_2seq(std::vector<T1> *vec_p, const int right, const int middle,
                      const int left);
  void vec_meta_merge_sort(std::vector<T1> *vec_p, const int right,
                           const int left);
  void vec_part_assign(std::vector<T1> *vec_p, const std::vector<T1> *temp,
                       const int begin_loc, const int end_loc);

public:
  SortFunc() = default;
  SortFunc(const std::vector<T1> vec) { unorder_vec_ = vec; }
  ~SortFunc() = default;
  void print_origin_vec();
  std::vector<T1> vec_select_sort();
  std::vector<T1> vec_merge_sort();
};

template <typename T1, bool ascend>
void SortFunc<T1, ascend>::print_origin_vec() {
  print_1dvec(unorder_vec_);
}

/**
 * @brief find the max or min value of prefix of vec, the prefix length is
 * declared by [0, loc)
 *
 * @return int return the max or min location OR loc if loc is the max or min
 */
template <typename T1, bool ascend>
int SortFunc<T1, ascend>::prefix_find(std::vector<T1> *vec_p, int loc) {
  if (loc == 0) {
    return loc;
  } else {
    int pre_loc = prefix_find(vec_p, loc - 1);
    if (ascend) {
      if (vec_p->at(loc) > vec_p->at(pre_loc)) {
        return loc;
      } else {
        return pre_loc;
      }
    } else {
      if (vec_p->at(loc) < vec_p->at(pre_loc)) {
        return loc;
      } else {
        return pre_loc;
      }
    }
  }
}

/**
 * @brief select_sort with two parameters. use prefix_max to find the max
 * value in prefix, then compare it with the loc-th element, swap if
 * nessesary
 */
template <typename T1, bool ascend>
void SortFunc<T1, ascend>::vec_meta_select_sort(std::vector<T1> *vec_p,
                                                int loc) {
  if (loc == 0) {
    return;
  }
  int pre_loc = prefix_find(vec_p, loc);
  if (ascend) {
    if (vec_p->at(pre_loc) > vec_p->at(loc)) {
      std::swap(vec_p->at(pre_loc), unorder_vec_.at(loc));
    }
  } else {
    if (vec_p->at(pre_loc) < vec_p->at(loc)) {
      std::swap(vec_p->at(pre_loc), vec_p->at(loc));
    }
  }
  vec_meta_select_sort(vec_p, loc - 1);
}

template <typename T1, bool ascend>
void SortFunc<T1, ascend>::vec_part_assign(std::vector<T1> *vec_p,
                                           const std::vector<T1> *temp,
                                           const int begin_loc,
                                           const int end_loc) {
  for (auto i = begin_loc; i <= end_loc; ++i) {
    vec_p->at(i) = temp->at(i - begin_loc);
  }
}

/**
 * @brief merge two sequences
 */
template <typename T1, bool ascend>
void SortFunc<T1, ascend>::vec_merge_2seq(std::vector<T1> *vec_p,
                                          const int left, const int middle,
                                          const int right) {
  std::vector<T1> temp{};
  int left_i{left};
  int right_i{middle + 1};
  int l_limit{middle - left};
  int r_limit{right - middle - 1};
  while ((left_i - left) <= l_limit && (r_limit - middle - 1) <= r_limit) {
    if (vec_p->at(left_i) < vec_p->at(right_i)) {
      temp.push_back(vec_p->at(left_i));
      left_i += 1;
    } else {
      temp.push_back(vec_p->at(right_i));
      right_i += 1;
    }
  }
  if ((left_i - left) > l_limit) {
    for (auto i = right_i; i <= right; ++i) {
      temp.push_back(vec_p->at(i));
    }
  } else {
    for (auto i = left_i; i <= middle; ++i) {
      temp.push_back(vec_p->at(i));
    }
  }
  vec_part_assign(vec_p, &temp, left, right);
}

/**
 * @brief partition and merge, choose the first element as the pivot-value
 */
template <typename T1, bool ascend>
void SortFunc<T1, ascend>::vec_meta_merge_sort(std::vector<T1> *vec_p,
                                               const int left,
                                               const int right) {
  if (left < right) {
    int middle = (left + right) / 2;
    vec_meta_merge_sort(vec_p, left, middle);
    vec_meta_merge_sort(vec_p, middle + 1, right);
    vec_merge_2seq(vec_p, left, middle, right);
  } else {
    return;
  }
}

template <typename T1, bool ascend>
std::vector<T1> SortFunc<T1, ascend>::vec_select_sort() {
  int loc = unorder_vec_.size() - 1;
  std::vector<T1> *res = &unorder_vec_;
  vec_meta_select_sort(res, loc);
  return *res;
}

template <typename T1, bool ascend>
std::vector<T1> SortFunc<T1, ascend>::vec_merge_sort() {
  int left = 0;
  int right = unorder_vec_.size() - 1;
  std::vector<T1> *res = &unorder_vec_;
  vec_meta_merge_sort(res, left, right);
  return *res;
}