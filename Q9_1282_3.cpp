#include <bits/stdc++.h>
using namespace std;
#define N 2010
int n;
int ai[N];
vector <int> bi[N], bf[N];
int vis[N];
int in[N];
struct comp
{
    int operator() (int a, int b) {return ai[a] < ai[b];}
};
priority_queue <int, vector <int>, comp> H;
void dfs(int t)
{
    vis[t] = 1;
    for (int i = 0; i < bi[t].size(); ++ i)
        if (!vis[bi[t][i]])
        {
            bf[t].push_back(bi[t][i]);
            in[bi[t][i]] ++;
            dfs(bi[t][i]);
        }
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> ai[i];
    sort(ai + 1, ai + n + 1);
    for (int i = 1; i <= n; ++ i)
        for (int j = i + 1; j <= n; ++ j)
            if (__gcd(ai[i], ai[j]) != 1)
                bi[i].push_back(j),
                bi[j].push_back(i);

    for (int i = 1; i <= n; ++ i)
        if (!vis[i]) dfs(i);

    for (int i = 1; i <= n; ++ i)
        if (!in[i]) H.push(i);
    while (!H.empty())
    {
        int hd = H.top(); H.pop();
        cout << ai[hd] << " ";
        for (int i = 0; i < bf[hd].size(); ++ i)
        {
            in[bf[hd][i]] --;
            if (!in[bf[hd][i]]) H.push(bf[hd][i]);
        }
    }
}
