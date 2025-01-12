#include <bits/stdc++.h>
using namespace std;
#define sz(x) ((int) (x).size())
#define forn(i,n) for (int i = 0; i < int(n); ++i)
typedef long long ll;
typedef long long i64;
typedef long double ld;
const int inf = int(1e9) + int(1e5);
const ll infl = ll(2e18) + ll(1e10);

#define int ll

const int maxn = 100100;
vector<int> xc, yc;
set<pair<int, int>> byx[maxn], byy[maxn];
vector<int> vbyx[maxn], vbyy[maxn];
bool used[maxn];
int deg[maxn];
int x[maxn], y[maxn];
int d;
int ANS;

int lb(int id, const vector<int> &v) {
    return lower_bound(v.begin(), v.end(), id) - v.begin();
}

void erase(int u) {
    ANS += deg[u];
    used[u] = true;
    int nx = lb(x[u], xc);
    int ny = lb(y[u], yc);
    byx[nx].erase(make_pair(y[u], u));
    byy[ny].erase(make_pair(x[u], u));
}

void dfs(int u) {
    vector<int> to;

    for (int delta: {-d, +d}) {
        int cx = x[u] + delta;
        int nx = lb(cx, xc);
        if (nx < sz(xc) && xc[nx] == cx) {
            for (auto it = byx[nx].lower_bound({y[u] - d, -1}); 
                        it != byx[nx].end() && it->first <= y[u] + d; ++it) {
                to.push_back(it->second);
            }
        }
    }
    for (int delta: {-d, +d}) {
        int cy = y[u] + delta;
        int ny = lb(cy, yc);
        if (ny < sz(yc) && yc[ny] == cy) {
            for (auto it = byy[ny].lower_bound({x[u] - d, -1}); 
                        it != byy[ny].end() && it->first <= x[u] + d; ++it) {
                to.push_back(it->second);
            }
        }
    }

    sort(to.begin(), to.end());
    to.erase(unique(to.begin(), to.end()), to.end());
    for (int v: to)
        erase(v);
    for (int v: to)
        dfs(v);
}

signed main() {
    #ifdef LOCAL
    assert(freopen("e.in", "r", stdin));
    #else
    #endif
    int n, a, b;
    cin >> n >> a >> b;
    --a, --b;
    forn (i, n) {
        int _x, _y;
        cin >> _x >> _y;
        x[i] = _x + _y;
        y[i] = _x - _y;
        xc.push_back(x[i]);
        yc.push_back(y[i]);
    }
    d = max(abs(x[a] - x[b]), abs(y[a] - y[b]));
    sort(xc.begin(), xc.end());
    xc.erase(unique(xc.begin(), xc.end()), xc.end());
    sort(yc.begin(), yc.end());
    yc.erase(unique(yc.begin(), yc.end()), yc.end());
    forn (i, n) {
        int nx = lb(x[i], xc);
        int ny = lb(y[i], yc);
        byx[nx].emplace(y[i], i);
        byy[ny].emplace(x[i], i);
        vbyx[nx].push_back(y[i]);
        vbyy[ny].push_back(x[i]);
    }
    forn (i, sz(xc))
        sort(vbyx[i].begin(), vbyx[i].end());
    forn (i, sz(yc))
        sort(vbyy[i].begin(), vbyy[i].end());
    forn (i, n) {
        for (int delta: {-d, +d}) {
            int cx = x[i] + delta;
            int nx = lb(cx, xc);
            if (nx < sz(xc) && xc[nx] == cx) {
                int yl = y[i] - d - 1;
                int yr = y[i] + d;
                yl = lb(yl, vbyx[nx]);
                yr = lb(yr, vbyx[nx]);
                deg[i] += yr - yl;
            }
        }
        for (int delta: {-d, +d}) {
            int cy = y[i] + delta;
            int ny = lb(cy, yc);
            if (ny < sz(yc) && yc[ny] == cy) {
                int xl = x[i] - d - 1;
                int xr = x[i] + d;
                xl = lb(xl, vbyy[ny]);
                xr = lb(xr, vbyy[ny]);
                deg[i] += xr - xl;
            }
        }
        //cerr << deg[i] << '\n';
    }
    erase(a);
    dfs(a);
    cout << ANS / 2 << '\n';
}
