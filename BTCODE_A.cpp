#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
//Greatest Common Divisor
LL gcd(LL a,LL b){
  LL tmp;
  while(b){
    tmp=a%b;
    a=b;
    b=tmp;
  }
  return a;
}
LL xs, ys, xd, yd;
int main(){
  int T;
  cin>>T;
  while(T--){
    cin>>xs>>ys>>xd>>yd;
    xs = abs(xs);
    ys = abs(ys);
    xd = abs(xd);
    yd = abs(yd);

    LL gs = gcd(xs, ys);
    LL gd = gcd(xd, yd);

    while(gs>0 && gs<gd)
      gs *= 2;
    if(gs==gd){
      printf("YES\n");
    }
    else{
      printf("NO\n");
    }
  }
  return 0;
}