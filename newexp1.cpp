#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include <nmmintrin.h>
#include <fstream>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <queue>
#include <cmath>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

int main()
{
	int n;
	cin >> n;
	vvi a(n, vi(n));
	if (n % 2 == 0) {
		int c = 1;
		for (int i = n / 2 - 1; i >= 0; --i)
			for (int j = 0; j < n; ++j, c += 2)
				a[i][j] = c;
		c = n * n - 2;
		for (int i = n / 2; i < n; ++i) {
			for (int j = 0; j < n; ++j, c -= 2) {
				if (c < 1)
					c = n * n;
				a[i][j] = c;
			}
		}
	} else if (n == 3) {
		a = { {9,3,1}, {5,7,8},{4,2,6} };
	} else {
		int c = 1;
		for (int j = 0; j <= n / 2; ++j, c += 2) {
			a[n / 2][j] = c;
			a[n / 2 + 1][j] = n * n - c;
		}
		int d = c;
		vi skipped;
		int n_skipped = 0;
		while ((-d + (c - 2) + n * n) % 3 != 0) {
			skipped.push_back(d);
			d += 2;
		}
		c = d;
		for (int j = n / 2 + 1; j < n; ++j, c += 2) {
			a[n / 2 - 1][j] = c;
			a[n / 2][j] = n * n - c;
		}
		a[n / 2 - 1][n / 2] = n * n;
		for (int i = 0; i < n / 2; ++i) {
			for (int j = 0; j < n; ++j) {
				if (i == n / 2 - 1 && j >= n / 2)
					break;
				int put_num = 0;
				if (n_skipped < skipped.size()) {
					put_num = skipped[n_skipped];
					++n_skipped;
				} else {
					put_num = c;
					c += 2;
				}
				a[i][j] = put_num;;
				a[n - 1 - i][n - j - 1] = n * n - put_num;
			}
		}
	}
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			cout << a[i][j] << " \n"[j == n - 1];
	return 0;
}
