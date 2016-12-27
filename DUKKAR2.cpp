#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)

typedef long long LL;

const int mod = (int(1e9)+7);
int mul(int a, int b){
  return (LL(a)*b)%mod;
}
int add(int a, int b){
  return (a+b)%mod;
}
int p, k;
vector<int> d;
vector<vector<int> > dp;
int main(){
  int T;
  icin(T);
  while(T--){
    icin(p);
    icin(k);
    d.resize(k);
    for(int i=0;i<k;i++)
      icin(d[i]);
    dp.assign(k,vector<int>(2, 0));
    dp[0][0] = ((LL(d[0])*(d[0]+1))/2)%mod;
    dp[0][1] = (d[0]+1)%mod;

    int tmp=1;
    int pp = ((LL(p)*(p+1))/2)%mod;
    for(int i=1;i<k;i++){
      tmp = mul(tmp, pp);
      dp[i][0] = mul(((LL(d[i])*(d[i]+1))/2)%mod, tmp);
      dp[i][1] = mul(d[i]+1, add(dp[i-1][0], dp[i-1][1]));
    }
    int val1 = add(dp[k-1][0], dp[k-1][1]);
    tmp=1;
    for(int i=0;i<k;i++){
      tmp = mul(tmp, d[i]+1);
    }
    val1 = (val1 - tmp + mod)%mod;

    int nn=0;
    tmp=1;
    for(int i=0;i<k;i++){
      nn = add(nn, mul(d[i], tmp));
      tmp = mul(tmp, p);
    }
    nn = ((LL(nn)*(nn+1))/2)%mod;
    printf("%d\n", (nn - val1 + mod)%mod);
  }
  return 0;
}