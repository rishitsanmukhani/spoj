#include <bits/stdc++.h>
using namespace std;

#define GC getchar_unlocked
int read(){
	register char c=0;
	while(c<33)c=GC();
	int a =0;
	while(c>33){
		a=a*10+c-48;
		c=GC();
	}
	return a;
}

#define icin(x) (x=read())
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

const int maxn=int(8e5)+1;
int a[maxn], dp[maxn];
int cnt[int(1e6)+1];
LL res[int(1e6)+1];

int main(){
	int n;
	icin(n);
	for(int i=1;i<=n;i++){
		icin(a[i]);
	}
	cnt[a[1]]=1;
	dp[1]=1;
	res[1]=1;
	for(int i=2;i<=n;i++){
		dp[i] = max(cnt[a[i]]+1, dp[i-1]);
		cnt[a[i]]=i;
		res[i-dp[i]+1]++;
	}
	for(int i=int(1e6)-1;i>=1;i--){
		res[i] += res[i+1];
	}
	for(int i=1;i<=int(1e6);i++){
		res[i]+=res[i-1];
	}
	int q;
	icin(q);
	while(q--){
		int a,b;
		icin(a);icin(b);
		printf("%lld\n", res[b] - res[a-1]);
	}
	return 0;
}