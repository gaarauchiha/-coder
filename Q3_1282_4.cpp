#include<bits/stdc++.h>
namespace ifzw{
#define ull unsigned ll 
#define ll long long
#define LL __int128
#define dd double
#define siz(A) ((int)A.size())
using namespace std;
char gc(){static char buf[1<<16],*s,*t;if(s==t){t=(s=buf)+fread(buf,1,1<<16,stdin);if(s==t)return EOF;}return *s++;}
ll read()
{
	char c;
	ll w=1;
	while((c=getchar())>'9'||c<'0')if(c=='-')w=-1;
	ll ans=c-'0';
	while((c=getchar())>='0'&&c<='9')ans=(ans<<1)+(ans<<3)+c-'0';
	return ans*w;
}
void pc(char c,int op)
{
	static char buf[1<<16],*s=buf,*t=buf+(1<<16);
	(op||((*s++=c)&&s==t))&&(fwrite(buf,1,s-buf,stdout),s=buf);
}
void wt(int x)
{
	if(x>9)wt(x/10);
	pc('0'+x%10,0);
}
void wts(int x,char op)
{
	if(x<0)pc('-',0),x=-x;
	wt(x);pc(op,0);
}
namespace ppprrr{const int xx=2,mod=2;ll ksm(ll a,ll b){return 0;}

ll jiec[xx],ni[xx];
ll C(ll n,ll m){return jiec[n]*ni[m]%mod*ni[n-m]%mod;}
void pre()
{
	jiec[0]=1;
	for(int i=1;i<xx;i++)jiec[i]=jiec[i-1]*i%mod;
	ni[xx-1]=ksm(jiec[xx-1],mod-2);
	for(int i=xx-2;i>=0;i--)ni[i]=ni[i+1]*(i+1)%mod;
}

int prim[xx],mn[xx],Cnt;
void pre(int n)
{
	for(int i=2;i<=n;i++)
	{
		if(!mn[i])mn[i]=i,prim[++Cnt]=i;
		for(int j=1;j<=Cnt;j++)
		{
			if(prim[j]*i>n)break;
			mn[i*prim[j]]=prim[j];
			if(i%prim[j]==0)break;
		}
	}
}
int yz[xx],tts;
void gyz(int x)
{
	tts=0,yz[++tts]=1;
	while(x!=1)
	{
		int M=mn[x],ct=0,ntt=tts;
		while(x%M==0)++ct,x/=M;
		for(int i=1,ty=1;(ty*=M),i<=ct;i++)
			for(int j=1;j<=ntt;j++)
				yz[++tts]=yz[j]*ty;
	}
}

int lb(int x){return x&-x;}
ll sum[xx];
void Add(int x,int y){for(;x<xx;x+=lb(x))sum[x]+=y;}
ll ask(int x){ll ans=0;for(;x;x-=lb(x))ans+=sum[x];return ans;}

void ad(int &a,int b){(a+=b)>=mod?a-=mod:0;}
void ad(int &a,ll b){(a=(a+b)%mod);}
int red(int x){return x>=mod?x-=mod:x;}

random_device R;
mt19937 G(218);
int rd(int l,int r){return uniform_int_distribution<int>(l,r)(G);}

}

ll gcd(ll a,ll b){return !b?a:gcd(b,a%b);}
const int xx=1e6+5,mod=998244353;

ll ksm(ll a,ll b=mod-2)
{
	ll ans=1;
	while(b)
	{
		if(b&1)ans*=a,ans%=mod;
		a*=a,a%=mod,b>>=1;
	}
	return ans;
}

#define Pr pair<int,int>
#define fi first
#define se second
int n,m,q,a[xx],b[xx];
int ct[xx],rt;
struct nod{int next,to;}e[xx<<1];
int cnt,h[xx];
void add(int x,int y){cnt++,e[cnt]={h[x],y},h[x]=cnt;}
int w[xx];
#define ii array<int,2>
multiset<ii>s;
void era(ii A)
{
	s.erase(s.find(A));
}
void ins(ii A)
{
	s.insert(A);
}
ii get(int x,int y)
{
	int cs=0;
	for(int i=h[x];i;i=e[i].next)if(e[i].to!=y)cs++;
	if(cs==0)return {w[x],x};
	if(cs>1)
	{
		era({w[x],x});
		ii ans=*s.begin();
		ins({w[x],x});
		return ans;
	}
	assert(cs==1);
	era({w[x],x});
	ii ans;
	for(int i=h[x];i;i=e[i].next)if(e[i].to!=y)ans=get(e[i].to,x);
	ins({w[x],x});
	return ans;
}
int mx[xx],siz[xx],is[xx],cur,lim;

void findc(int x,int y)
{
	siz[x]=is[x],mx[x]=0;
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y)continue;
		findc(e[i].to,x),siz[x]+=siz[e[i].to];
		mx[x]=max(mx[x],siz[e[i].to]);
	}
	mx[x]=max(mx[x],lim-siz[x]);
	if(!is[x])
	{
		if(!cur||mx[x]<mx[cur])cur=x;
	}
}
vector<int>v[xx],lf;
void down(int x,int y)
{
	if(is[x])lf.push_back(x);
	for(int i=h[x];i;i=e[i].next)
	{
		if(e[i].to==y)continue;
		down(e[i].to,x);
	}
}
struct no
{
	int i;
	bool operator<(const no&w)const{return siz(v[i])>siz(v[w.i]);}
};
multiset<no>as;
int main(){
	int T=read();
	while(T--)
	{
		n=read();
		memset(h,0,sizeof(h[0])*(n+1)),cnt=0;
		s.clear();
		for(int i=1;i<=n;i++)w[i]=read(),s.insert({w[i],i});
		for(int i=1;i<=n;i++)v[i].clear(),is[i]=0,siz[i]=mx[i]=0;
		cur=lim=0;
		for(int i=1;i<=n;i++)ct[i]=0;
		for(int i=1;i<n;i++)
		{
			int a=read(),b=read();
			ct[a]++,ct[b]++;
			add(a,b),add(b,a);
		}
		for(int i=1;i<=n;i++)
			if(ct[i]!=1)rt=i;
		int re=0;
		for(int i=1;i<=n;i++)re+=(ct[i]==1);
		for(int i=1;i<=n;i++)is[i]=0;
		vector<ii>an;
		if(re%2==0)
		{
			for(int i=1;i<=n;i++)if(ct[i]==1)is[i]=1;
		}
		else 
		{
			int tt=0;
			for(int i=1;i<=n;i++)if(ct[i]==1)is[i]=1,tt+=w[i];
			ii mn={(int)2e9,0};
			int A=0;
			for(int i=1;i<=n;i++)
			{
				if(ct[i]==1)
				{
					ii td=get(i,0);
					mn=min(mn,td);
					if(mn==td)A=i;
				}
			}
			is[A]=0;
			an.push_back({A,mn[1]});
		}
		lim=0;
		for(int i=1;i<=n;i++)lim+=is[i];
		findc(rt,0);
		as.clear();
		int nm=0;
		for(int i=h[cur];i;i=e[i].next)
		{
			lf.clear();
			down(e[i].to,cur);
			++nm,v[nm]=lf;
		}
		for(int i=1;i<=nm;i++)as.insert({i});
		while(siz(as))
		{
			if(siz(v[as.begin()->i])==0)as.erase(as.begin());
			else 
			{
				int L=as.begin()->i;
				as.erase(as.begin());
				int R=as.begin()->i;
				as.erase(as.begin());
				an.push_back({v[L].back(),v[R].back()});
				v[L].pop_back();
				v[R].pop_back();
				as.insert({L});
				as.insert({R});
			}
		}
		cout<<siz(an)<<"\n";
		for(auto it:an)cout<<it[0]<<" "<<it[1]<<"\n";
	}
	pc('1',1);
	return 0;
}



}signed main(){return ifzw::main();}