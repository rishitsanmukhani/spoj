#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair

int N;
vector<vector<int> > e;
vector<vector<int> > er;
vector<int> v;	//Visited
vector<vector<int> > cc;		//Connected components
stack<int> order;	//dfs completion time ordering

void addEdge(int a,int b){
	e[a].pb(b);er[b].pb(a);
}
void dfs(int n){
	if(v[n])return;
	v[n]=1;
	for(int i=0;i<e[n].size();i++){
		if(!v[e[n][i]])dfs(e[n][i]);
	}
	order.push(n);
}
void dfs_rev(int n){
	if(v[n])return;
	v[n]=1;
	for(int i=0;i<er[n].size();i++){
		if(!v[er[n][i]])dfs_rev(er[n][i]);
	}
	cc.back().pb(n);
}
void scc(){
	cc.clear();
	v.resize(N,0);
	for(int i=0;i<N;i++)
		if(!v[i])dfs(i);
	
	fill(v.begin(),v.end(),0);
	while(!order.empty()){
		int i=order.top();order.pop();
		if(!v[i]){
			cc.pb(vector<int>(0));
			dfs_rev(i);
		}
	}
}
int main(){
	int M,a,b;
	icin(N);icin(M);
	e.resize(N,vector<int>(0));
	er.resize(N,vector<int>(0));
	for(int i=0;i<M;i++){
		icin(a);icin(b);
		addEdge(a,b);
	}
	
	scc();
	
	int mini;
	for(int i=0;i<cc.size();i++){
		mini=N+1;
		for(int j=0;j<cc[i].size();j++){
			v[cc[i][j]]=i;
			if(cc[i][j]<mini)mini=cc[i][j];
		}
		cc[i][0]=mini;
	}
	for(int i=0;i<N;i++){
		printf("%d\n",cc[v[i]][0]);
	}
	return 0;
}