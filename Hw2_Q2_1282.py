# -*- coding: utf-8 -*-
"""
Created on Mon Dec 30 03:31:20 2024

"""
class PotentialUnionFind():
    def __init__(self, n, inf = 10 ** 18):
        self.n = n
        self.PA = [-1] * n
        self.pot = [0] * n
        self.inf = inf
    def root(self, a):
        a0 = a
        s = 0
        L1 = []
        while self.PA[a] >= 0:
            L1.append((a, self.pot[a]))
            s += self.pot[a]
            a = self.PA[a]
        pa = a
        a = a0
        L2 = []
        while a != pa:
            L2.append((a, self.pot[a]))
            self.pot[a], s = s, s - self.pot[a]
            self.PA[a], a = pa, self.PA[a]
        return pa
    def dist(self, a, b):
        ra = self.root(a)
        rb = self.root(b)
        if ra == rb:
            return self.pot[b] - self.pot[a]
        return self.inf
    def unite(self, a, b, d):
        ra, rb = self.root(a), self.root(b)
        if ra != rb:
            if self.PA[rb] >= self.PA[ra]:
                self.PA[ra] += self.PA[rb]
                self.pot[rb] = self.pot[a] + d - self.pot[b]
                self.PA[rb] = ra
            else:
                self.PA[rb] += self.PA[ra]
                self.pot[ra] = self.pot[b] - d - self.pot[a]
                self.PA[ra] = rb
    def size(self, a):
        return -self.PA[self.root(a)]
    def groups(self):
        G = [[] for _ in range(self.n)]
        for i in range(self.n):
            G[self.root(i)].append(i)
        return [g for g in G if g]
    def groups_index(self):
        G = [[] for _ in range(self.n)]
        for i in range(self.n):
            G[self.root(i)].append(i)
        cnt = 0
        GG = []
        I = [-1] * self.n
        for i in range(self.n):
            if G[i]:
                GG.append(G[i])
                I[i] = cnt
                cnt += 1
        return GG, I
    def group_size(self):
        G = [[] for _ in range(self.n)]
        for i in range(self.n):
            G[self.root(i)].append(i)
        return [len(g) for g in G if g]

import sys
input = lambda: sys.stdin.readline().rstrip()
from math import gcd
N, M = map(int, input().split())
L = [N] * N
ans = N * N
uf = PotentialUnionFind(N)
for _ in range(M):
    a, b, c, d = map(int, input().split())
    x = (b - a) % N
    y = (d - c) % N
    z = (c - a) % N
    rx = uf.root(x)
    ry = uf.root(y)
    if rx == ry:
        w = (z - uf.dist(x, y)) % N
        ans -= L[rx]
        L[rx] = gcd(L[rx], w)
        ans += L[rx]
    else:
        ans -= L[rx]
        ans -= L[ry]
        g = gcd(L[rx], L[ry])
        uf.unite(x, y, z)
        r = uf.root(x)
        L[r] = g
        ans += L[r]
    
    print(ans)
