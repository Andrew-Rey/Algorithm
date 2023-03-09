#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 O(log n) 的算法。
 */

class Solution {
private:
  int binary_search(std::vector<int> &nums, const int left, const int right,
                    const int target) {
    int mid = (left + right) / 2;
    if (left >= right && target != nums.at(left)) {
      // cant find
      return left;
    }
    if (target == nums.at(left)) {
      return left;
    }
    if (target == nums.at(right)) {
      return right;
    }
    if (target == nums.at(mid)) {
      return mid;
    }
    if (target < nums.at(mid)) {
      return binary_search(nums, left, mid, target);
    } else {
      return binary_search(nums, mid + 1, right, target);
    }
  }

public:
  int searchInsert(std::vector<int> &nums, int target) {
    if (target > nums.back()) {
      return nums.size();
    }
    return binary_search(nums, 0, nums.size() - 1, target);
  }
};

int main(int argc, char **argv) {
  Solution solution{};
  std::vector<int> nums{1, 3, 5, 6};
  int target{7};
  int res = solution.searchInsert(nums, target);
  std::cout << res << std::endl;
  return 0;
}
