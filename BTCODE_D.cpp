#include <bits/stdc++.h>
using namespace std;
#define icin(x) scanf("%d", &x)
#define lcin(x) scanf("%lld", &x)
typedef long long LL;

LL A[101][101], B[101][101], C[101][101];
int main(){
  int t;
  icin(t);
  while(t--){
    int m,n;
    icin(m);
    icin(n);
    for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        lcin(A[i][j]);
    for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        lcin(B[i][j]);
    for(int i=0;i<m;i++)
      for(int j=0;j<n;j++)
        lcin(C[i][j]);
    LL res=0;
    for(int i=0;i<m;i++){
      LL maxi=0;
      for(int j=0;j<n;j++){
        maxi = max(maxi, C[i][j]*min(A[i][j], B[i][j]));
      }
      res += maxi;
    }
    printf("%lld\n", res);
  }
  return 0;
}