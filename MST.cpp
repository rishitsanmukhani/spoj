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

int n,m;
vector<vector<pii> > adj;
vi taken;
LL sum=0;

void MST(){
	priority_queue<pii,vector<pii>,greater<pii> > pq;
	for(int i=0;i<adj[1].size();i++)pq.push(mp(adj[1][i].second,adj[1][i].first));
	taken[1]=1;
	int a,w;
	while(!pq.empty()){
		auto p=pq.top();pq.pop();
		a=p.second;w=p.first;
		if(taken[a])continue;
		for(int i=0;i<adj[a].size();i++){
			if(taken[adj[a][i].first])continue;
			pq.push(mp(adj[a][i].second,adj[a][i].first));
		}
		taken[a]=1;
		sum += w;
	}
}
int main(){
	icin(n);icin(m);
	int a,b,w;
	adj.resize(n+1,vector<pii>(0));
	for(int i=0;i<m;i++){
		icin(a);icin(b);icin(w);
		adj[a].pb(mp(b,w));
		adj[b].pb(mp(a,w));
	}
	taken.assign(n+1,0);
	MST();
	cout<<sum<<endl;
	
	return 0;
}