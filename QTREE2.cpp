#include <bits/stdc++.h>

using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

const int maxn=1<<14,log_maxn=14;
int n,log_n;
pii dp[maxn][log_maxn+1];
int vis[maxn],L[maxn];
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
	int p,w;
	for(int i=0;i<adj[k].size();i++){
		p=adj[k][i].first;
		w=adj[k][i].second;
		if(vis[p])continue;
		dp[p][0]=mp(k,w);							//p is child of k, so first ancestor update
		L[p]=L[k]+1;
		DFS(p);
	}
}
void process(){
	pii p;
	int a,b;
	for(int i=1;i<=log_n;i++){
		for(int j=1;j<=n;j++){
			if(dp[j][i-1].first!=-1){
				p=dp[j][i-1];
				a=dp[p.first][i-1].first;
				b=p.second + dp[p.first][i-1].second;
				dp[j][i]=mp(a,b);
			}
		}
	}
}
pii nthAncestor(int a,int n){
	if(n>L[a])return mp(-1,0);
	int sum=0;
	for(int i=log_n;i>=0;i--){
		if((1<<i)<=n)n=n-(1<<i),sum+=dp[a][i].second,a=dp[a][i].first;
	}
	return mp(a,sum);
}
pii LCA(int a,int b){
	if(L[a]<L[b])swap(a,b);
	int sum=0;
	pii p =nthAncestor(a,L[a]-L[b]);
	a=p.first;
	sum=p.second;
	if(a==b)return mp(a,sum);
	for(int i = log_n; i >= 0; i--){
		if(dp[a][i].first!=-1 && dp[a][i].first!=dp[b][i].first){
			sum += dp[a][i].second;a=dp[a][i].first;
			sum += dp[b][i].second;b=dp[b][i].first;
		}
	}
	sum+=dp[a][0].second;a=dp[a][0].first;
	sum+=dp[b][0].second;b=dp[b][0].first;
	return mp(a,sum);
}
int main(){
	int t;
	icin(t);
	while(t--){
		int a,b,w;
		icin(n);
		log_n=logBinary(n);

		adj.assign(n+1,vector<pii>(0));
		for(int i=1;i<n;i++){
			icin(a);icin(b);icin(w);
			adj[a].pb(mp(b,w));
			adj[b].pb(mp(a,w));
		}
		memset(vis,0,sizeof vis);
		memset(L,0,sizeof L);
		for(int i=0;i<=log_n;i++)for(int j=1;j<=n;j++)dp[j][i]=mp(-1,0);
		DFS(1);
		process();
		string s;
		int k;
		while(1){
			cin>>s;
			if(s=="DONE")break;
			if(s=="DIST"){
				icin(a);icin(b);
				printf("%d\n",LCA(a,b).second);
			}
			else{
				icin(a);icin(b);icin(k);
				int anc=LCA(a,b).first;
				if((L[a]-L[anc]+1)>=k)
					printf("%d\n",nthAncestor(a,k-1).first);
				else
					printf("%d\n",nthAncestor(b,L[a]+L[b]-2*L[anc]+1-k));
			}
		}
	}
}