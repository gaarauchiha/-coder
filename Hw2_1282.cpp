#include <bits/stdc++.h>
using namespace std;

int main()
{
  static char s[500010];
  scanf("%s",s);
  int n=strlen(s);
  static int a[500000];
  for(int i=0;i<n;i++){
    a[i]=s[n-i-1]-'0';
  }
  int L=-1,R=10000000;
  while(L+1<R){
    int D=(L+R)/2;
    int d=D;
    int q=0;
    bool F=0;
    for(int i=0;i<n;i++){
      int g=a[i]-q;
      if(g>d){
	F=1;
	break;
      }
      int d2=g+(d-g)/10*10;
      q=(d2-g)/10;
      d=d2;
    }
    if(F){
      L=D;
    }
    else{
      R=D;
    }
  }
  printf("%d\n",(R+8)/9);
  return 0;
}