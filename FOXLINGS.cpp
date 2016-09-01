#include <cstdint>
#include <vector>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <unordered_map>
using namespace std;

typedef long long LL;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair

class DSU{
public:
	vector<int32_t> parent;
	vector<int32_t> rank;
	vector<int32_t> size;		//Size of set
	int32_t number_of_sets;
	DSU(){
		init(0);
	}
	~DSU(){
		number_of_sets=0;
		parent.clear();rank.clear();size.clear();
	}
	void init(int32_t _n){
		number_of_sets=_n;
		parent.resize(_n);
		rank.resize(_n);
		size.resize(_n);
		for(int32_t i=0;i<_n;i++){
			parent[i]=i;rank[i]=1;size[i]=1;
		}
	}
	int32_t root(int32_t i){
		return (parent[i]==i) ? i : (parent[i] = root(parent[i]));
	}
	int32_t sizeSet(int32_t i){
		return (parent[i]==i) ? size[i] : size[i] = size[root(i)];
	}
	void unionSet(int32_t i,int32_t j){
		i=root(i);j=root(j);
		if(i==j)return;
		number_of_sets--;
		if(rank[i]<rank[j])swap(i,j);
		if(rank[i]==rank[j])rank[i]++;
		parent[j]=i;
		size[i] += size[j]; 
	}
	bool isSameSet(int32_t i,int32_t j){
		return root(i)==root(j);
	}
};

DSU dset;
vector<pair<int,int> > inp;
unordered_map<int,int> m;

int main(){
	int N,M,index=0;
	icin(N);icin(M);

	inp.resize(M);
	m.clear();
	dset.init(min(int(2e5),N));

	for(int i=0;i<M;i++){
		icin(inp[i].first);
		icin(inp[i].second);
		if(m.count(inp[i].first)==0){
			m.insert(mp(inp[i].first,index));
			index++;
		}
		if(m.count(inp[i].second)==0){
			m.insert(mp(inp[i].second,index));
			index++;
		}
		dset.unionSet(m.find(inp[i].first)->second,m.find(inp[i].second)->second);
	}
	
	int ans = dset.number_of_sets+max(0,N - int(2e5));
	printf("%d",ans);
	return 0;
}