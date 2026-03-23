#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

void print_postorder(int pre_start, int pre_end, int in_start, int in_end,
                     const string &pre, const string &in) {
  if (pre_start > pre_end) {
    return;
  }
  char root = pre[pre_start];
  int root_index = in.find(root);
  int left_size = root_index - in_start;

  print_postorder(pre_start + 1, pre_start + left_size, in_start,
                  root_index - 1, pre, in);
  print_postorder(pre_start + left_size + 1, pre_end, root_index + 1, in_end,
                  pre, in);
  cout << root;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  //   begin
  string pre, in;
  cin >> in >> pre;

  print_postorder(0, pre.size() - 1, 0, in.size() - 1, pre, in);
  cout << "\n";
  //   end

  return 0;
}