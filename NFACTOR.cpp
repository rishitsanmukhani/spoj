#include <bits/stdc++.h>
using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int maxn=int(1e6)+1;
int p[maxn];
void sieve(){
	memset(p, 0, sizeof p);
	for(int i=2;i<=maxn;i++){
		if(p[i]!=0)continue;
		for(int j=i;j<=maxn;j+=i){
			p[j]++;
		}
	}
}
vector<int> ans[maxn];
void precompute(){
	sieve();
	vector<int> cnt(11,0);
	ans[0]=cnt;
	for(int i=1;i<=maxn;i++){
		cnt[p[i]]++;
		ans[i]=cnt;
	}
}
int main(){
	precompute();
	int t;
	icin(t);
	while(t--){
		int a,b,n;
		icin(a);icin(b);icin(n);
		printf("%d\n", ans[b][n]-ans[a-1][n]);
	}
	return 0;
}