#include <bits/stdc++.h>
using namespace std;
#define icin(x) (scanf("%d",&x))
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

vi b,c;
vector<vector<LL> > dp;
int main(){
	int n,m;
	icin(n);icin(m);
	b.resize(n);
	c.resize(m);
	for(int i=0;i<n;i++)icin(b[i]);
	for(int i=0;i<m;i++)icin(c[i]);
	sort(b.begin(), b.end());
	sort(c.begin(), c.end());
	dp.resize(n+1, vector<LL>(m+1,0));
	for(int i=1;i<=n;i++){
		dp[i][i] = abs(b[i-1]-c[i-1])+dp[i-1][i-1];
		for(int j=i+1;j<=m;j++){
			dp[i][j] = min(dp[i][j-1], dp[i-1][j-1] + abs(b[i-1] - c[j-1]));
		}
	}
	printf("%lld\n", dp[n][m]);
	return 0;
}