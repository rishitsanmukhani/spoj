#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define bitcount(x) __builtin_popcount(x)
#define pb push_back
#define MOD (int(1e8)+7)
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

const int maxn=int(1e5)+1;
int dp[maxn];
void precompute(){
	dp[1]=1;
	for(int i=2;i<maxn;i++){
		dp[i]=i;
		for(int j=1;j*j*j<=i;j++){
			dp[i] = min(dp[i], 1 + dp[i-j*j*j]);
		}
	}
}
int main(){
	precompute();
	int n,t=1;
	while(scanf("%d",&n)!=EOF){
		printf("Case #%d: %d\n",t++,dp[n]);
	}
	return 0;
}