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
FenwickTree ft(int(1e5)+1);
unordered_map<string,int> m;
vector<string> v;

int main(){
  int t;
  icin(t);
  while(t--){
    ft.clear();
    m.clear();
    v.clear();
    int n;
    icin(n);
    v.resize(n);
    for(int i=0;i<n;i++)cin>>v[i];
    string s;
    for(int i=1;i<=n;i++){
      cin>>s;
      m[s]=i;
    }
    LL ans=0;
    int num;
    for(int i=n-1;i>=0;i--){
      num=m[v[i]];
      ans += ft.rsq(1,num-1);
      ft.adjust(num,1);
    }
    cout<<ans<<endl;
  }
}