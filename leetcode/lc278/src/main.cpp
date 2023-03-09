#include <iostream>

using namespace std;

/**你是产品经理，目前正在带领一个团队开发新的产品。
不幸的是，你的产品的最新版本没有通过质量检测。由于每个版本都是基于之前的版本开发的，所以错误的版本之后的所有版本都是错的。

假设你有 n 个版本 [1, 2, ...,
n]，你想找出导致之后所有版本出错的第一个错误的版本。

你可以通过调用 bool isBadVersion(version) 接口来判断版本号 version
是否在单元测试中出错。实现一个函数来查找第一个错误的版本。你应该尽量减少对调用
API 的次数。
*/

// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
private:
  unsigned int bad_version_{};
  bool isBadVersion(int version) { return version == bad_version_; }
  unsigned int binary_search(const unsigned int begin_n, const unsigned int end_n) {
    if (end_n == begin_n && isBadVersion(begin_n)) {
      return begin_n;
    }
    if (isBadVersion((begin_n + end_n) / 2)) {
      return binary_search(begin_n, (begin_n + end_n) / 2);
    } else {
      return binary_search((begin_n + end_n) / 2 + 1, end_n);
    }
  }

public:
  Solution(unsigned int bad_version) : bad_version_{bad_version} {}
  int firstBadVersion(unsigned int n) { return binary_search(0, n); }
};
int main() {
  Solution solution{1702766719};
  unsigned int res = solution.firstBadVersion(2126753390);
  std::cout << res << std::endl;
  return 0;
}
