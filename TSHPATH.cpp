#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define INF (LL(1e12))
typedef long long LL;
typedef pair<LL, int> pii;


map<string, int> m;
char name[20];
int n;
vector<vector<pii> > G;
vector<LL> dist;
priority_queue<pii, vector<pii>, greater<pii> > pq;

LL dijkstra(int s, int t){
	int u, v;
	LL d, w;

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
	return dist[t];
}

int main(){
	int t;
	icin(t);
	while(t--){
		icin(n);
		G.assign(n+1,vector<pii>());
		for(int u=1;u<=n;u++){
			scanf("%s",name);
			m[string(name)]=u;
			int k, v;
			LL w;
			icin(k);
			for(int j=0;j<k;j++){
				icin(v);lcin(w);
				G[u].pb(pii(w, v));
			}
		}
		int r, u, v;
		icin(r);
		for(int i=0;i<r;i++){
			scanf("%s", name);
			u = m[string(name)];
			scanf("%s", name);
			v = m[string(name)];
			printf("%lld\n",dijkstra(u, v));
		}
	}
	return 0;
} 