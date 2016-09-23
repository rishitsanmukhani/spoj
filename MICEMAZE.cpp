#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define INF (int(3e8))
typedef long long LL;
typedef pair<int, int> pii;


int n,m;
vector<vector<pii> > G, G_inv, G1;
vector<int> dist, dist_s, dist_t;
priority_queue<pii, vector<pii>, greater<pii> > pq;

void dijkstra(int s, int t, vector<vector<pii> >& G){
	int u, v, d, w;

	dist.assign(n+1, INF);
	pq.push(pii(0, s));
	dist[s]=0;

	while(!pq.empty()){
		pii front = pq.top();pq.pop();
		d = front.first, u = front.second;
		if(d > dist[u])
			continue;
		for(int j=0;j<G[u].size();j++){
			w = G[u][j].first, v = G[u][j].second;
			if(dist[u] + w < dist[v]){
				dist[v] = dist[u] + w;
				pq.push(pii(dist[v], v));
			}
		}
	}
}
int main(){
	int s, t;
	icin(n);
	icin(s);icin(t);
	icin(m);
	G.assign(n+1,vector<pii>());
	G_inv.assign(n+1,vector<pii>());
	int u,v,w;
	for(int i=1;i<=m;i++){
			icin(u);icin(v);icin(w);
			G[u].pb(pii(w, v));
			G_inv[v].pb(pii(w, u));
	}
	dijkstra(s, 0, G_inv);
	int res=0;
	for(int i=1;i<=n;i++){
		if(dist[i]<=t)res++;
	}
	printf("%d\n", res);
	return 0;
}