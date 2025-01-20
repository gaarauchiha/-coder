#include <bits/stdc++.h>
using namespace std;

vector<vector<int> > tree;

const int MAXN = 2100;

bool added[MAXN][MAXN];
bool killed[MAXN][MAXN];

vector<int> stuff[MAXN][MAXN];

int parv[MAXN][MAXN];
int depth[MAXN][MAXN];

vector<int> ord[MAXN];

void dfs(int i, int v, int p, int d){
	ord[i].push_back(v);
	parv[i][v] = p;
	depth[i][v] = d;
	for(int w : tree[v]){
		if(w == p) continue;
		dfs(i, w, v, d+1);
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	tree.resize(n);
	for(int i = 0; i < n-1; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		tree[a].push_back(b);
		tree[b].push_back(a);
	}
	for(int i = 0; i < n; i++){
		dfs(i, i, i, 0);
	}
	vector<pair<int,int> > add_edge;
	for(int i = 0; i < m; i++){
		int c, d;
		cin >> c >> d;
		c--; d--;
		add_edge.emplace_back(c, d);
	}
	int s = 0;
	while(s < add_edge.size()){
		int c = add_edge[s].first;
		int d = add_edge[s].second;
		s++;
		if(added[c][d]) continue;
		if(killed[c][d]) continue;
		added[c][d] = added[d][c] = true;
		{
			int x = d;
			while(x != c){
				if(x != d && added[c][x]){
					killed[c][d] = killed[d][c] = true;
					add_edge.emplace_back(x, d);
					break;
				}
				x = parv[c][x];
				if(x != c) stuff[c][x].push_back(d);
			}
			if(killed[c][d]) continue;
		}
		{
			int x = c;
			while(x != d){
				if(x != c && added[d][x]){
					killed[c][d] = killed[d][c] = true;
					add_edge.emplace_back(x, c);
					break;
				}
				x = parv[d][x];
				if(x != d) stuff[d][x].push_back(c);
			}
			if(killed[c][d]) continue;
		}
		for(int x : stuff[c][d]){
			if(killed[c][x]) continue;
			killed[c][x] = killed[x][c] = true;
			add_edge.emplace_back(d, x);
		}
		for(int x : stuff[d][c]){
			if(killed[d][x]) continue;
			killed[d][x] = killed[x][d] = true;
			add_edge.emplace_back(c, x);
		}
	}
	vector<pair<int,int> > good;
	vector<vector<int> > edges(n);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(added[i][j] && !killed[i][j]){
				edges[i].push_back(j);
				edges[j].push_back(i);
			}
		}
	}
	int res = 0;
	for(int s = 0; s < n; s++){
		vector<int> dp(n, 0);
		for(int v : ord[s]){
			if(v == s){
				dp[v] = 1;
			} else {
				for(int w : edges[v]){
					if(dp[w] && depth[v][w] + depth[w][s] == depth[v][s]){
						dp[v] = 1;
					}
				}
			}
		}
		int ans = 0;
		for(int v = 0; v < n; v++){
			if(dp[v] && v != s) ans++;
		}
		res += ans;
	}
	res /= 2;
	cout << res << '\n';
}