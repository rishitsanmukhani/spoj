#include <bits/stdc++.h>

using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair
#define F first
#define S second

typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

int n,m;
vvi adj;
vi dfs_num,dfs_low,vis,parent,articulation_point;
int dfs_root,root_children;

void DFS(int k){
	if(vis[k])return;
	vis[k]=1;
	int p;
	for(int i=0;i<adj[k].size();i++){
		p=adj[k][i];
		if(vis[p]){
			if(p!=parent[k]){
				dfs_low[k]=min(dfs_low[k],dfs_num[p]);
			}
		}
		else{
			if(k==dfs_root)root_children++;
			parent[p]=k;
			dfs_num[p]=1+dfs_num[k];
			dfs_low[p]=dfs_num[p];
			DFS(p);
			if(dfs_low[p]>=dfs_num[k])
				articulation_point[k]=1;
			dfs_low[k]=min(dfs_low[k],dfs_low[p]);
		}
	}
}

int main(){
	while(1){
		icin(n);
		icin(m);
		if(n==0 && m==0)break;
		adj.assign(n+1,vi(0));
		int a,b;
		for(int i=0;i<m;i++){
			icin(a);icin(b);
			adj[a].pb(b);adj[b].pb(a);
		}
		dfs_num.assign(n+1,0);
		dfs_low.assign(n+1,0);
		vis.assign(n+1,0);
		parent.assign(n+1,-1);
		articulation_point.assign(n+1,0);

		for(int i=1;i<=n;i++){
			if(vis[i])continue;
			dfs_root = i;root_children=0;
			dfs_num[dfs_root]=0;
			dfs_low[dfs_root]=dfs_num[dfs_root];
			DFS(i);
			if(root_children>1) articulation_point[dfs_root]=1;
			else articulation_point[dfs_root]=0;
		}
		int cnt=0;
		for(int i=1;i<=n;i++){
			if(articulation_point[i])cnt++;
		}
		printf("%d\n",cnt);
	}
	return 0;
}