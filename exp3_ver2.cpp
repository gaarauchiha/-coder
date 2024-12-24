#include <cstdio>

const int m = 1000000007;
long long b[2001];
long long c[2001][2002];
long long dp[2001][2002];

int main() {
    int n, k, i, j;
    long long ans = 0;
    
    scanf("%d %d", &n, &k);
    
    b[0] = b[1] = 1;
    for (i = 2; i <= n; i++) b[i] = b[i - 1] * 2 % m;
    
    for (i = 0; i <= n; i++) {
        c[i][0] = c[i][i] = 1;
        for (j = 1; j < i; j++) c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % m;
    }
        
    
    dp[0][0] = 1;
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= n; j++) {
            if (i > 0) dp[i][j] += dp[i - 1][j + 1];
            if (j > 0) dp[i][j] += dp[i][j - 1];
            if (dp[i][j] >= m) dp[i][j] -= m;
        }
    }
    
    if (n == k) {
        ans = dp[n - 1][0];
    } else {
        for (i = n - k; i < n; i++) {
            ans += c[i - 1][n - k - 1] * dp[n - i - 1][i - n + k] % m;
            if (ans >= m) ans -= m;
        }
        
        ans = ans * b[n - k] % m;
    }
    
    printf("%lld\n", ans);
    
    return 0;
}
