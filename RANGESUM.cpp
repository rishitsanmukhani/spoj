#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair
#define sz(x) ((int)x.size())
#define LSOne(x) (x & -x)
typedef long long LL;
typedef vector<int> vi;
typedef pair<int,int> pii;

//Use one based indexing
class FenwickTree{
public:
  vector<LL> ft;
  int n;
  FenwickTree(int _n){
    n=_n;
    ft.assign(n+1,0);
  }
  LL rsq(int b){
    LL sum=0;
    for(;b;b-=LSOne(b))sum += ft[b];
    return sum;
  }
  LL rsq(int a,int b){
    return rsq(b)-(a==1 ?0:rsq(a-1));
  }
  void adjust(int k,LL v){
    for(;k<sz(ft);k+=LSOne(k)) ft[k]+=v;
  }
  void clear(){
    ft.assign(n,0);
  }
};

const int maxn=int(1e6)+1;
FenwickTree f(maxn);

int main(){
  int n;
  icin(n);
  int start_idx=int(1e6)-int(1e5),a;
  for(int i=1;i<=n;i++){
    icin(a);
    f.adjust(start_idx+i,a);
  }
  int q,l,r;
  icin(q);
  for(int i=0;i<q;i++){
    icin(a);
    if(a==1){
      icin(l);icin(r);
      printf("%lld\n",f.rsq(start_idx+l,start_idx+r));
    }
    else{
      icin(a);
      f.adjust(start_idx,a);
      start_idx--;
    }
  }
  return 0;
}