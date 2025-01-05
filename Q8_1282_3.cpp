#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define vi vector<int>
#define pi pair<int, int>
#define mod 998244353
template<typename T> bool chkmin(T &a, T b){return (b < a) ? a = b, 1 : 0;}
template<typename T> bool chkmax(T &a, T b){return (b > a) ? a = b, 1 : 0;}
ll ksm(ll a, ll b) {if (b == 0) return 1; ll ns = ksm(a, b >> 1); ns = ns * ns % mod; if (b & 1) ns = ns * a % mod; return ns;}
using namespace std;
const int S = 4000005;
const int r = 17;
struct st {
    int a[3][2];
}u[S];
int nx[S][3];
int id[r][r][r][r][r][r];
int idcnt = 0;
void sid(st a) {
    idcnt += 1;
    id[a.a[0][0]][a.a[0][1]][a.a[1][0]][a.a[1][1]][a.a[2][0]][a.a[2][1]] = idcnt;
    u[idcnt] = a;
}
int gid(st a) {
    if (id[a.a[0][0]][a.a[0][1]][a.a[1][0]][a.a[1][1]][a.a[2][0]][a.a[2][1]])
        return id[a.a[0][0]][a.a[0][1]][a.a[1][0]][a.a[1][1]][a.a[2][0]][a.a[2][1]];
    else return 0;
}
void calc(int id) {
    for (int j = 0; j < 3; j++) {
        int v = (j + 2) % 3;

        st cur = u[id];
        if (cur.a[v][0]) cur.a[v][0] -= 1;
        cur.a[j][0] += 1;
        cur.a[j][1] += 1;
        nx[id][j] = gid(cur);
    }
}
char inp[55];
int dp[55][S];
void otp(int a) {
    st x = u[a];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            cout << x.a[i][j] << ' ';
    cout << endl;
}
int main() {
    int n;
    cin >> n;
    st a;
    for (a.a[0][0] = 0; a.a[0][0] <= n; a.a[0][0]++) 
    for (a.a[0][1] = a.a[0][0]; a.a[0][1] <= n; a.a[0][1]++)
    for (a.a[1][0] = 0; a.a[1][0] <= n; a.a[1][0]++) 
    for (a.a[1][1] = a.a[1][0]; a.a[1][1] <= n; a.a[1][1]++)
    for (a.a[2][0] = 0; a.a[2][0] <= n; a.a[2][0]++) 
    for (a.a[2][1] = a.a[2][0]; a.a[2][1] <= n; a.a[2][1]++)
        sid(a);
    for (int i = 1; i <= idcnt; i++)
        calc(i);   
    scanf("%s", inp + 1);
    int l = strlen(inp + 1);
    for (int j = l + 1; j >= 1; j--) {
        for (int i = 1; i <= idcnt; i++) {
            if (j == l + 1) {
                st cur = u[i];

                if (cur.a[0][0] + cur.a[1][0] + cur.a[2][0] <= n && cur.a[0][1] == n && cur.a[1][1] == n    
                        && cur.a[2][1] == n) dp[j][i] = 1;
                else dp[j][i] = 0;
            }
            else {
                dp[j][i] = 0;
                if (inp[j] != '?') {
                    dp[j][i] = dp[j + 1][nx[i][inp[j] - 'A']];
                }
                else {
                    for (int m = 0; m < 3; m++) {
                        dp[j][i] += dp[j + 1][nx[i][m]], 
                        dp[j][i] %= mod;
                    }
                }
            }
        }
    }
    cout << dp[1][1] << endl;
    return 0;
}