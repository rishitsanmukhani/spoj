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

int K,M;
int dp[1001][50];

int knapsack01(vector<pair<int,int> >& v,int K){
	//dp[k][i] = max weight is k and items are v[0...i]
	for(int i=0;i<v.size();i++)dp[0][i]=0;
	for(int k=0;k<=K;k++){
		if(v[0].first<=k)dp[k][0] = v[0].second; 
		else dp[k][0] = 0;
	}
	for(int k=1;k<=K;k++){
		for(int i=1;i<v.size();i++){
			if(v[i].first <= k)
				dp[k][i] = max(dp[k-v[i].first][i-1]+v[i].second,dp[k][i-1]); 
			else
				dp[k][i] = dp[k][i-1];
		}
	}
	return dp[K][v.size()-1];
}

int main(){
	int T;
	icin(T);
	while(T--){
		icin(K);icin(M);
		vector<pair<int,int> > v(M);
		for(int i=0;i<M;i++){
			icin(v[i].first);
			icin(v[i].second);
		}
		printf("Hey stupid robber, you can get %d.\n",knapsack01(v,K));
	}
	return 0;
}