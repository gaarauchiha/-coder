#include <bits/stdc++.h>

using namespace std;

const int N = 300043;

int n, m;
set<int> g[N];
set<int> g2[N];

vector<int> res;

void euler(int x)
{
    while(!g2[x].empty())
    {
        int y = *g2[x].begin();
        g2[x].erase(y);
        g2[y].erase(x);
        euler(y);
    }
    res.push_back(x);
}

bool check(int c)
{
    for(int i = 1; i <= n; i++)
        g2[i] = g[i];
    res = vector<int>();
    euler(c);
    int curm = 0;
    for(int i = 1; i <= n; i++)
        curm += g[i].size();
    for(int i = 1; i <= n; i++)
        g2[i] = g[i];
    for(int i = 1; i < res.size(); i++)
    {
        int x = res[i - 1];
        int y = res[i];
        if(g2[x].count(y) != 1)
            return false;
        g2[x].erase(y);
        g2[y].erase(x);
    }
    return curm / 2 + 1 == res.size();    
}

int main()
{
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        g[x].insert(y);
        g[y].insert(x);
    }
    for(int i = 1; i <= n; i++)
    {
        set<int> pr = g[i];
        set<int> diff;
        for(auto x : pr)
            if(g[x].size() % 2 == 1)
            {
                g[i].erase(x);
                g[x].erase(i);
                diff.insert(x);
            }
        if(check(i))
        {
            res.push_back(-1);
            for(auto x : diff)
            {
                res.push_back(x);
                res.push_back(i);
            }
            printf("%d\n", res.size());
            for(auto x : res) printf("%d ", x);
            puts("");
            exit(0);
        }
        for(auto x : pr)
        {
            if(g[i].count(x))
            {
                g[i].erase(x);
                g[x].erase(i);
                diff.insert(x);
            }
            else
            {
                g[i].insert(x);
                g[x].insert(i);
                diff.erase(x);
            }
            if(check(i))
            {
                res.push_back(-1);
                for(auto x : diff)
                {
                    res.push_back(x);
                    res.push_back(i);
                }
                printf("%d\n", res.size());
                for(auto x : res) printf("%d ", x);
                puts("");
                exit(0);
            }
            if(g[i].count(x))
            {
                g[i].erase(x);
                g[x].erase(i);
                diff.insert(x);
            }
            else
            {
                g[i].insert(x);
                g[x].insert(i);
                diff.erase(x);
            }
        }
        for(auto x : diff)
        {
            g[i].insert(x);
            g[x].insert(i);
        }
    }
    puts("0");
}