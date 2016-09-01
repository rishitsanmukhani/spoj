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

#define MOD (int(5e6))
const int maxn=11000;
const int maxk=51;

//Use one based indexing
class FenwickTree{
public:
  vector<int> ft;
  int n;
  FenwickTree(int _n=maxn){
    n=_n;
    ft.assign(n+1,0);
  }
  int rsq(int b){
    int sum=0;
    for(;b;b-=LSOne(b)){
      sum += ft[b];
      if(sum>=MOD)sum%=MOD;
    }
    return sum;
  }
  int rsq(int a,int b){
    return rsq(b)-(a==1 ?0:rsq(a-1));
  }
  void adjust(int k,int v){
    for(;k<sz(ft);k+=LSOne(k)){
      ft[k]+=v;
      if(ft[k]>=MOD)ft[k]%=MOD;
    }
  }
  void clear(){
    ft.assign(n,0);
  }
};

FenwickTree f[maxk];
vi v,_v;
int n,k,tmp;
map<int,int> m;
void compress(){
  sort(_v.begin(),_v.end());
  for(int i=0;i<n;i++){
    m[_v[i]]=i+1;  
  }
  for(int i=0;i<n;i++){
    v[i]=m[v[i]];
  }
}
int main(){
  icin(n);icin(k);
  v.resize(n);
  for(int i=0;i<n;i++){
    icin(v[i]);
    _v.pb(v[i]);
  }
  if(k==1){
    cout<<n<<endl;
    return 0;
  }
  compress();
  int ans=0,tot;
  for(int i=0;i<n;++i){
    tmp=v[i];
    for(int j=k;j>=2;--j){
      tot=f[j-1].rsq(tmp-1);
      if(j==k)ans +=tot;
      if(ans>=MOD)ans%=MOD;
      f[j].adjust(tmp,tot);
    }
    f[1].adjust(tmp,1);
  }
  printf("%d\n",ans);
  return 0;
}