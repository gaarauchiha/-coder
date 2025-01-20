#include <bits/stdc++.h>

using namespace std;

const int MX = 200000, md = 1000000007;

char s[MX + 1];
int dp[MX + 1], sum[MX + 1];

int main() {
	int n, m;
	ignore = scanf("%d %d %s", &n, &m, s);
	
	char R = s[0];
	
	vector<int> sizes;
	for (int i = 0, sz = 0; i < m; i++) {
		if (s[i] == R) sz++;
		else if (sz > 0) {
			sizes.push_back(sz);
			sz = 0;
		}
	}
	
	if (sizes.empty()) {
		auto count = [](int n, int first) {
			int f = first, g = 1 - first;
			for (int i = 1; i < n; i++) {
				tie(f, g) = make_pair(f + g, f);
				f %= md;
				g %= md;
			}
			
			return (f + first * g) % md;
		};
		
		int ans = count(n, 0) + count(n, 1);
		ans %= md;
		printf("%d\n", ans);
		
		return 0;
	}
	
	int maxSize = sizes[0] + 1;
	for (int sz : sizes) if (sz % 2 == 1) maxSize = min(maxSize, sz);
	
	if (maxSize % 2 == 0) maxSize--;
	
	for (int i = 2; i <= n; i++) {
		dp[i] = sum[i - 2];
		
		if (i - maxSize - 3 >= 0) {
			dp[i] += md - sum[i - maxSize - 3];
			dp[i] %= md;
		}
		
		if (1 <= i - 1 && i - 1 <= maxSize && i % 2 == 0) {
			dp[i] += i;
			dp[i] %= md;
		}
		
		sum[i] = dp[i];
		if (i - 2 > 0) {
			sum[i] += sum[i - 2];
			sum[i] %= md;
		}
	}
	
	printf("%d\n", dp[n]);
	
	return 0;
}
