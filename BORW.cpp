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

const int maxn = int(201);
int dp[maxn][maxn][maxn];
int v[maxn];

int main(){
	while(1){
		int n;
		icin(n);
		if(n==-1)break;
		for(int i=1;i<=n;i++){
			icin(v[i]);
		}
		memset(dp,0,sizeof dp);
		dp[1][1][0]=0;
		dp[1][0][1]=0;
		dp[1][0][0]=1;
		dp[1][1][1]=1;
		for(int i=2;i<=n;i++){
			for(int x=0;x<i;x++){
				for(int y=0;y<i;y++){
					if(x==y)
						dp[i][x][y] = i;
					else
						dp[i][x][y] = 1 + dp[i-1][x][y];
				}
			}
			for(int y=0;y<i;y++){
				dp[i][i][y]=dp[i-1][0][y];
				for(int x=1;x<i;x++){
					if(v[x]<v[i])
						dp[i][i][y]=min(dp[i-1][x][y],dp[i][i][y]);
				}
			}
			for(int x=0;x<i;x++){
				dp[i][x][i]=dp[i-1][x][0];
				for(int y=1;y<i;y++){
					if(v[y]>v[i])
						dp[i][x][i]=min(dp[i-1][x][y],dp[i][x][i]);
				}
			}
			dp[i][i][i]=i;
		}
		// for(int i=1;i<=n;i++){
		// 	for(int x=0;x<=i;x++)
		// 		for(int y=0;y<=i;y++){
		// 			printf("%d %d %d -> %d\n",i,x,y,dp[i][x][y]);
		// 		}
		// 	cout<<endl<<endl;
		// }
		int ans=n;
		for(int x=0;x<=n;x++){
			for(int y=0;y<=n;y++){
				ans = min(ans,dp[n][x][y]);
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}