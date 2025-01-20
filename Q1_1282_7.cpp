#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

//not a multiset
//find_by_order(k) -> itr of k-th(0-based) element
//order_of_key(k) -> index of lower_bound(k)
using ordered_set=tree<
int,
null_type,
less<int>,
rb_tree_tag,
tree_order_statistics_node_update>;


//https://codeforces.com/blog/entry/62393
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const {
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}

	size_t operator()(pair<int,int> x) const {
		return operator()(uint64_t(x.first)<<32|x.second);
	}
};

template<class t,class u>
using hash_table=gp_hash_table<t,u,custom_hash>;

//count が使えない
//find を，しようね！
//move コンストラクタがないのでマージテクで壊れる バカ
//value を null_type にすることで unordered_set が実現できる
//insert などの関数が存在する (ドキュメント，どこ？)
//https://gcc.gnu.org/onlinedocs/libstdc++/manual/policy_data_structures.html (長すぎ，HELP)

using ll=long long;
//#define int ll

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
#define si(x) int(x.size())
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
#ifdef LOCAL
void dmpr(ostream&os){os<<endl;}
template<class T,class... Args>
void dmpr(ostream&os,const T&t,const Args&... args){
	os<<t<<" ";
	dmpr(os,args...);
}
#define dmp2(...) dmpr(cerr,__LINE__,##__VA_ARGS__)
#else
#define dmp2(...) void(0)
#endif

using uint=unsigned;
using ull=unsigned long long;

template<class t,size_t n>
ostream& operator<<(ostream&os,const array<t,n>&a){
	return os<<vc<t>(all(a));
}

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

template<class t>
void print(t x,int suc=1){
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

pi readpi(int off=0){
	int a,b;cin>>a>>b;
	return pi(a+off,b+off);
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
	cout<<"YES"<<"\n";
	#else
	cout<<"Yes"<<"\n";
	#endif
	if(ex)exit(0);
}
void no(bool ex=true){
	#ifdef CAPITAL
	cout<<"NO"<<"\n";
	#else
	cout<<"No"<<"\n";
	#endif
	if(ex)exit(0);
}
void possible(bool ex=true){
	#ifdef CAPITAL
	cout<<"POSSIBLE"<<"\n";
	#else
	cout<<"Possible"<<"\n";
	#endif
	if(ex)exit(0);
}
void impossible(bool ex=true){
	#ifdef CAPITAL
	cout<<"IMPOSSIBLE"<<"\n";
	#else
	cout<<"Impossible"<<"\n";
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
int botbit(signed a){
	return a==0?32:__builtin_ctz(a);
}
int botbit(ll a){
	return a==0?64:__builtin_ctzll(a);
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
ll mask(int i){
	return (ll(1)<<i)-1;
}

bool inc(int a,int b,int c){
	return a<=b&&b<=c;
}

template<class t> void mkuni(vc<t>&v){
	sort(all(v));
	v.erase(unique(all(v)),v.ed);
}

ll rand_int(ll l, ll r) { //[l, r]
	#ifdef LOCAL
	static mt19937_64 gen;
	#else
	static mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
	#endif
	return uniform_int_distribution<ll>(l, r)(gen);
}

template<class t>
void myshuffle(vc<t>&a){
	rep(i,si(a))swap(a[i],a[rand_int(0,i)]);
}

template<class t>
int lwb(const vc<t>&v,const t&a){
	return lower_bound(all(v),a)-v.bg;
}

const int nmax=200010;

int n;
struct Rook{
	int x,y,i,a,b;
	bool operator<(const Rook&r)const{return x<r.x;}
};
Rook z[nmax];

using P=pair<ll,ll>;

hash_table<pi,P> memo;

int lf[2][nmax],rt[2][nmax];
int w[2]{1,-1};

int getdist(const Rook&a,const Rook&b){
	return abs(a.x-b.x)+abs(a.y-b.y);
}

P slv(int l,int r,int bot,int top){
	pi key(l,r);
	{
		auto itr=memo.find(key);
		if(itr!=memo.ed)return itr->b;
	}
	
	int tar[2]{bot,top};
	rep(k,2){
		int i=l,j=r;
		if(i>0&&z[i-1].b+w[k]==tar[0]){
			i=lf[k][i-1];
		}
		if(j+1<n&&tar[1]+w[k]==z[j+1].b){
			j=rt[k][j+1];
		}
		if(pi(i,j)!=pi(l,r)){
			dmp2(l,r,i,j);
			P res=slv(i,j,min({bot,z[i].b,z[j].b}),max({top,z[i].b,z[j].b}));
			ll a=infLL,b=infLL;
			int lc=l-i,rc=j-r;
			if(lc&&rc){
				int base=getdist(z[i],z[j])-lc-rc;
				a=min(getdist(z[j],z[l])+res.a,getdist(z[i],z[l])+res.b)+base;
				b=min(getdist(z[j],z[r])+res.a,getdist(z[i],z[r])+res.b)+base;
			}else if(lc){
				a=getdist(z[i],z[l])-lc+res.a;
				b=getdist(z[i],z[r])-lc+res.a;
			}else if(rc){
				a=getdist(z[j],z[l])-rc+res.b;
				b=getdist(z[j],z[r])-rc+res.b;
			}else assert(0);
			return memo[key]=P(a,b);
		}
		swap(tar[0],tar[1]);
	}
	
	return memo[key]=P(0,0);
}

signed main(){
	cin.tie(0);
	ios::sync_with_stdio(0);
	cout<<fixed<<setprecision(20);
	
	cin>>n;
	rep(i,n){
		cin>>z[i].x>>z[i].y;
		z[i].i=i;
	}
	sort(z,z+n);
	vi xs(n),ys(n);
	rep(i,n){
		xs[i]=z[i].x;
		ys[i]=z[i].y;
	}
	sort(all(xs));
	sort(all(ys));
	rep(i,n){
		z[i].a=lwb(xs,z[i].x);
		z[i].b=lwb(ys,z[i].y);
	}
	
	rep(k,2){
		rep(i,n){
			lf[k][i]=i;
			if(i>0&&z[i-1].b+w[k]==z[i].b)
				lf[k][i]=lf[k][i-1];
		}
		per(i,n){
			rt[k][i]=i;
			if(i+1<n&&z[i].b+w[k]==z[i+1].b)
				rt[k][i]=rt[k][i+1];
		}
	}
	
	vc<ll> ans(n);
	rep(i,n)ans[z[i].i]=slv(i,i,z[i].b,z[i].b).a;
	for(auto v:ans)print(v);
}
