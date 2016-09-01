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

#define GC getchar_unlocked
int read(){
	register char c=0;
	while(c<33)c=GC();
	int a=0;
	while(c>33){
		a=(a<<3)+(a<<1)+c-48;
		c=GC();
	}
	return a;
}
#define icin(x) (x=read())
#define pb push_back
#define mp make_pair

int N;
bool flag;
vector<vector<int> > e(N,vector<int>(0));
vector<int> v(N,0);		//Visited(0-white,1-grey,2-black)
stack<int> order;	//dfs completion time ordering

void addEdge(int a,int b){
	e[a].pb(b);
}
void dfs(int n){
	if(v[n]==1)flag=true;
	if(v[n])return;
	v[n]=1;
	for(int i=e[n].size()-1;i>=0;i--){
		dfs(e[n][i]);
	}
	v[n]=2;
	order.push(n);
}
void toposort(){
	flag=false;
	for(int i=N-1;i>=0;i--)
		if(!v[i])dfs(i);
}
int main(){
	int M,a,b;
	icin(N);icin(M);
	for(int i=0;i<M;i++){
		icin(a);icin(b);
		a--;b--;
		addEdge(a,b);
	}
	for(int i=0;i<N;i++){
		sort(e[i].begin(),e[i].end());
	}
	toposort();
	if(flag){
		printf("Sandro fails.\n");
	}else{
		while(order.size()!=1){
			printf("%d ",order.top()+1);
			order.pop();
		}
		printf("%d\n",order.top()+1);
	}
	return 0;
}