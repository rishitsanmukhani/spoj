#include <bits/stdc++.h>
using namespace std;
#define icin(x) (scanf("%d",&x))
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

int dp[2001][2001][3];
int H[3] = {-20, -5, 3};
int A[3] = {5, -10, 2};

int solve(int h, int a, int t){
	if(h<=0 || a<=0)return -1;
	if(dp[h][a][t]>=0)return dp[h][a][t];
	int p = (t+1)%3,q=(t+2)%3;
	dp[h][a][t] = 1 + max(solve(h + H[p], a + A[p], p), solve(h + H[q],a + A[q],q));
	return dp[h][a][t];
}
int main(){
	memset(dp, -1,sizeof dp);
	int t;
	icin(t);
	while(t--){
		int h,a;
		icin(h);
		icin(a);
		printf("%d\n", 1 + max(solve(h+H[0],a+A[0],0), max(solve(h+H[1],a+A[1],1) , solve(h+H[2],a+A[2],2))));
	}
	return 0;
}