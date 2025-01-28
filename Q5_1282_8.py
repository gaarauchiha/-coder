for _ in range(int(input())):
  n,q=map(int,input().split())
  g=[[0]*1001 for _ in range(1001)]
  for _ in range(n):
    h,w=map(int,input().split())
    g[h][w]+=w*h
  for i in range(1001):
    for j in range(1001):
      if i > 0: g[i][j]+=g[i-1][j]
      if j > 0: g[i][j]+=g[i][j-1]
      if i>0 and j > 0: g[i][j]-=g[i-1][j-1]
  for _ in range(q):
    a,b,c,d=map(int,input().split())
    c-=1
    d-=1
    print(g[c][d]-g[c][b]-g[a][d]+g[a][b])
