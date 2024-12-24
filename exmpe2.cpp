#include <bits/stdc++.h>
#define ll long long
#define lc(x) ((x) << 1)
#define rc(x) ((x) << 1 | 1)
#define ru(i, l, r) for (int i = (l); i <= (r); i++)
#define rd(i, r, l) for (int i = (r); i >= (l); i--)
#define mid ((l + r) >> 1)
#define pii pair<int, int>
#define mp make_pair
#define fi first
#define se second
#define sz(s) (int)s.size()
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>
using namespace std;
#define maxn 405
mt19937 Rand(chrono::steady_clock::now().time_since_epoch().count());
const int mo = 998244353;
int read() {
    int x = 0, w = 0; char ch = getchar();
    while(!isdigit(ch)) w |= ch == '-', ch = getchar();
    while(isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return w ? -x : x;
}
int n, a[maxn];
int qpow(int x, int step) {
    int res = 1;
    for (; step; step >>= 1) {
        if(step & 1) res = (ll)res * x % mo;
        x = (ll)x * x % mo;
    }
    return res;
}
void upd(int &x, int y) {
    x += y; if(x >= mo) x -= mo;
}
int dp[maxn][maxn][maxn], c[maxn][maxn], sum[maxn][maxn];
int main() {
    ru(i, 0, maxn - 1) {
        c[i][0] = c[i][i] = 1;
        ru(j, 1, i - 1) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % mo;
    }
    int n = read(), m = read();
    ru(i, 1, m) dp[1][1][i] = 1;
    ru(i, 2, n) {
    
    memset(sum, 0, sizeof(sum));
    ru(a, 1, m) ru(b, 1, m) sum[a][b] = (((dp[i - 1][a][b] + sum[a - 1][b]) % mo + sum[a][b - 1]) % mo + mo - sum[a - 1][b - 1]) % mo;    
    ru(nl, 1, m) ru(nr, nl, m) {//ru(l, 1, nl) ru(r, nl - 1, min(nr, m)) {
        dp[i][nl][nr] = sum[nl][min(nr, m)];
        if(nl > 1) upd(dp[i][nl][nr], mo - sum[nl][nl - 2]);
        //upd(dp[i][nl][nr], dp[i - 1][l][r]);
    }
    }
    int ans = 1;
    ru(i, 1, n) ru(j, 1, m) {
        int sum = 0;
        ru(k, 1, j) upd(sum, dp[i][k][j]);
        upd(ans, (ll)sum * c[n][i] % mo * c[m][j] % mo);
    }
    printf("%d\n", ans);
    return 0;
}