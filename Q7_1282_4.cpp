#include <iostream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <set>
 
using namespace std;
typedef long long ll;
const int MAXN = 510;

int N;
ll A[MAXN][MAXN];
ll ps[MAXN][MAXN];
ll vs[MAXN][MAXN];
ll dp[MAXN][MAXN]; 
ll ndp[MAXN][MAXN];

int main()
{
    ios_base::sync_with_stdio(0);

    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == i) A[i][j] = 0;
            else cin >> A[i][j];
        }
    }

    for (int i = 0; i < N; i++)
    {
        ps[i][0] = 0;
        for (int j = 0; j < N; j++)
            ps[i][j+1] = ps[i][j] + A[i][j];
        vs[i][0] = 0;
        for (int j = 0; j < N; j++)
            vs[i][j+1] = vs[i][j] + A[j][i];
    }

    for (int i = 0; i < MAXN; i++)
        for (int j = 0; j < MAXN; j++)
            dp[i][j] = 1e17;
    dp[0][0] = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j <= N; j++)
            for (int k = 0; k <= N; k++)
                ndp[j][k] = 1e17;

        for (int j = 0; j <= i; j++)
        {
            for (int k = 0; k <= i - j; k++)
            {
                if (dp[j][k] > 9e16) continue;

                int ostart = i - j;
                int mstart = i - j - k;
                
                ll rtot = 0;
                rtot += vs[i][i] - vs[i][ostart];
                rtot += ps[i][mstart];
                ndp[j+1][k] = min (ndp[j+1][k], dp[j][k] + rtot);

                rtot = 0;
                rtot += ps[i][ostart];
                ndp[1][j] = min (ndp[1][j], dp[j][k] + rtot);
            }
        }

        for (int j = 0; j <= N; j++)
            for (int k = 0; k <= N; k++)
                dp[j][k] = ndp[j][k];
    }

    ll ans = 1e18;
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= N; j++)
            ans = min (ans, dp[i][j]);
    cout << ans << "\n";
}