#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;
typedef long long LL;
const int maxn=60, maxv=3200, maxc=5;

vector<vector<int> > G;
vector<vector<pair<int, int> > > P;
vector<int> is_main;
LL dp[maxn][maxv];
int main(){
	int t;
	icin(t);
	while(t--){
		int v, n;
		icin(v);icin(n);
		v=v/10;
		G.assign(n+1, vi());
		P.assign(n+1, vpii());
		is_main.assign(n+1,1);
		int p, c, u;
		for(int i=1;i<=n;i++){
			icin(p);icin(c);
			icin(u);
			p/=10;
			c = p*c;
			P[i].pb(pii(p, c));
			if(u){
				is_main[i]=0;
				G[u].pb(i);
			}
		}
		for(int i=1;i<=n;i++){
			for(auto u:G[i]){
				int sz = P[i].size();
				p = P[u][0].first;
				c = P[u][0].second;
				for(int j=0;j<sz;j++){
					P[i].pb(pii(P[i][j].first + p, P[i][j].second + c));
				}
			}
		}
		// for(auto v:P){
		// 	for(auto p:v){
		// 		cout<<p.first<<" "<<p.second<<" : ";
		// 	}
		// 	cout<<endl;
		// }
		for(int i=1;i<=n;i++){
			for(int j=1;j<=v;j++){
				dp[i][j]=dp[i-1][j];
				if(is_main[i]){
					for(auto p:P[i]){
						if(p.first>j)continue;
						dp[i][j]=max(dp[i][j], dp[i-1][j-p.first]+p.second);
					}
				}
			}
		}
		printf("%lld\n", 10*dp[n][v]);
	}
}