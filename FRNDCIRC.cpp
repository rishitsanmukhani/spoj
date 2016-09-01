#include <cstdint>
#include <vector>
#include <cstdio>
#include <iostream>
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
unordered_map<string,int> m;

int main(){
	
	int T;icin(T);
	while(T--){
		int N,index=0;
		string s1,s2;
		icin(N);
		
		dset.init(2*N);
		m.clear();

		for(int i=0;i<N;i++){
			cin>>s1;
			cin>>s2;
			auto it1 = m.find(s1);
			auto it2 = m.find(s2);
			if(it1==m.end()){
				it1 = m.insert(mp(s1,index)).first;
				index++;
			}
			if(it2==m.end()){
				it2 = m.insert(mp(s2,index)).first;
				index++;
			}
			dset.unionSet(it1->second,it2->second);
			printf("%d\n",dset.sizeSet(it1->second));
		}
	}
	return 0;
}