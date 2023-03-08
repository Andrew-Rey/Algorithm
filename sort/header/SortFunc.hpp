#pragma once
#define SUCCESS 0
#define NULL_VEC -1
#define OUT_OF_RANGE -2

#include "../header/utils.hpp"
#include <cassert>
#include <vector>

template <typename T1, bool ascend = true> class SortFunc {
private:
  int prefix_find(const std::vector<T1> *vec_p, int loc);
  int vec_meta_select_sort(std::vector<T1> *vec_p, int loc);
  int vec_meta_merge_sort(std::vector<T1> *vec_p, const int right_loc,
                           const int left_loc);

public:
  SortFunc() = default;
  ~SortFunc() = default;
  void vec_select_sort(std::vector<T1> *vec_p);
  void vec_merge_sort(std::vector<T1> *vec_p);
};

/**
 * @brief find the max or min value of prefix of vec, the prefix length is
 * declared by [0, loc)
 *
 * @return int return the max or min location OR loc if loc is the max or min
 */
template <typename T1, bool ascend>
int SortFunc<T1, ascend>::prefix_find(const std::vector<T1> *vec_p, int loc) {
  if (loc < 0) {
    return OUT_OF_RANGE;
  }
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
 *
 * @return int next loc-place, [0, loc) is unorder, [loc, size) is order
 */
template <typename T1, bool ascend>
int SortFunc<T1, ascend>::vec_meta_select_sort(std::vector<T1> *vec_p,
                                               int loc) {
  if (vec_p != nullptr && loc >= 0) {
    int pre_loc = prefix_find(vec_p, loc);
    if (ascend) {
      if (vec_p->at(pre_loc) > vec_p->at(loc)) {
        std::swap(vec_p->at(pre_loc), vec_p->at(loc));
      }
    } else {
      if (vec_p->at(pre_loc) < vec_p->at(loc)) {
        std::swap(vec_p->at(pre_loc), vec_p->at(loc));
      }
    }
    vec_meta_select_sort(vec_p, loc - 1);
  }
  return NULL_VEC;
}

/**
 * @brief partition and merge, choose the first element as the pivot-value
 * 
 * @return int the status
 */
template <typename T1, bool ascend>
int SortFunc<T1, ascend>::vec_meta_merge_sort(std::vector<T1> *vec_p,
                                               const int left,
                                               const int right) {
  if (vec_p != nullptr) {
    if (left <= right) {
      int middle = (left + right) / 2;
      vec_meta_merge_sort(vec_p, left, middle);
      vec_meta_merge_sort(vec_p, middle + 1, right);
    }
  }
  return NULL_VEC;
}

template <typename T1, bool ascend>
void SortFunc<T1, ascend>::vec_select_sort(std::vector<T1> *vec_p) {
  if (vec_p != nullptr) {
    int loc = vec_p->size() - 1;
    int status = vec_meta_select_sort(vec_p, loc);
    assert(status == NULL_VEC);
  }
}

template <typename T1, bool ascend>
void SortFunc<T1, ascend>::vec_merge_sort(std::vector<T1> *vec_p) {
    if (vec_p != nullptr) {
        int left = 0;
        int right = vec_p->size() - 1;
        int status = vec_merge_sort(vec_p, left, right);
        assert(status == NULL_VEC);
    }
}