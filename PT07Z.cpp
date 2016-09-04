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

const int maxn=int(1e4);
vvi G;
vi vis, l;
void dfs(int u, int p=-1){
	if(vis[u])return;
	vis[u] = 1;
	int v;
	for(int i=0;i<G[u].size();i++){
		v = G[u][i];
		if(p==v)continue;
		l[v] = 1 + l[u];
		dfs(v, u);
	}
}
int main(){
	int n;
	icin(n);
	int a, b;
	G.resize(n+1);
	for(int i=1;i<n;i++){
		icin(a);icin(b);
		G[a].pb(b);
		G[b].pb(a);
	}
	vis.assign(n+1, 0);
	l.assign(n+1, 0);

	dfs(1);
	int idx=1;
	for(int i=1;i<=n;i++){
		if(l[i]>l[idx])idx=i;
	}
	
	vis.assign(n+1, 0);
	l.assign(n+1, 0);
	dfs(idx);
	int ans=-1;
	for(int i=1;i<=n;i++)if(l[i]>ans)ans=l[i];
	printf("%d\n", ans);
	return 0;
}