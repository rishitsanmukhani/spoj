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

#define trace1(x) cerr<<#x<<"->"<<x<<endl
#define trace2(x, y)  cerr<<#x<<"->"<<x<<"\t"<<#y<<"\t"<<y<<endl
#define trace3(x, y, z) cerr<<#x<<"->"<<x<<"\t"<<#y<<"->"<<y<<"\t"<<#z<<"->"<<z<<endl

//Use one based indexing
class FenwickTree{
public:
  vector<int> ft;
  int n;
  FenwickTree(int _n){
    n=_n;
    ft.assign(n+1,0);
  }
  int rsq(int b){
    int sum=0;
    for(;b;b-=LSOne(b))sum += ft[b];
    return sum;
  }
  int rsq(int a,int b){
    return rsq(b)-(a==1 ?0:rsq(a-1));
  }
  void adjust(int k,int v){
    for(;k<sz(ft);k+=LSOne(k)) ft[k]+=v;
  }
  void clear(){
    ft.assign(n,0);
  }
};
FenwickTree ft(int(1e5)+1);
vi v;
int n;

int getIndex(int &s,int ecells_req){
  int ecells=(n-s+1-ft.rsq(s,n));
  if(ecells<ecells_req){
    s=1;
    ecells_req -= ecells;
    ecells=(n-ft.rsq(1,n));
    if(ecells<ecells_req) ecells_req = ecells_req%ecells;
    if(ecells_req==0)ecells_req=ecells;
  }
  int a=s,b=n,m;
  while(1){
    m=(a+b)>>1;
    ecells=(m-s+1-ft.rsq(s,m));
    if(ecells>ecells_req)b=m-1;
    else if(ecells<ecells_req)a=m+1;
    else{
      b=m;
      if(v[b]==-1)break;
    }
  }
  return b;
}
int main(){
  int t;
  icin(t);
  while(t--){
    ft.clear();
    icin(n);
    v.assign(n+1,-1);
    int val=0,rem=n;
    int a=1,idx;
    while(rem>0){
      val++;rem--;
      idx=getIndex(a,val+1);
      v[idx]=val;a=idx;
      ft.adjust(a,1);
    }
    for(int i=1;i<=n;i++){
      printf("%d ",v[i]);
    }
    printf("\n");
  }
}