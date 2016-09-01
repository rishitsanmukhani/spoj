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

int dp[20][3];
int v[20][3];
int N;
int solve(){
	dp[0][0]=v[0][0];
	dp[0][1]=v[0][1];
	dp[0][2]=v[0][2];


	for(int i=1;i<N;i++){
		dp[i][0] = v[i][0] + min(dp[i-1][1],dp[i-1][2]);
		dp[i][1] = v[i][1] + min(dp[i-1][0],dp[i-1][2]);
		dp[i][2] = v[i][2] + min(dp[i-1][0],dp[i-1][1]);
	}
	return min(dp[N-1][0],min(dp[N-1][1],dp[N-1][2]));
}



int main(){
	int T;
	icin(T);
	while(T--){
		icin(N);
		for(int i=0;i<N;i++){
			icin(v[i][0]);icin(v[i][1]);icin(v[i][2]);
		}
		printf("%d\n",solve());
		
	}
	return 0;
}