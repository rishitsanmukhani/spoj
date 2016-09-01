#include <bits/stdc++.h>

using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair

typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int,int> pii;

vvi adj;
vi dp1,dp2;
vi visited;
void solve(int k){
	if(visited[k]==1)return;
	visited[k]=1;
	dp1[k]=1;
	dp2[k]=0;
	for(int i=0;i<adj[k].size();i++){
		if(visited[adj[k][i]]==0){
			solve(adj[k][i]);
			dp1[k] += min(dp2[adj[k][i]],dp1[adj[k][i]]);
			dp2[k] += dp1[adj[k][i]];
		}
	}
}

int main(){
	int n;
	icin(n);
	int a,b;
	adj.resize(n+1,vi(0));
	for(int i=1;i<n;i++){
		icin(a);icin(b);
		assert(a>=1 && a<=n);
		assert(b>=1 && b<=n);
		adj[a].pb(b);adj[b].pb(a);
	}
	dp1.assign(n+1,0);
	dp2.assign(n+1,0);
	visited.assign(n+1,0);
	solve(1);
	cout<<min(dp1[1],dp2[1])<<endl;
	return 0;
}