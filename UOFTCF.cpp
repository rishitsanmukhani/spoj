#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)

typedef long long LL;

int R,C;
vector<string> v;
int dp[50][50][50];
int solve(){
	//dp[i][j][k] = [i][j] -> position of Alice
	//[i][k] -> position of Bob
	memset(dp,-1,sizeof dp);
	for(int j=0;j<C;j++){
		if(v[0][j]=='#')continue;
		for(int k=0;k<C;k++){
			if(v[0][k]=='#' || j==k)continue;
			if(abs(j-k)==1)dp[0][j][k]=1;
			else dp[0][j][k]=0;
		}
	}
	for(int i=1;i<R;i++){
		for(int j=0;j<C;j++){
			if(v[i][j]=='#')continue;
			for(int k=0;k<C;k++){
				if(v[i][k]=='#' || j==k)continue;
				
				int max_ans=-1;
				for(int m=-1;m<=1;m++){
					if(j+m<0 || j+m>=C)continue;
					if(v[i-1][j+m]=='#')continue;
					for(int n=-1;n<=1;n++){
						if(k+n<0 || k+n>=C || j+m==k+n)continue;
						if(v[i-1][k+n]=='#')continue;
						max_ans = max(max_ans,dp[i-1][j+m][k+n]);
					}
				}
				if(max_ans>=0){
					if(abs(j-k)==1) dp[i][j][k] = 1+max_ans;
					else dp[i][j][k]=max_ans;
				}
			}
		}
	}
	int ans=-1;
	for(int j=0;j<C;j++){
		for(int k=0;k<C;k++){
			ans = max(ans,dp[R-1][j][k]);
		}
	}
	return ans;
}
int main(){
	int T;
	icin(T);
	while(T--){
		icin(R);icin(C);
		v.resize(R,"");
		for(int i=0;i<R;i++){
			cin>>v[i];
		}
		int ans = solve();
		if(ans<0)printf("Detour\n");
		else printf("%d\n",solve());
	}
	return 0;
}