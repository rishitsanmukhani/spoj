#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define bitcount(x) __builtin_popcount(x)
#define pb push_back
#define MOD (int(1e8)+7)
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

int v[2][(1<<10)];

int norm(int& val){
	if(val>=MOD)
		val -= MOD;
}

int main(){
	int T;
	icin(T);
	for(int t=1;t<=T;t++){
		int n,m,val;
		icin(n);icin(m);
		memset(v,0,sizeof v);
		v[0][0]=1;
		for(int i=1;i<=n;i++){
			icin(val);
			for(int j=0;j<(1<<10);j++){
				int cnt = v[(i-1)&1][j];
				v[(i-1)&1][j]=0;
				if(cnt){
					v[i&1][j^val] += cnt;
					v[i&1][j] += cnt;
					norm(v[i&1][j^val]);
					norm(v[i&1][j]);
				}
			}
		}
		for(int i=0;i<m;i++){
			icin(val);
			v[n&1][val]=0;
		}
		int ans=0;
		for(int i=0;i<(1<<10);i++){
			ans = ans + v[n&1][i];
			norm(ans);
		}
		printf("Case %d: %d\n",t,	ans);
	}
	return 0;
}