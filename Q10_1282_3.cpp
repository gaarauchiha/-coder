#include <bits/stdc++.h>
using namespace std;

int pw[110][11000];
int qw[110][11000];
int f[110], g[110];
int dp[2][110][110];
int ex[11000];

int a[1<<16];
int b[1<<16];
int c[1<<16];
int x[1<<16];

int fast_exponentiation(int a, int n, int p) {
	int ret = 1;
	for (; n; n >>= 1, a = 1LL * a * a % p) if (n & 1) ret = 1LL * ret * a % p;
	return ret;
}

namespace FFT {

	const int MAXN = 1<<16;
	using LL = long long;
	using DB = double;

	struct CP {
		DB x, y;
		CP(DB x=0, DB y=0) : x(x), y(y) {}
		CP operator+(const CP &rhs) const {
			return CP(x+rhs.x, y+rhs.y);
		}
		void operator+=(const CP &rhs) {
			x += rhs.x, y += rhs.y;
		}
		CP operator-(const CP &rhs) const {
			return CP(x-rhs.x, y-rhs.y);
		}
		CP operator*(const CP &rhs) const {
			return CP(x*rhs.x-y*rhs.y, x*rhs.y+y*rhs.x);
		}
		CP operator!() const {
			return (CP) {
				x, -y
			};
		}
		void operator*=(const CP &rhs) {
			DB tx = x*rhs.x-y*rhs.y, ty = x*rhs.y+y*rhs.x;
			x = tx, y = ty;
		}
	} f[MAXN], g[MAXN], h[MAXN], p_w[MAXN+1], gb[MAXN], gc[MAXN];

	int bit_inv[MAXN];

	void init() {
		DB alpha = acos(-1)/MAXN*2;
		for (int i = 0; i <= MAXN; i++) p_w[i] = CP(cos(alpha*i), sin(alpha*i));
		for (int i = 0, j = 1; j < MAXN; j++) {
			for (int k = MAXN >> 1; (i ^= k) < k; k >>= 1);
			bit_inv[j] = i;
		}
	}

	void FFT(CP *A, int N, int D = 1) {
		for (int j = 1, i, d = __builtin_ctz(MAXN/N); j < N-1; j++) if ((i = (bit_inv[j] >> d)) < j) swap(A[i], A[j]);
		for (int n = 1, m = MAXN/2*D; n < N; m /= 2, n <<= 1) {
			for (int i = 0; i < N; i += n<<1) {
				CP *w = (D == 1 ? p_w : p_w + MAXN), *a = A+i, *b = A+i+n;
				for (int j = 0; j < n; j++, a++, b++, w += m) {
					CP x = *w **b;
					*b = *a - x;
					*a += x;
				}
			}
		}
		if (D != 1) for (int i = 0; i < N; i++) A[i].x /= N, A[i].y /= N;
	}

	void conv(int *A, int *B, int *C, CP *g, int N, int MOD) {
		if (N <= 64) {
			static int temp[64];
			memset(temp, 0, sizeof(int)*N);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N-i; j++) temp[i+j] = (temp[i+j] + 1LL * A[i] * B[j]) % MOD;
				for (int j = N-i; j < N; j++) temp[i+j-N] = (temp[i+j-N] + 1LL * A[i] * B[j]) % MOD;
			}
			memcpy(C, temp, sizeof(int)*N);
			return;
		}
		for (int i = 0; i < N; i++) f[i] = CP(A[i]>>15, A[i]&32767);
		FFT(f, N);
//		for (int i = 0; i < N; i++) g[i] = CP(B[i]>>15, B[i]&32767);
//		FFT(g, N);
		for (int i = 0; i < N; i++) {
			int j=i?N-i:0;
			h[i]=((f[i]+!f[j])*(!g[j]-g[i])+(!f[j]-f[i])*(g[i]+!g[j]))*CP(0,0.25);
		}
		FFT(h, N, -1);
		for (int i = 0; i < N; i++) C[i] = (LL(h[i].x+0.5)%MOD<<15)%MOD;
		for (int i = 0; i < N; i++) {
			int j=i?N-i:0;
			h[i]=(!f[j]-f[i])*(!g[j]-g[i])*CP(-0.25, 0)+CP(0, 0.25)*(f[i]+!f[j])*(g[i]+!g[j]);
		}
		FFT(h, N, -1);
		for (int i = 0; i < N; i++) C[i] = (C[i] + LL(h[i].x+0.5)+((LL(h[i].y+0.5)%MOD)<<30)) % MOD;
	}
};

using FFT::gb;
using FFT::gc;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int n, m, k, mod; cin >> n >> m >> k >> mod;
	for (int x = 0; x <= k; x++) {
		for (int j = 0; j <= n * m; j++) {
			pw[x][j] = j == 0 ? 1 : pw[x][j - 1] * 1LL * x % mod;
		}
		int y = fast_exponentiation(x, mod - 2, mod);
		for (int j = 0; j <= n * m; j++) {
			qw[x][j] = j == 0 ? 1 : qw[x][j - 1] * 1LL * y % mod;
		}
	}
	for (int i = 0; i <= max(n, m); i++) {
		f[i] = i == 0 ? 1 : f[i - 1] * 1LL * i % mod;
		g[i] = fast_exponentiation(f[i], mod - 2, mod);
	}
	int M = 2 * m + 1, N = 2 * n + 1;
	dp[0][0][0] = 1;
	int now = 0;
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			b[i * M + j] = g[i] * 1LL * g[j] % mod;
			c[i * M + j] = b[i * M + j];
			if (i + j & 1) c[i * M + j] = mod - b[i * M + j];
		}
	}
	FFT::init();
	int T = 1 << (32 - __builtin_clz(M * N - 1));
	for (int i = 0; i < T; i++) gb[i] = FFT::CP(b[i] >> 15, b[i] & 32767);
	for (int i = 0; i < T; i++) gc[i] = FFT::CP(c[i] >> 15, c[i] & 32767);
	FFT::FFT(gb, T);
	FFT::FFT(gc, T);
	for (int i = 1; i < k; i++) {
		now ^= 1;
		int alpha = (1 + qw[k - i][1]) % mod;
		for (int j = 0; j <= n * m; j++) {
			ex[j] = j == 0 ? 1 : ex[j - 1] * 1LL * alpha % mod;
		}
		for (int r = 0; r <= n; r++) {
			for (int c = 0; c <= m; c++) {
				a[r * M + c] = dp[!now][r][c] * 1LL * pw[i][(n - r) * (m - c)] % mod;
			}
		}
		FFT::conv(a, b, x, gb, T, mod);
		for (int r = 0; r <= n; r++) {
			for (int c = 0; c <= m; c++) {
				a[r * M + c] = x[r * M + c] * 1LL * ex[r * c] % mod;
			}
		}
		FFT::conv(a, c, x, gc, T, mod);
		for (int r = 0; r <= n; r++) {
			for (int c = 0; c <= m; c++) {
				dp[now][r][c] = x[r * M + c] * 1LL * qw[i][(n - r) * (m - c)] % mod;
			}
		}
	}
	int ans = 0;
	for (int r = 0; r <= n; r++) {
		for (int c = 0; c <= m; c++) {
			ans = (ans + g[n - r] * 1LL * g[m - c] % mod * dp[now][r][c] % mod * pw[k][(n - r) * (m - c)]) % mod;
		}
	}
	ans = 1LL * ans * f[n] % mod * f[m] % mod;
	cout << ans << endl;
	return 0;
}