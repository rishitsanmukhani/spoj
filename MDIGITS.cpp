#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)

typedef vector<int> vi;
typedef long long LL;

template < typename T > std::string to_string( const T& n ){
  std::ostringstream stm;stm << n;
  return stm.str() ;
}

const int n=17;
string y;
LL dp[n][n][2][2];

LL F(int idx,int digit_occurence,bool flag,int digit,bool leading_zero){
  if(idx==n){
    return digit_occurence;
  }
  if(dp[idx][digit_occurence][flag][leading_zero]!=-1)
    return dp[idx][digit_occurence][flag][leading_zero];
  int d_max = (flag) ? 9:(y[idx]-'0');
  LL ans=0;
  for(int i=0;i<=d_max;i++){
    if(i==digit){
      if(leading_zero && digit==0)
        ans += F(idx+1,digit_occurence, flag || (i < y[idx]-'0'),digit,(leading_zero && i==0));
      else
        ans += F(idx+1,digit_occurence+1, flag || (i < y[idx]-'0'),digit,(leading_zero && i==0));
    }
    else ans += F(idx+1,digit_occurence, flag || (i < y[idx]-'0'),digit,(leading_zero && i==0));
  }
  dp[idx][digit_occurence][flag][leading_zero]=ans;
  return ans;
}

LL solve(LL a,int digit){
  if(a<0)a=0;
  y=to_string(a);
  y=string(n-y.size(),'0')+y;
  memset(dp,-1,sizeof dp);
  return F(0,0,0,digit,1);
}
int main(){
  while(1){
    LL a,b;
    lcin(a);lcin(b);
    if(a>b)swap(a,b);
    if(a==0)break;
    for(int i=0;i<=9;i++){
      printf("%lld ",solve(b,i)-solve(a-1,i));
    }
    printf("\n");
  } 
  return 0;
}