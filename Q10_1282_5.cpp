#include <bits/stdc++.h>

using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

class dsu {
 public:
  vector<int> p;
  int n;

  dsu(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) {
    return (x == p[x] ? x : (p[x] = get(p[x])));
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  while (tt--) {
    int n, k;
    cin >> n >> k;
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
      cin >> p[i];
      --p[i];
    }
    auto orig = p;
    int lim = 2 * n;
    dsu d(n);
    for (int i = 0; i < n; i++) {
      if (d.unite(i, p[i])) {
        lim -= 1;
      }
    }
    if (k > lim || k % 2 != lim % 2) {
      cout << "No" << '\n';
      continue;
    }
    int cur = lim;
    cout << "Yes" << '\n';
    vector<int> seq;
    for (int i = 0; i < n; i++) {
      if (d.get(i) == i) {
        if (seq.empty()) {
          seq.push_back(i);
        } else {
          if (cur > k) {
            cur -= 2;
            swap(p[seq.back()], p[i]);
            seq.push_back(i);
          }
        }
      }
    }
    if (cur > k) {
      vector<bool> was(n, false);
      vector<int> cycle(1, seq.back());
      was[cycle[0]] = true;
      for (int i = 1; i < n; i++) {
        int nxt = p[cycle[i - 1]];
        assert(!was[nxt]);
        was[nxt] = true;
        cycle.push_back(nxt);
      }
      vector<int> use;
      for (int x : cycle) {
        if (d.get(x) != x) {
          use.push_back(x);
        }
      }
      for (int i = 0; i < (int) use.size() - 1; i += 2) {
        if (cur > k) {
          cur -= 2;
          int x = use[i];
          swap(p[seq.back()], p[x]);
          seq.push_back(x);
          int y = use[i + 1];
          swap(p[seq.back()], p[y]);
          seq.push_back(y);
        }
      }
      assert(cur == k);
    }
    vector<int> x(n);
    iota(x.begin(), x.end(), 0);
    for (int i = 0; i < (int) seq.size() - 1; i++) {
      swap(x[seq[i]], x[seq[i + 1]]);
    }
    vector<int> y(n);
    for (int i = 0; i < n; i++) {
      y[i] = orig[x[i]];
    }
    int comp = 2 * n;
    dsu dx(n);
    dsu dy(n);
    for (int i = 0; i < n; i++) {
      if (dx.unite(i, x[i])) {
        comp -= 1;
      }
      if (dy.unite(i, y[i])) {
        comp -= 1;
      }
    }
    assert(comp == k);
    for (int i = 0; i < n; i++) {
      cout << x[i] + 1 << " \n"[i == n - 1];
    }
  }
  return 0;
}
