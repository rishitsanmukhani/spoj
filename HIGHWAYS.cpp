#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define INF (int(1e9))
typedef long long LL;
typedef pair<int, int> pii;


int n,m;
vector<vector<pii> > G;
vector<int> dist;
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
	int T;
	icin(T);
	while(T--){
		int s, t;
		icin(n);icin(m);
		icin(s);icin(t);
		G.assign(n+1,vector<pii>());
		int u,v,w;
		for(int i=1;i<=m;i++){
				icin(u);icin(v);icin(w);
				G[u].pb(pii(w, v));
				G[v].pb(pii(w, u));
		}
		dijkstra(s, t, G);
		if(dist[t]==INF)
			printf("NONE\n");
		else
			printf("%d\n", dist[t]);
	}
	return 0;
}