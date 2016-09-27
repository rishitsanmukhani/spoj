#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define bit(x, i) ((x>>i)&1)
#define MOD (int(1e9)+7)
typedef long long LL;

const int B=10;	// MAX_XOR = 2^10 - 1 = 1023
int cnt[1<<B];
int r[B+1], c[B+1];
LL p[1<<B];
int n,m;

// Pre-computed factorials
void factorials(){
	p[0]=1;
	p[1]=1;
	for(int i=2;i<(1<<B);i++){
		p[i] = (p[i-1]*i)%MOD;	
	}
}

// 1 <= r <= n; r[B+1] = n[B...0] (bitwise possible counts)
// 1 <= c <= m; c[B+1] = m[B...0] (bitwise possible counts)
// r[i] = # bitwise counts <= n[i....0]
void precompute(){
	// n
	if(n&1)r[0]=2;
	else r[0]=1;
	for(int i=1;i<=B;i++){
		if(bit(n,i)==1) r[i] = (1<<i) + r[i-1];
		else r[i] = r[i-1];
	}
	// m
	if(m&1)c[0]=2;
	else c[0]=1;
	for(int i=1;i<=B;i++){
		if(bit(m,i)==1) c[i] = (1<<i) + c[i-1];
		else c[i] = c[i-1];
	}
}

// #pairs of (r,c) such that r^c = x
int solve(int x){
	vector<int> dp(B+1, 0);
	int i=0;
	if(bit(x,i)==1){
		if(bit(n,i)==1 && bit(m,i)==1){
			dp[i] = 2;
		}
		else if(bit(n,i)==1){
			dp[i] = 1;
		}
		else if(bit(m,i)==1){
			dp[i] = 1;
		}
		else{
			dp[i] = 0;
		}
	}
	else{
		if(bit(n,i)==1 && bit(m,i)==1){
			dp[i] = 2;
		}
		else{
			dp[i] = 1;
		}
	}
	for(int i=1;i<=B;i++){
		if(bit(x,i)==1){
			if(bit(n,i)==1 && bit(m,i)==1){
				dp[i] = r[i-1] + c[i-1];
			}
			else if(bit(n,i)==1){
				dp[i] = dp[i-1];
			}
			else if(bit(m,i)==1){
				dp[i] = dp[i-1];
			}
			else{
				dp[i] = 0;
			}
		}
		else{
			if(bit(n,i)==1 && bit(m,i)==1){
				dp[i] = dp[i-1] + (1<<i);
			}
			else if(bit(n,i)==1){
				dp[i] = c[i-1];
			}
			else if(bit(m,i)==1){
				dp[i] = r[i-1];
			}
			else{
				dp[i] = dp[i-1];
			}
		}
	}
	return dp[B];
}
int main(){
	factorials();
	int t;
	icin(t);
	while(t--){
		icin(n);icin(m);
		precompute();
		// solution is for 0...n * 0...m
		// We want it for 1...n * 1...m
		// So removing row/col corresponding to zero
		LL ans=p[(solve(0)-1)], val;
		for(int i=1;i<(1<<B);i++){
			val = solve(i);
			if(i<=n)val--;
			if(i<=m)val--;
			ans *= p[val];
			if(ans>=MOD)ans%=MOD;
		}
		printf("%lld\n",ans);
	}

	return 0;
}