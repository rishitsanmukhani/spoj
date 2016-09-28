#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define bit(x, i) ((x>>i)&1)
#define MOD (int(1e9)+7)
typedef long long LL;

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
const int maxn=int(1e6);
int f[maxn+1], g[maxn+1], h[maxn+1];
// f => A !< B && B !< A
// g => A < B or B < A
// h => A == B
void precompute(){
	f[1] = 0;
	g[1] = 2;
	h[1] = 2;
	for(int i=2;i<=maxn;i++){
		h[i] = mul(2,h[i-1]);
		g[i] = add(mul(3, g[i-1]), mul(2, h[i-1]));
		f[i] = add(mul(4, f[i-1]), g[i-1]);
	}
}

int main(){
	precompute();
	int t;
	icin(t);
	while(t--){
		int n;
		icin(n);
		printf("%d\n", f[n]);
	}
	return 0;
}