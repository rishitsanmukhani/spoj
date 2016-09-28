#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define bit(x, i) ((x>>i)&1)
#define MOD (int(1e9)+7)
typedef long long LL;

const int maxn=int(1e7);
int f[maxn+1];
inline int mul(int a,int b){
	LL res=LL(a)*b;
	if(res>=MOD)res%=MOD;
	return res;
}
inline int add(int a, int b){
	int res = a+b;
	if(res>=MOD)res%=MOD;
	return res;	
}

// g[h] = g[h-1]*f[h-1]
// g[h] = f[h]-f[h-1]
void precompute(){
	f[0]=1;
	f[1]=2;
	for(int i=2;i<=maxn;i++){
		int a = add(mul(f[i-1], f[i-1]), f[i-1]);
		int b = mul(f[i-1], f[i-2]);
		f[i] = (a - b);
		if(f[i]<0)f[i]+=MOD;
	}
}

int main(){
	precompute();
	int t;
	icin(t);
	while(t--){
		int n;
		icin(n);
		int ans = f[n]-f[n-1];
		if(ans<0)ans += MOD;
		printf("%d\n", ans);
	}
	return 0;
}