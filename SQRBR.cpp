#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef vector<int> vi;
typedef long long LL;

const int maxn=20;
// dp[i][j] = ith position, j opening brackets used
LL dp[(maxn<<1)+1][(maxn<<1)+1];
int v[(maxn<<1)+1];
int main(){
	int t;
	icin(t);
	while(t--){
		int n,k,pos;
		icin(n);
		icin(k);
		memset(v, 0, sizeof v);
		memset(dp, 0, sizeof dp);
		for(int i=0;i<k;i++){
			icin(pos);
			v[pos]=1;
		}
		dp[1][1]=1LL;
		for(int i=2;i<=2*n;i++){
			for(int j=((i+1)>>1);j<=i;j++){
				dp[i][j] = dp[i-1][j-1] + (1-v[i])*dp[i-1][j];
			}
		}
		printf("%lld\n",dp[n<<1][n]);
	}
}