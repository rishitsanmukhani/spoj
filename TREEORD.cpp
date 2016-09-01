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

vi pre,post,in;
vvi adj;
vi idx_in;
int n;
void process(){
	idx_in.resize(n+1);
	for(int i=0;i<n;i++){
		idx_in[in[i]]=i;
	}
}
void solve(int pre_l,int pre_r,int in_l,int in_r){
	if(pre_l>=pre_r)return;
	int root=pre[pre_l];
	int idx=idx_in[root];
	int n_left=idx-in_l,n_right=in_r-idx;
	if(n_left>0){
		adj[root].pb(pre[pre_l+1]);	
		solve(pre_l+1,pre_l+n_left,in_l,idx-1);
	}
	if(n_right>0){
		adj[root].pb(pre[pre_r-n_right+1]);
		solve(pre_r-n_right+1,pre_r,idx+1,in_r);
	}
}
vi post_new;
void postorder(int p){
	for(int i=0;i<adj[p].size();i++){
		postorder(adj[p][i]);
	}
	post_new.pb(p);
}
int main(){
	icin(n);
	pre.resize(n),post.resize(n),in.resize(n);
	for(int i=0;i<n;i++)icin(pre[i]);
	for(int i=0;i<n;i++)icin(post[i]);
	for(int i=0;i<n;i++)icin(in[i]);
	adj.resize(n+1,vi(0));
	process();
	solve(0,n-1,0,n-1);
	postorder(pre[0]);
	int flag=1;
	for(int i=0;i<n;i++)if(post_new[i]!=post[i])flag=0;
	if(flag)cout<<"yes"<<endl;
	else cout<<"no"<<endl;
	return 0;
}