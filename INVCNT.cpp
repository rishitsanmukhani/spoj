#include <bits/stdc++.h>

using namespace std;
#define icin(x) scanf("%d",&x)
#define pb push_back
typedef vector<int> vi;
typedef long long LL;

vi v;
vi tmp;
LL inversions(int a,int b){
  if(a==b)return 0;
  LL ans=0;
  int m=(a+b)>>1;
  ans += inversions(a,m);
  ans += inversions(m+1,b);
  tmp.clear();
  int i=a,j=m+1;
  
  while(i<=m && j<=b){
   if(v[i]<=v[j]) tmp.pb(v[i]),i++,ans += (j-m-1);
   else tmp.pb(v[j]),j++;
  }
  while(i<=m)tmp.pb(v[i]),i++,ans+=(j-m-1);
  while(j<=b)tmp.pb(v[j]),j++;

  for(int i=a;i<=b;i++) v[i]=tmp[i-a];
  
  return ans;
}
int main(){
  int t;
  icin(t);
  while(t--){
    int n;
    icin(n);
    v.resize(n);
    for(int i=0;i<n;i++){
      icin(v[i]);
    }
    cout<<inversions(0,n-1)<<endl;
  }
}