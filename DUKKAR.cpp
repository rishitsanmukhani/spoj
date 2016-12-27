#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;
int main(){
  int T;
  icin(T);
  while(T--){
    LL n, p;
    lcin(n);
    lcin(p);
    LL ans=1;
    LL tmp = n;
    while(tmp){
      ans *= ((tmp%p)+1);
      tmp /= p;
    }
    ans = (n+1)-ans;
    printf("%lld\n", ans);
  }
  return 0;
}