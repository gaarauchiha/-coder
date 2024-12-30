#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pr;
const int mod=998244353;
int n,q,fa[200005],loop[200005],ANS,d[200005],p[200005][20],dis[200005],sz[200005];
ll ans;
struct E{
	int to,val;
};
vector<E> g[200005];
int gf(int x){
	return x==fa[x]?x:fa[x]=gf(fa[x]);
}
int LCA(int x,int y){
	if(d[x]<d[y])swap(x,y);
	for(int i=17;i>=0;i--)if(d[x]-(1<<i)>=d[y])x=p[x][i];
	if(x==y)return x;
	for(int i=17;i>=0;i--)if(p[x][i]^p[y][i])x=p[x][i],y=p[y][i];
	return p[x][0];
}
int Dis(int x,int y){
	return (dis[y]-dis[x]+n)%n;
}
void dfs(int x,int fa,int dep,int ds){
	p[x][0]=fa,d[x]=dep,dis[x]=ds;
	for(int i=1;i<=17;i++)p[x][i]=p[p[x][i-1]][i-1];
	for(E i:g[x]){
		int y=i.to;
		if(y==fa)continue;
		dfs(y,x,dep+1,(ds+i.val)%n);
	}
}
void Add(int x,int y,int dif){
	if(dif==0)dif=n;
	//cout<<x<<' '<<y<<' '<<dif<<'\n';
	int fx=gf(x),fy=gf(y);
	if(fx!=fy){
		if(sz[fx]>sz[fy]){
			swap(fx,fy);
			swap(x,y);
			dif=(n-dif)%n;
		}
		//x合到y上 
		ans-=loop[fx];
		ans-=loop[fy];
		fa[fx]=fy;
		sz[fy]+=sz[fx];
		loop[fy]=__gcd(loop[fy],loop[fx]);
		ans+=loop[fy];
		g[x].push_back({y,dif});
		g[y].push_back({x,n-dif});
		dfs(x,y,d[y]+1,(dis[y]+n-dif)%n);
		return ;
	}
	int w=Dis(x,y);
	//cout<<w<<'\n';
	int o=((w-dif)%loop[fx]+loop[fx])%loop[fx];
	if(o==0)o=loop[fx];
	ans-=loop[fx];
	loop[fx]=__gcd(loop[fx],o);
	ans+=loop[fx];
}
int main(){
	cin>>n>>q;
	for(int i=0;i<n;i++)fa[i]=i,loop[i]=n,sz[i]=1;
	ans=1ll*n*n;
	for(int i=0,a,b,c,d;i<q;i++){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		int x=(a-b+n)%n,y=(c-d+n)%n;
		Add(x,y,(c-a+n)%n);
		cout<<ans<<'\n';
	}
}
