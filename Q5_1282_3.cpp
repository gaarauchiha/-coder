#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll mod = 1000000007;
#define SIZE 10101010
ll inv[SIZE + 1];
ll kai[SIZE + 1];
ll invkai[SIZE + 1];
void invinit()
{
	inv[1] = 1;
	for (int i = 2; i <= SIZE; i++)
	{
		inv[i] = mod - (mod / i)*inv[mod%i] % mod;
	}
	kai[0] = invkai[0] = 1;
	for (int i = 1; i <= SIZE; i++)
	{
		kai[i] = kai[i - 1] * i%mod;
		invkai[i] = invkai[i - 1] * inv[i] % mod;
	}
}
ll com(ll a, ll b)
{
	if (b < 0 || a < b)return 0;
	return (invkai[b] * invkai[a - b]) % mod*kai[a] % mod;
}
int main()
{
	int num, gen;
	scanf("%d%d", &num, &gen);
	invinit();
	ll r = 0;
	int t = num - gen;
	for (int i = 1; i <= gen; i++)
	{
		ll s = 0;
		for (int j = 0; j < i; j++)
		{
			int rem = i - j;
			ll z = kai[t] * kai[rem] % mod*com(t + rem - 1, t) % mod*com(i, j) % mod;
			if (i < gen)
			{
				ll q = kai[num - j - 1] * invkai[num - gen + i - j] % mod;
				z = (z*q) % mod;
			}
			if (j % 2 == 0)s = (s + z) % mod;
			else s = (s + mod - z) % mod;
		}
		//printf("%d %lld\n", i, s);
		r = (r + s) % mod;
	}
	printf("%lld\n", r);
}