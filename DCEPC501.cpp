#include <bits/stdc++.h>
using namespace std;
#define icin(x) (scanf("%d",&x))
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

int n;
vi v;
vector<LL> dp;
void solve(){
	dp[n-1]=v[n-1];
	if(n==1)return;
	dp[n-2]=dp[n-1]+v[n-2];
	if(n==2)return;
	dp[n-3]=dp[n-2]+v[n-3];
	if(n==3)return;
	for(int i=n-4;i>=0;i--){
		dp[i] = v[i] + dp[i+2];
		dp[i] = max(dp[i], v[i] + v[i+1] + dp[i+4]);
		dp[i] = max(dp[i], v[i] + +v[i+1] + v[i+2] + dp[i+6]);
	}
}
int main(){
	int t;
	icin(t);
	while(t--){
		icin(n);
		v.resize(n);
		for(int i=0;i<n;i++)icin(v[i]);
		dp.assign(n+3,0);
		solve();
		printf("%lld\n", dp[0]);
	}
	return 0;
}