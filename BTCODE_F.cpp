#include <bits/stdc++.h>
using namespace std;
#define icin(x) scanf("%d", &x)
#define lcin(x) scanf("%lld", &x)
typedef long long LL;

#define OFF (650)
int v[25][25];
int dp[2][25][1300];
int main(){
  int t;
  icin(t);
  while(t--){
    memset(dp, 0, sizeof dp);
    int m,n,a,b;
    icin(m);icin(n);
    icin(a);icin(b);
    a += OFF;
    b += OFF;
    for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        icin(v[i][j]);
    for(int j=0;j<n;j++)
      dp[0][j][v[0][j]+OFF]=1;
    for(int i=1;i<m;i++){
      int k0 = (i+1)&1;
      int k1 = i&1;
      for(int j=0;j<n;j++){
        if(j>0)
          for(int k=0;k<1300;k++)
            if(dp[k0][j-1][k])
              dp[k1][j][k+v[i][j]]=1;
        if(j<n-1)
          for(int k=0;k<1300;k++)
            if(dp[k0][j+1][k])
              dp[k1][j][k+v[i][j]]=1;
        for(int k=0;k<1300;k++)
          if(dp[k0][j][k])
            dp[k1][j][k+v[i][j]]=1;
      }
      for(int j=0;j<n;j++){
        for(int k=0;k<1300;k++){
          dp[k0][j][k]=0;
        }
      }
    }
    int k1 = (m-1)&1;
    int maxi = -1, mini = 1300;
    for(int i=0;i<25;i++){
      for(int j=min(1300-1, b);j>=max(a,0);j--){
        if(dp[k1][i][j])
          maxi = max(maxi, j);
      }
    }
    for(int i=0;i<25;i++){
      for(int j=min(1300-1, b);j>=max(a,0);j--){
        if(dp[k1][i][j])
          mini = min(mini, j);
      }
    }
    if(mini==1300)printf("NO ");
    else printf("%d ", mini-OFF);
    if(maxi==-1)printf("NO\n");
    else printf("%d\n", maxi-OFF);
  }
  return 0;
}