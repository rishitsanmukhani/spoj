#include <bits/stdc++.h>

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

typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int,int> pii;

int n;
vvi e;
vector<int> v,ans;		//Visited(0-white,1-grey,2-black)
stack<int> order;

void dfs(int n){
	if(v[n])return;
	v[n]=1;
	for(int i=0; i<e[n].size(); ++i){
		dfs(e[n][i]);
	}
	v[n]=2;
	order.push(n);
}
void toposort(){
	for(int i=1; i<=n; ++i){
		if(!v[i]){
			dfs(i);
		}
	}
}
int main(){
	int k,a, w;
	icin(n);icin(k);
	e.resize(n+1);
	for(int i=1;i<=k;++i){
		icin(w);
		for(int j=1; j<=w; ++j){
			icin(a);
			e[i].pb(a);
		}
	}
	v.assign(n+1, 0);
	ans.assign(n+1, 0);
	toposort();

	int p=0;
	while(!order.empty()){
		ans[order.top()]=p;
		p = order.top();
		order.pop();
	}
	for(int i=1;i<=n;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}