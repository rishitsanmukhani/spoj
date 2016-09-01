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
const LL MOD = int(1e9)+7;

string s;
vector<int> dp(int(1e5)+1);
vector<int> sum(int(1e5)+1);
int last[26];

int solve(){
	fill(dp.begin(),dp.end(),0);
	fill(sum.begin(),sum.end(),0);
	memset(last,-1,sizeof last);
	//Empty sequence
	dp[0]=1;
	sum[0]=1;
	
	//dp[i] = distinct sequences ending with s[i-1]
	//sum[i] = all distinct sequences possible with s[0...i-1]
	for(int i=1;i<=s.size();i++){
		if(last[s[i-1]-'A']>=1) dp[i] = (sum[i-1]-sum[last[s[i-1]-'A']-1] + MOD)%MOD;
		else dp[i]=(sum[i-1])%MOD;
		last[s[i-1]-'A']=i;
		sum[i] = (dp[i] + sum[i-1])%MOD;
	}
	return sum[s.size()];
}

int main(){
	int T;
	icin(T);
	while(T--){
		cin>>s;
		printf("%d\n",solve());
	}
	return 0;
}