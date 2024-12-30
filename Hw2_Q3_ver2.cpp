#include<bits/stdc++.h>
using namespace std;
const int N=2005,M=998244353;
int t,n,i,k,j;
long long m,f[N],inv[N],g[N],a[N],f1[N][N],f2[N][N],C[N][N];
int main()
{
	scanf("%d %lld",&n,&m);
	for(i=1;i<=n;++i)
		scanf("%lld",&a[i]);
	inv[1]=1;
	for(i=2;i<=n+1;++i)
		inv[i]=inv[M%i]*(M-M/i)%M;
	f[0]=1;
	f2[0][0]=f1[0][0]=1;
	C[0][0]=1;
	for(i=1;i<=n;++i)
	{
		C[i][0]=C[i][i]=1;
		for(j=1;j<=i;++j)
		{
			f1[i][j]=(f1[i-1][j-1]+f1[i-1][j]*(i-1))%M;
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%M;
		}
	}
	for(i=1;i<=n;++i)
		for(j=1;j<=i;++j)
			f2[i][j]=(f2[i-1][j-1]+f2[i-1][j]*j)%M;
	for(i=n;i>=1;--i)
	{
		for(j=0;j<=n-i;++j)
			g[j]=f[j];
		for(j=0;j<=n-i;++j)
			g[j+1]+=f[j]*inv[j+1];
		for(j=0;j<=n-i+1;++j)
			g[j]%=M;
		long long s=0,su=1;
		for(j=0;j<=n-i+1;++j)
		{
			s=(s+su*g[j])%M;
			su=su*((m-j)%M)%M;
		}
		m/=a[i];
		if(a[i]!=1)
		{
			long long u=1;
			for(j=0;j<=n-i+1;++j)
				f[j]=g[j];
			for(j=0;j<=n-i+1;++j)
				g[j]=0;
			for(j=0;j<=n-i+1;++j)
				for(k=0;k<=j;++k)
					g[k]=(g[k]+f[j]*f1[j][k]*(j-k&1?-1:1))%M;
			for(j=0;j<=n-i+1;++j)
				f[j]=0;
			for(j=0;j<=n-i+1;++j)
			{
				u=1;
				for(k=0;k<=j;++k)
				{
					f[k]=(f[k]+(j-k&1?-1:1)*C[j][k]*g[j]%M*u)%M;
					u=u*a[i]%M;
				}
			}
			for(j=0;j<=n-i+1;++j)
				f[j]=-f[j];
			for(j=0;j<=n-i+1;++j)
				g[j]=0;
			for(j=0;j<=n-i+1;++j)
				for(k=0;k<=j;++k)
					g[k]=(g[k]+f[j]*f2[j][k])%M;
			for(j=0;j<=n-i+1;++j)
				f[j]=g[j];
		}
		if(a[i]==1)
		{
			for(j=0;j<=n-i+1;++j)
				f[j]=-g[j];
			for(j=n-i+1;j>=1;--j)
				f[j-1]=(f[j-1]-f[j]*j)%M;
		}
		f[0]=(f[0]+s)%M;
	}
	for(j=0;j<=n;++j)
		g[j]=f[j];
	for(j=0;j<=n;++j)
		g[j+1]+=f[j]*inv[j+1];
	for(j=0;j<=n-i+1;++j)
		g[j]%=M;
	long long s=0,su=1;
	for(j=0;j<=n+1;++j)
	{
		s=(s+su*g[j])%M;
		su=su*((m-j)%M)%M;
	}
	cout<<((s-f[0])%M+M)%M;
}