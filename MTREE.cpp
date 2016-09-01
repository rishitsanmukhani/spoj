#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <queue>
#include <set>

using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;
const LL MOD = int(1e9)+7;

int N;
vector<vector<pair<int,int> > > edge(int(1e5)+1,vector<pair<int,int> >(0));
vector<pair<LL,LL> > vert(int(1e5)+1);
vector<int> parent(int(1e5)+1);

LL Weight(int v){
	if(vert[v].first>=0) return vert[v].first;
	
	LL weight=0;
	LL rooted_path=0;
	LL tmp1=0,tmp2=0;
	
	for(int i=0;i<edge[v].size();i++){
		if(parent[edge[v][i].first]>=0)continue;
		parent[edge[v][i].first]=v;

		weight = (weight + Weight(edge[v][i].first))%MOD;
		LL path = (edge[v][i].second*(1+vert[edge[v][i].first].second))%MOD; 
		tmp2 = (tmp2 + (path*tmp1)%MOD)%MOD;
		tmp1 = (tmp1+path)%MOD;
	}
	
	rooted_path=tmp1;
	weight=(weight+(rooted_path+tmp2)%MOD)%MOD;

	vert[v].first = weight;
	vert[v].second = rooted_path;
	return vert[v].first;
}


int main(){
	icin(N);
	int a,b,w;
	for(int i=1;i<N;i++){
		icin(a);icin(b);icin(w);
		edge[a].push_back(pair<int,int>(b,w));
		edge[b].push_back(pair<int,int>(a,w));
	}
	fill(vert.begin(),vert.end(),pair<int,int>(-1,-1));
	fill(parent.begin(),parent.end(),-1);
	parent[1]=0;
	printf("%lld\n",(Weight(1)+MOD)%MOD);
	// for(int i=1;i<=N;i++){
	// 	cout<<vert[i].first<<" "<<vert[i].second<<endl;
	// }


	return 0;
}