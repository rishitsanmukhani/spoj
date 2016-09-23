#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define INF (int(1e6))
typedef long long LL;
typedef pair<int, int> pii;


int n,m;
vector<vector<pii> > G, G_inv, G1;
vector<int> dist, dist_s, dist_t;
priority_queue<pii, vector<pii>, greater<pii> > pq;

void dijkstra(int s, int t, vector<vector<pii> >& G){
	int u, v, d, w;

	dist.assign(n, INF);
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
	while(1){
		icin(n);icin(m);
		if(n==0 && m==0)break;
		int s, t;
		icin(s);icin(t);
		G.assign(n,vector<pii>());
		G_inv.assign(n,vector<pii>());
		G1.assign(n,vector<pii>());
		int u,v,w;
		for(int i=1;i<=m;i++){
				icin(u);icin(v);icin(w);
				G[u].pb(pii(w, v));
				G_inv[v].pb(pii(w, u));
		}
		dijkstra(t, s, G_inv);dist_t = dist;
		dijkstra(s, t, G);dist_s = dist;
		for(int i=0;i<n;i++){
			for(int j=0;j<G[i].size();j++){
				if(dist_s[i] + G[i][j].first + dist_t[G[i][j].second] != dist_s[t]){
					G1[i].pb(G[i][j]);
				}
			}
		}
		dijkstra(s, t, G1);
		if(dist[t]==INF)
			printf("-1\n");
		else
			printf("%d\n", dist[t]);
	}
	return 0;
}