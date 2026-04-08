#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

// 循环生成全排列
void permute_loop(vector<int> &nums, vector<vector<int>> &res) {
  sort(nums.begin(), nums.end());
  do {
    res.push_back(nums);
  } while (next_permutation(nums.begin(), nums.end()));
}

// 递归生成全排列
void permute_recursive(vector<int> &nums, vector<vector<int>> &res) {
  if (nums.empty()) {
    res.push_back({});
    return;
  }
  for (size_t i = 0; i < nums.size(); ++i) {
    int num = nums[i];
    vector<int> remaining(nums.begin(), nums.end());
    remaining.erase(remaining.begin() + i);
    vector<vector<int>> sub_res;
    permute_recursive(remaining, sub_res);
    for (auto &perm : sub_res) {
      perm.insert(perm.begin(), num);
      res.push_back(perm);
    }
  }
}

// 循环生成组合_位掩码法
void combine_loop_mask(vector<int> &nums, vector<vector<int>> &res) {
  int n = nums.size();
  for (int mask = 0; mask < (1 << n); ++mask) {
    vector<int> comb;
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) {
        comb.push_back(nums[i]);
      }
    }
    res.push_back(comb);
  }
}

// 循环生成组合_迭代法
void combine_loop(vector<int> &nums, vector<vector<int>> &res) {
  res.push_back({}); // 初始化为空组合
  for (int num : nums) {
    int size = res.size(); // 获取当前组合数量
    for (int i = 0; i < size; ++i) {
      vector<int> comb = res[i];
      comb.push_back(num);
      res.push_back(comb);
    }
  }
}

// 递归生成组合
void combine_recursive(vector<int> &nums, vector<vector<int>> &res) {
  if (nums.empty()) {
    res.push_back({});
    return;
  }
  int num = nums.back();
  vector<int> remaining(nums.begin(), nums.end() - 1); // 不修改原参数，用副本
  vector<vector<int>> sub_res;
  combine_recursive(remaining, sub_res);
  for (const auto &comb : sub_res) {
    res.push_back(comb);         // 不包含num的组合
    vector<int> with_num = comb; // 创建副本
    with_num.push_back(num);
    res.push_back(with_num); // 包含num的组合
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> nums = {1, 2, 3};
  vector<vector<int>> res;

  cout << "全排列（循环生成）：" << endl;
  permute_loop(nums, res);
  for (const auto &perm : res) {
    for (int num : perm) {
      cout << num << " ";
    }
    cout << endl;
  }

  cout << "全排列（递归生成）：" << endl;
  res.clear();
  permute_recursive(nums, res);
  for (const auto &perm : res) {
    for (int num : perm) {
      cout << num << " ";
    }
    cout << endl;
  }

  cout << "组合（循环生成_位掩码法）：" << endl;
  res.clear();
  combine_loop_mask(nums, res);
  for (const auto &comb : res) {
    for (int num : comb) {
      cout << num << " ";
    }
    cout << endl;
  }

  cout << "组合（循环生成_迭代法）：" << endl;
  res.clear();
  combine_loop(nums, res);
  for (const auto &comb : res) {
    for (int num : comb) {
      cout << num << " ";
    }
    cout << endl;
  }

  cout << "组合（递归生成）：" << endl;
  res.clear();
  combine_recursive(nums, res);
  for (const auto &comb : res) {
    for (int num : comb) {
      cout << num << " ";
    }
    cout << endl;
  }

  return 0;
}