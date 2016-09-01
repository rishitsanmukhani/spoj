#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef vector<int> vi;
typedef pair<int,int> pii;

const int maxn=int(1e5)+1;

int n,v;
LL single[maxn],diameter[maxn],vis[maxn];
LL ans=0;
vi adj[maxn];
struct Param2{
  int u,parent;
  Param2(int _u,int _parent){
    u=_u,parent=_parent;
  }
};
stack<Param2> st1;

void dfs(){
  st1.push(Param2(1,-1));
  while(!st1.empty()){
    Param2 param=st1.top();
    int u=param.u,parent=param.parent,v;
    if(vis[u]==0){
      for(int i=0;i<adj[u].size();i++){
        v=adj[u][i];
        if(v==parent)continue;
        st1.push(Param2(v,u));
      }
      vis[u]=1;
      continue;
    }
    if(vis[u]==1){
      st1.pop();
      LL ff=0,ss=0,bb=0,p;
      for(int i=0;i<adj[u].size();i++){
        v = adj[u][i];
        if(v==parent)continue;
        p = single[v]+1;
        bb = max(bb,diameter[v]);
        
        if(p>ff) ss=ff,ff=p;
        else if(p>ss) ss=p;
      }
      single[u] = ff;
      diameter[u] = max(bb,ff+ss);  
    }
  }
}
struct Param4{
  int u,parent;
  LL max_depth,max_so_far;
  Param4(int _u,LL _max_depth,LL _max_so_far,int _parent){
    u=_u;
    max_depth=_max_depth;
    max_so_far=_max_depth;
    parent=_parent;
  }
};

stack<Param4> st2;

void solve(){
  st2.push(Param4(1,0,0,-1));
  while(!st2.empty()){
    Param4 param=st2.top();
    st2.pop();
    int u=param.u,parent=param.parent;
    LL max_depth=param.max_depth,max_so_far=param.max_so_far;
    if(vis[u])continue;
    vis[u]=1;
    

    LL single_path[3] = {0,0,0};
    LL single_path_owner[3] = {-1, -1, -1};
    LL diameter_path[2] = {0, 0};
    LL diameter_path_owner[2] = {-1,-1};
    LL p,msf=0;
    int v;
    for(int i = 0; i<adj[u].size();i++){
      v = adj[u][i];
    
      if(v==parent)continue;

      p = single[v] + 1;
      if (p > single_path[0]){
        single_path[2] = single_path[1],single_path_owner[2] = single_path_owner[1];
        single_path[1] = single_path[0],single_path_owner[1] = single_path_owner[0];
        single_path[0] = p,single_path_owner[0] = v;
      }
      else if (p > single_path[1]){
        single_path[2] = single_path[1],single_path_owner[2] = single_path_owner[1];
        single_path[1] = p,single_path_owner[1] = v;
      }
      else if (p > single_path[2]){
        single_path[2] = p,single_path_owner[2] = v;
      }

      p = diameter[v];

      if (p > diameter_path[0]){
        diameter_path[1] = diameter_path[0],diameter_path_owner[1]=diameter_path_owner[0];
        diameter_path[0] = p,diameter_path_owner[0]=v;
      }
      else if (p > diameter_path[1]){
        diameter_path[1] = p,diameter_path_owner[1]=v;
      }
    }
    for (int i = 0; i<adj[u].size();i++){
      v = adj[u][i];
      if(v==parent)continue;
      p = (single_path_owner[0] == v) ? single_path[1] : single_path[0];

      msf = max(max_so_far, max_depth + p);
      if (single_path_owner[0] == v) msf = max(msf, single_path[1] + single_path[2]);
      else if (single_path_owner[1] == v) msf = max(msf, single_path[0] + single_path[2]);
      else msf = max(msf, single_path[0] + single_path[1]);

      if (diameter_path_owner[0] != v) msf = max(msf, diameter_path[0]);
      else msf = max(msf, diameter_path[1]);

      ans = max(ans, msf * diameter[v]);

      st2.push(Param4(v, max(max_depth,p) + 1, msf,u));
    }
  }
}
int main(){
  icin(n);
  int a,b;
  for(int i=1;i<n;i++){
    icin(a);icin(b);
    adj[a].pb(b);
    adj[b].pb(a);
  }
  memset(vis,0,sizeof vis);
  dfs();
  memset(vis,0,sizeof vis);
  solve();
  cout<<ans<<endl;
  return 0;
}