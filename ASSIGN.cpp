#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define bitcount(x) __builtin_popcount(x)
#define pb push_back
#define MOD (int(1e9)+7)
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

const int maxn=20;
vvi v;
LL dp[1<<maxn];

int main(){
	int t;
	icin(t);
	while(t--){
		int n,val;
		icin(n);
		v.assign(n,vi(0));
		for(int i=0;i<n;i++){
			for(int j=0;j<n;j++){
				icin(val);
				if(val)v[i].pb(j);
			}
		}
		dp[0]=1;
		for(int mask=1;mask<(1<<n);mask++){
			dp[mask]=0;
			int i = bitcount(mask);
			for(int j=0;j<v[i-1].size();j++){
				if(mask & (1<<v[i-1][j]))
					dp[mask] += dp[mask & (~(1<<v[i-1][j]))];
			}
		}
		printf("%lld\n",dp[(1<<n)-1]);
	}
	return 0;
}