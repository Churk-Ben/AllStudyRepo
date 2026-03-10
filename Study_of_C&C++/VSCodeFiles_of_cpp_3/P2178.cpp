#include <iostream>
#include <queue>
#include <string>
#include <vector>


using namespace std;

struct Task {
  string name;
  int needed;
  int spent = 0;
};

int main() {
  int N, Q, t = 0;
  queue<Task> q;
  vector<Task> p;

  cin >> N >> Q;

  for (int i = 0; i < N; i++) {
    Task p;
    cin >> p.name >> p.needed;
    q.push(p);
  }

  while (!q.empty()) {
    Task cur = q.front();
    if (cur.needed > Q) {
      cur.needed -= Q;
      q.push(cur);
      q.pop();
      t += Q;
    } else {
      cur.spent = t + cur.needed;
      t += cur.needed;
      p.push_back(cur);
      q.pop();
    }
  }

  for (auto task : p) {
    cout << task.name << " " << task.spent << endl;
  }

  return 0;
}