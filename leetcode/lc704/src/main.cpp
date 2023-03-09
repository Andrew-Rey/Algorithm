#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief 给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target
 *  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
 *
 */

class Solution {
public:
  int binary_search(std::vector<int> &nums, const int left, const int right,
                    const int target) {
    if (left >= right && nums[left] != target) {
      return -1;
    }
    if (nums.at(left) == target) {
      return left;
    }
    if (nums.at(right) == target) {
      return right;
    }
    int mid = (left + right) / 2;
    if (target == nums.at(mid)) {
      return mid;
    }
    if (target <= nums.at(mid)) {
      return binary_search(nums, left, mid, target);
    } else {
      return binary_search(nums, mid + 1, right, target);
    }
  }
  int search(std::vector<int> &nums, const int target) {
    int res_loc{};
    if (nums.empty()) {
      res_loc = -1;
    } else {
      res_loc = binary_search(nums, 0, nums.size() - 1, target);
    }
    return res_loc;
  }
};

int main() {
  Solution solution{};
  std::vector<int> nums{-1, 0, 3, 5, 9, 12};
  int target = 9;
  int res_loc = solution.search(nums, target);
  std::cout << res_loc << std::endl;
  return 0;
}
