#include <bits/stdc++.h>
using namespace std;

using ll=long long;
#define int ll

#define rng(i,a,b) for(int i=int(a);i<int(b);i++)
#define rep(i,b) rng(i,0,b)
#define gnr(i,a,b) for(int i=int(b)-1;i>=int(a);i--)
#define per(i,b) gnr(i,0,b)
#define pb push_back
#define eb emplace_back
#define a first
#define b second
#define bg begin()
#define ed end()
#define all(x) x.bg,x.ed
#ifdef LOCAL
#define dmp(x) cerr<<__LINE__<<" "<<#x<<" "<<x<<endl
#else
#define dmp(x) void(0)
#endif

template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

template<class t> using vc=vector<t>;
template<class t> using vvc=vc<vc<t>>;

using pi=pair<int,int>;
using vi=vc<int>;

template<class t,class u>
ostream& operator<<(ostream& os,const pair<t,u>& p){
	return os<<"{"<<p.a<<","<<p.b<<"}";
}

template<class t> ostream& operator<<(ostream& os,const vc<t>& v){
	os<<"{";
	for(auto e:v)os<<e<<",";
	return os<<"}";
}

#define mp make_pair
#define mt make_tuple
#define one(x) memset(x,-1,sizeof(x))
#define zero(x) memset(x,0,sizeof(x))

using uint=unsigned;
using ull=unsigned long long;

template<int i,class T>
void print_tuple(ostream&,const T&){
}

template<int i,class T,class H,class ...Args>
void print_tuple(ostream&os,const T&t){
	if(i)os<<",";
	os<<get<i>(t);
	print_tuple<i+1,T,Args...>(os,t);
}

template<class ...Args>
ostream& operator<<(ostream&os,const tuple<Args...>&t){
	os<<"{";
	print_tuple<0,tuple<Args...>,Args...>(os,t);
	return os<<"}";
}

void print(ll x,int suc=1){
	cout<<x;
	if(suc==1)
		cout<<"\n";
	if(suc==2)
		cout<<" ";
}

ll read(){
	ll i;
	cin>>i;
	return i;
}

vi readvi(int n,int off=0){
	vi v(n);
	rep(i,n)v[i]=read()+off;
	return v;
}

template<class T>
void print(const vector<T>&v,int suc=1){
	rep(i,v.size())
		print(v[i],i==int(v.size())-1?suc:2);
}

string readString(){
	string s;
	cin>>s;
	return s;
}

template<class T>
T sq(const T& t){
	return t*t;
}

//#define CAPITAL
void yes(bool ex=true){
	#ifdef CAPITAL
	cout<<"YES"<<endl;
	#else
	cout<<"Yes"<<endl;
	#endif
	if(ex)exit(0);
}
void no(bool ex=true){
	#ifdef CAPITAL
	cout<<"NO"<<endl;
	#else
	cout<<"No"<<endl;
	#endif
	if(ex)exit(0);
}

constexpr ll ten(int n){
	return n==0?1:ten(n-1)*10;
}

const ll infLL=LLONG_MAX/3;

#ifdef int
const int inf=infLL;
#else
const int inf=INT_MAX/2-100;
#endif

int topbit(signed t){
	return t==0?-1:31-__builtin_clz(t);
}
int topbit(ll t){
	return t==0?-1:63-__builtin_clzll(t);
}
int popcount(signed t){
	return __builtin_popcount(t);
}
int popcount(ll t){
	return __builtin_popcountll(t);
}
bool ispow2(int i){
	return i&&(i&-i)==i;
}

bool inc(int a,int b,int c){
	return a<=b&&b<=c;
}

template<class t> void mkuni(vc<t>&v){
	sort(all(v));
	v.erase(unique(all(v)),v.ed);
}

ll rand_int(ll l, ll r) { //[l, r]
    static random_device rd;
    static mt19937_64 gen(rd());
    return uniform_int_distribution<ll>(l, r)(gen);
}

int mul(int a,int b){
	if(b==0)return 0;
	else if(a<=inf/b)return a*b;
	else return inf;
}

int myp(int a,int b){
	int res=1;
	while(b){
		if(b%2)res=mul(res,a);
		a=mul(a,a);
		b>>=1;
	}
	return res;
}

const int nmax=200010;
int L;
int ch[nmax][2];

struct waf{
	vi head,tail;
	int hs,ts,al,mx;
	waf():head(1,1),tail(1,1),hs(0),ts(0),al(0),mx(0){}
	waf(const vi&h,const vi&t,int hhs,int tts,int aal,int mmx):
		head(h),tail(t),hs(hhs),ts(tts),al(aal),mx(mmx){}
	void upd(int to){
		int w=myp(L,to-mx);
		if(w==1)return;
		vi h(hs/w+1);
		rep(i,hs+1)if(i==0||i>=w)h[i/w]+=head[i];
		vi t(ts/w+1);
		rep(i,ts+1)if(i==0||i>=w)t[i/w]+=tail[i];
		swap(h,head);
		swap(t,tail);
		hs/=w;
		ts/=w;
		if(al!=-1)al/=w;
		if(mx&&al==0)al=-1;
		mx=to;
	}	
};

int ans;

waf dfs(int v,const vi&arr){
	dmp(v);
	if(v==-1)
		return waf();
	waf a=dfs(ch[v][0],arr);
	waf b=dfs(ch[v][1],arr);
	a.upd(arr[v]);
	b.upd(arr[v]);
	vi p=a.tail;
	per(i,a.ts)p[i]+=p[i+1];
	rep(i,b.hs+1){
		int need=max(int(0),L-1-i);
		if(need<=a.ts)
			ans+=p[need]*b.head[i];
	}
	
	ans++;
	
	vi h=a.head,t=b.tail;
	int hs=a.hs,ts=b.ts,al=-1,mx=arr[v];
	if(a.al!=-1){
		assert(a.hs==a.al);
		hs+=1+b.hs;
		h.resize(hs+1);
		rep(i,b.hs+1)
			h[a.al+1+i]+=b.head[i];
	}
	
	if(b.al!=-1){
		assert(b.ts==b.al);
		ts+=1+a.ts;
		t.resize(ts+1);
		rep(i,a.ts+1)
			t[b.al+1+i]+=a.tail[i];
	}
	if(a.al!=-1&&b.al!=-1)
		al=a.al+1+b.al;
	return waf(h,t,hs,ts,al,mx);
}

signed main(){
	cin.tie(0);
	ios::sync_with_stdio(0);
	cout<<fixed<<setprecision(20);
	
	int n;cin>>n;
	cin>>L;
	vi a;
	if(n==-1){
		n=200000;
		a=vi(n,1);
		iota(all(a),1);
	}else{
		a=readvi(n);
	}
	vc<pi> w(n);
	rep(i,n)
		w[i]=pi(a[i],rand_int(0,ten(9)));
	vi idx;
	vi par(n,-1);
	rep(i,n){
		int last=-1;
		while(idx.size()&&w[idx.back()]<w[i]){
			last=idx.back();
			idx.pop_back();
		}
		if(last!=-1)
			par[last]=i;
		if(idx.size())
			par[i]=idx.back();
		idx.pb(i);
	}
	one(ch);
	int root=-1;
	rep(i,n)if(par[i]!=-1)
		ch[par[i]][par[i]<i]=i;
	else
		root=i;
	dfs(root,a);
	cout<<ans<<endl;
}
