#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define MOD (int(1e9)+7)
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

const int maxn = 6200;
int dp[2][maxn];

int main(){
	int t;
	icin(t);
	while(t--){
		memset(dp,0,sizeof dp);
		string s;
		cin>>s;
		int n = s.size();
		for(int i=n-1;i>=0;i--){
			dp[i&1][i]=0;
			for(int j=i+1;j<n;j++){
				if(s[i]==s[j]){
					dp[i&1][j] = (i+1 > j-1)?0:dp[(i+1)&1][j-1];
				}
				else{
					dp[i&1][j] = 1 + min(dp[(i+1)&1][j], dp[i&1][j-1]);
				}
			}
		}
		printf("%d\n",dp[0][n-1]);
	}
	return 0;
}