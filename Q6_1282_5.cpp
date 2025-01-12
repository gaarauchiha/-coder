#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <assert.h>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <list>
#include <bitset>

using namespace std;
typedef long long ll;
#define Fi first
#define Se second
#define pb(x) push_back(x)
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0;i<n;i++)
#define all(x) (x).begin(), (x).end()
typedef tuple<int, int, int> t3;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef long double ldouble;
typedef pair<double, double> pdd;

vector <pii> E[410];
int p[410];
int Find(int x){return p[x] == x ? x : p[x] = Find(p[x]); }
int dead[410];
int al[410];
int chk[410];
int chke[100010];

int can[410];
int dead2[410][410], al2[410][410];

void solve() {
	int n, m; scanf("%d%d", &n, &m);
	for(int i=1;i<=n;i++)p[i] = i;
	rep(i, m){
		int x, y; scanf("%d%d", &x, &y);
		E[x].pb(pii(i+1, y));
		E[y].pb(pii(i+1, x));
		p[Find(x)] = Find(y);
	}
	int ans = 0;
	int cnt = 0;
	map <int, int> M;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++) dead[j] = m + 10;
		for(int j=1;j<=n;j++) al[j] = 0;
		for(int j=1;j<=n;j++) chk[j] = 0;
		for(int j=1;j<=m;j++) chke[j] = 0;
		al[i] = m + 10;
		priority_queue <pii> pq; pq.push(pii(al[i], i));
		int ok = 1;
		while(!pq.empty()){
			pii t = pq.top(); pq.pop();
			if(chk[t.Se]) continue;
			chk[t.Se] = 1;
			for(pii e : E[t.Se]) {
				if(chke[e.Fi]) continue;
				chke[e.Fi] = 1;
				if(e.Fi > t.Fi){
					dead[e.Se] = min(dead[e.Se], e.Fi);
					if(dead[e.Se] < al[e.Se]) ok = 0;
				}
				else {
					if(dead[e.Se] < e.Fi || al[e.Se] > e.Fi) ok = 0;
					else dead[e.Se] = al[e.Se] = e.Fi, pq.push(pii(al[e.Se], e.Se));
				}
			}
		}
		if(al[i] < m + 10) ok = 0;
		if(ok) {
			for(int j=1;j<=n;j++) dead2[i][j] = dead[j];
			for(int j=1;j<=n;j++) al2[i][j] = al[j];
			can[i] = 1;
			M[Find(i)]++;
			++cnt;
		}
	}
	for(int i=1;i<=n;i++) if(can[i]) for(int j=1;j<i;j++) if(can[j] && Find(i) == Find(j)) {
		int ok = 1;
		for(int k=1;k<=n;k++) if(min(dead2[i][k], dead2[j][k]) < max(al2[i][k], al2[j][k])){
			ok = 0;
		}
		if(ok) ans++;
	}
	int C = cnt * cnt;
	for(auto e : M) C -= e.Se * e.Se;
	printf("%d\n", ans + C / 2);
}

int main(){
	int Tc = 1; 
	for(int tc=1;tc<=Tc;tc++){
		solve();
	}
	return 0;
};