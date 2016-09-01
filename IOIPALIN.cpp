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
int N;
string S;
int dp[2][5000];

int solve(){
	memset(dp,0,sizeof dp);
	for(int i=N-2;i>=0;i--){
		for(int j=i+1;j<=N-1;j++){
			if(S[i]==S[j])dp[i%2][j] = dp[(i+1)%2][j-1];
			else dp[i%2][j] = 1 + min(dp[i%2][j-1],dp[(i+1)%2][j]);
		}
	}
	return dp[0][N-1];
}

int main(){
	icin(N);
	cin>>S;
	printf("%d\n",solve());	
	return 0;
}