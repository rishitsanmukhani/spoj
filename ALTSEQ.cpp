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

const int maxn=5000;
int v[maxn],dp[maxn];
int main(){
	int n;
	icin(n);
	for(int i=0;i<n;i++){
		icin(v[i]);
	}
	int ans=1;
	dp[0]=1;
	for(int i=1;i<n;i++){
		dp[i]=1;
		int j=i-1;
		while(j>=0){
			if(v[i]>0 && v[j]<0 && v[i]+v[j]>0)
				dp[i] = max(dp[i], 1 + dp[j]);
			else if(v[i]<0 && v[j]>0 && v[i]+v[j]<0)
				dp[i] = max(dp[i], 1 + dp[j]);
			j--;
		}
		ans = max(ans,dp[i]);
	}
	printf("%d\n",ans);
	return 0;
}