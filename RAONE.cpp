#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
typedef vector<int> vi;

template < typename T > std::string to_string( const T& n ){
  std::ostringstream stm;stm << n;
  return stm.str() ;
}

const int n=9;
string y;
int dp[n][9*n][2];

int F(int idx,int digit_sum,bool flag){
  if(idx==n){
    return digit_sum==1;
  }
  if(dp[idx][digit_sum][flag]!=-1)
    return dp[idx][digit_sum][flag];
  int d_max = (flag) ? 9:(y[idx]-'0');
  int ans=0;
  for(int i=0;i<=d_max;i++){
    if(idx&1)
      ans += F(idx+1,digit_sum+i, flag || (i < y[idx]-'0'));
    else
      ans += F(idx+1,digit_sum-i, flag || (i < y[idx]-'0'));
  }
  dp[idx][digit_sum][flag]=ans;
  return ans;
}

int solve(int a){
  if(a<0)a=0;
  y=to_string(a);
  y=string(n-y.size(),'0')+y;
  memset(dp,-1,sizeof dp);
  return F(0,0,0);
}
int main(){
  int t;
  icin(t);
  while(t--){
    int a,b;
    icin(a);icin(b);
    cout<<solve(b)-solve(a-1)<<endl;
  } 
  return 0;
}