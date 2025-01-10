#include <bits/stdc++.h>
using namespace std;
#define FOR(i,m,n) for(int i=(m);i<(n);++i)
#define REP(i,n) FOR(i,0,n)
#define ALL(v) (v).begin(),(v).end()
using ll = long long;
constexpr int INF = 0x3f3f3f3f;
constexpr long long LINF = 0x3f3f3f3f3f3f3f3fLL;
constexpr double EPS = 1e-8;
constexpr int MOD = 998244353;
// constexpr int MOD = 1000000007;
constexpr int DY4[]{1, 0, -1, 0}, DX4[]{0, -1, 0, 1};
constexpr int DY8[]{1, 1, 0, -1, -1, -1, 0, 1};
constexpr int DX8[]{0, -1, -1, -1, 0, 1, 1, 1};
template <typename T, typename U>
inline bool chmax(T& a, U b) { return a < b ? (a = b, true) : false; }
template <typename T, typename U>
inline bool chmin(T& a, U b) { return a > b ? (a = b, true) : false; }
struct IOSetup {
  IOSetup() {
    std::cin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
    std::cout << fixed << setprecision(20);
  }
} iosetup;

void solve() {
  int n; cin >> n;
  vector<int> w(n); REP(i, n) cin >> w[i];
  vector<vector<int>> graph(n);
  REP(_, n - 1) {
    int u, v; cin >> u >> v; --u; --v;
    graph[u].emplace_back(v);
    graph[v].emplace_back(u);
  }
  const auto it = max_element(ALL(graph), [](const vector<int>& a, const vector<int>& b) -> bool { return a.size() < b.size(); });
  if (it->size() == 2) {
    vector<int> leaves;
    REP(i, n) {
      if (graph[i].size() == 1) leaves.emplace_back(i);
    }
    cout << 1 << '\n'
         << leaves.front() + 1 << ' ' << leaves.back() + 1 << '\n';
    return;
  }
  vector<int> par(n, -1), leaves;
  const auto f = [&](auto f, const int ver) -> void {
    if (graph[ver].size() == 1) leaves.emplace_back(ver);
    for (const int e : graph[ver]) {
      if (e != par[ver]) {
        par[e] = ver;
        f(f, e);
      }
    }
  };
  REP(i, n) {
    if (graph[i].size() == 3) {
      f(f, i);
      break;
    }
  }
  vector<pair<int, int>> ans;
  ans.reserve((leaves.size() + 1) / 2);
  if (leaves.size() % 2 == 1) {
    map<int, set<int>> costs;
    REP(i, n) costs[w[i]].emplace(i);
    int del = -1, pr = -1, min_cost = INF;
    for (const int l : leaves) {
      for (int ver = l; ; ver = par[ver]) {
        const auto it = costs.find(w[ver]);
        it->second.erase(ver);
        if (it->second.empty()) costs.erase(it);
        if (graph[ver].size() == 3) break;
      }
      if (chmin(min_cost, costs.begin()->first)) {
        del = l;
        pr = *costs.begin()->second.begin();
      }
      for (int ver = l; ; ver = par[ver]) {
        costs[w[ver]].emplace(ver);
        if (graph[ver].size() == 3) break;
      }
    }
    ans.emplace_back(del, pr);
    leaves.erase(find(ALL(leaves), del));
  }
  const int s = leaves.size();
  REP(i, s / 2) ans.emplace_back(leaves[i], leaves[i + s / 2]);
  cout << ans.size() << '\n';
  for (const auto& [a, b] : ans) {
    cout << a + 1 << ' ' << b + 1 << '\n';
  }
}

int main() {
  int t; cin >> t;
  while (t--) solve();
  return 0;
}
