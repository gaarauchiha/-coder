#include <bits/stdc++.h>

using namespace std;

#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define Debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long LL;
typedef long double LD;
typedef unsigned int uint;
typedef pair <int, int> pii;
typedef unsigned long long uLL;

template <typename T> inline void Read(T &x) {
  char c = getchar();
  bool f = false;
  for (x = 0; !isdigit(c); c = getchar()) {
    if (c == '-') {
      f = true;
    }
  }
  for (; isdigit(c); c = getchar()) {
    x = x * 10 + c - '0';
  }
  if (f) {
    x = -x;
  }
}

template <typename T> inline bool CheckMax(T &a, const T &b) {
  return a < b ? a = b, true : false;
}

template <typename T> inline bool CheckMin(T &a, const T &b) {
  return a > b ? a = b, true : false;
}

const int N = 305;

int n, m, mod, c[N][N], f[N][N], g[N][N];

int main() {
#ifdef wxh010910
  freopen("d.in", "r", stdin);
#endif
  Read(n), Read(m), Read(mod);
  for (int i = 0; i <= n; ++i) {
    c[i][0] = 1;
    for (int j = 1; j <= i; ++j) {
      c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
    }
  }
  for (int i = 1; i <= m; ++i) {
    f[1][i] = g[1][i] = (m - i + 1) % mod;
  }
  for (int i = 2; i <= n; ++i) {
    for (int j = m - 1; j; --j) {
      f[i][j] = (g[i - 1][j + 1] + f[i][j + 1]) % mod;
    }
    for (int j = 1; j <= m; ++j) {
      g[i][j] = f[i][j];
      for (int k = 1; k < i; ++k) {
        g[i][j] = (1LL * f[k][j] * g[i - k][j] % mod * c[i - 1][k - 1] + g[i][j]) % mod;
      }
    }
  }
  printf("%d\n", g[n][1]);
#ifdef wxh010910
  Debug("My Time: %.3lfms\n", (double)clock() / CLOCKS_PER_SEC);
#endif
  return 0;
}
