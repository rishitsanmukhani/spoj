#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef vector<int> vi;
typedef pair<int,int> pii;

const int maxn=61;

int n,k;
vi adj[maxn];
//dp1[i][j] = #subtrees rooted at i and longest path length <= j(with root as end point) and diameter <=k
LL dp1[maxn][maxn];
//dp2[i][j] = #subtrees rooted at i and longest path length = j(with root as end point) and diameter <=k
LL dp2[maxn][maxn];
LL suff[maxn],pref[maxn];

void dfs(int u,int p){
  int v,v1,v2;
  vi children;
  for(int i=0;i<adj[u].size();i++){
    v=adj[u][i];
    if(v==p)continue;
    dfs(v,u);
    children.pb(v);
  }

  dp1[u][0]=1;
  dp2[u][0]=1;

  for(int j=1;j<=k;j++){
    int a=min(j-2,k-j-1),b=min(j-1,k-j-1);
    
    //precomputation
    fill(pref,pref+children.size(),1);
    fill(suff,suff+children.size(),1);
    if(a>=0){
      for(int m=0;m<children.size();m++){
        v1=children[m];
        if(m==0)
          pref[m]=(1+dp1[v1][a]);
        else
          pref[m] = pref[m-1]*(1+dp1[v1][a]);
      }
    }
    if(b>=0){
      for(int n=children.size()-1;n>=0;n--){
        v2=children[n];
        if(n==children.size()-1) suff[n]=(1+dp1[v2][b]);
        else suff[n]=suff[n+1]*(1+dp1[v2][b]);
      }
    }
    
    //Iterate over children, suppose mth child has j-1 path (all <m has min(j-2,k-j-1) and >m has min(j-1,k-j-1))
    for(int m=0;m<children.size();m++){
      v=children[m];
      LL tmp=dp2[v][j-1];
      if(m>0)tmp*=pref[m-1];
      if(m<children.size()-1)tmp*=suff[m+1];
      dp2[u][j] += tmp;
    }
    dp1[u][j] = dp2[u][j]+dp1[u][j-1];
  }
}
int main(){
  int t;
  icin(t);
  while(t--){
    memset(dp1,0,sizeof dp1);
    memset(dp2,0,sizeof dp2);
    memset(pref,0,sizeof pref);
    memset(suff,0,sizeof suff);
    for(int i=0;i<maxn;i++)adj[i].clear();
    icin(n);icin(k);
    int a,b;
    for(int i=1;i<n;i++){
      icin(a);icin(b);
      adj[a].pb(b);
      adj[b].pb(a);
    }
    dfs(0,-1);
    LL ans=0;
    for(int i=0;i<n;i++){
      ans += (dp1[i][k]);
    }
    cout<<ans<<endl;
  }
  return 0;

}