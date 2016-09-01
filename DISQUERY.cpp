#include <bits/stdc++.h>
using namespace std;

#define GC getchar
int read(){
	char c=0;
	while(c<33)c=GC();
	int a =0;
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
typedef vector<vi> vvi;
typedef pair<int,int> pii;

const int maxn=100005,log_maxn=17;
int n,log_n;
pair<int,pii> dp[log_maxn][maxn];
int vis[maxn]={0},L[maxn]={0};
vector<vector<pii> > adj;

int logBinary(unsigned int n){
	if(n==0)return-1;
	int p = 0;
	if (n>=1<<16){ n>>= 16; p += 16;}
	if (n>=1<< 8){ n>>=  8; p += 8; }
	if (n>=1<< 4){ n>>=  4; p += 4; }
	if (n>=1<< 2){ n>>=  2; p += 2; }
	if (n>=1<< 1){          p += 1; }
	return p;
}
void DFS(int k){
	if(vis[k])return;
	vis[k]=1;
	pii p;
	int w;
	for(int i=0;i<adj[k].size();i++){
		p=adj[k][i];
		w=p.second;
		if(vis[p.first])continue;
		L[p.first]=L[k]+1;
		dp[0][p.first]=mp(k,mp(w,w));
		DFS(p.first);
	}
}
void print(pair<int,pii> p){
	cout<<p.first<<" "<<p.second.first<<" "<<p.second.second<<endl;
}
void process(){
	pair<int,pii> p1,p2;
	for(int i=1;i<=log_n;i++){
		for(int j=1;j<=n;j++){
			if(dp[i-1][j].first!=-1){
				p1=dp[i-1][j];
				p2=dp[i-1][p1.first];
				dp[i][j].first=p2.first;
				dp[i][j].second.first=max(p1.second.first,p2.second.first);
				dp[i][j].second.second=min(p1.second.second,p2.second.second);
			}
		}
	}
}
#define MAX int(1e9)
#define MIN int(-1e9)
pii LCA(int a,int b){
	if(a==b)return mp(0,0);
	if(L[a]<L[b])swap(a,b);
	int maxi=MIN,mini=MAX;
	for(int i=log_n;i>=0;i--){
		if(L[a]-(1<<i)>=L[b])maxi=max(maxi,dp[i][a].second.first),mini=min(mini,dp[i][a].second.second),a=dp[i][a].first;
	}
	if(a==b)return mp(maxi,mini);
	for(int i = log_n; i >= 0; i--){
		if(dp[i][a].first!=-1 && dp[i][a].first!=dp[i][b].first){
			maxi=max(maxi,dp[i][a].second.first),mini=min(mini,dp[i][a].second.second),a=dp[i][a].first;
			maxi=max(maxi,dp[i][b].second.first),mini=min(mini,dp[i][b].second.second),b=dp[i][b].first;
		}
	}
	maxi=max(maxi,dp[0][a].second.first),mini=min(mini,dp[0][a].second.second),a=dp[0][a].first;
	maxi=max(maxi,dp[0][b].second.first),mini=min(mini,dp[0][b].second.second),b=dp[0][b].first;
	return mp(maxi,mini);
}
int main(){
	int a,b,w;
	icin(n);
	log_n=logBinary(n);
	adj.resize(n+1,vector<pii>(0));
	for(int i=1;i<n;i++){
		icin(a);icin(b);icin(w);
		adj[a].pb(mp(b,w));
		adj[b].pb(mp(a,w));
	}
	for(int i=0;i<=log_n;i++)for(int j=1;j<=n;j++)dp[i][j]=mp(-1,mp(0,0));
	DFS(1);
	process();
	int k;
	icin(k);
	for(int i=0;i<k;i++){
		icin(a);icin(b);
		auto p=LCA(a,b);
		printf("%d %d\n",p.second,p.first);
	}
	return 0;
}