#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
#include <climits>
#include <cassert>

using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;

int N,T;
LL dp1[101][251];	//risk
LL dp2[101][251];	//time_taken
LL time_taken[101][101];
LL risk[101][101];

pair<LL,LL> solve(int _N,int _T){
	assert(_T>=0 && "Time should be positive");
	if(dp1[_N][_T]>=0)return pair<LL,LL>(dp1[_N][_T],dp2[_N][_T]);
	if(_N==1){
		dp1[_N][_T]=0;
		dp2[_N][_T]=0;
		return pair<LL,LL>(dp1[_N][_T],dp2[_N][_T]);
	}

	LL ans = LONG_MAX;
	for(int i=1;i<=N;i++){
		if(i==_N)continue;
		if(_T-time_taken[i][_N]<0)continue;
		pair<LL,LL> tmp = solve(i,_T-time_taken[i][_N]);
		if(tmp.first<0) continue;
		if(risk[i][_N]+tmp.first<ans){
			ans = risk[i][_N]+tmp.first;
			dp2[_N][_T] = time_taken[i][_N] + tmp.second;
		}
	}
	
	if(ans==LONG_MAX)ans=-1;

	dp1[_N][_T]=ans;

	return pair<LL,LL>(dp1[_N][_T],dp2[_N][_T]);
}


int main(){
	int t;
	icin(t);
	while(t--){
		memset(dp1,-1,sizeof dp1);
		icin(N);icin(T);
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				lcin(time_taken[i][j]);
			}
		}
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				lcin(risk[i][j]);
			}
		}
		pair<LL,LL> ans=solve(N,T);
		if(ans.first<0)
			printf("-1\n");
		else
		printf("%lld %lld\n",ans.first,ans.second);
	}
	return 0;
}