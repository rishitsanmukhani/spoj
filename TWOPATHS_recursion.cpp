//This code involves recursion, but will give run time error because of limited c++ recursion depth.
//We thus use modified code implementing recursion using stack

#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair
typedef long long LL;
typedef vector<int> vi;
typedef pair<int,int> pii;

const int maxn=int(1e6)+1;

int n;
//single[i] = largest path from root in subtree of i
//diameter[i] = diameter of subtree of i
LL single[maxn],diameter[maxn];

vi adj[maxn];

void dfs(int u,int parent){  
  LL ff=0,ss=0,bb=0,p;
  int v;
  for(int i=0;i<adj[u].size();i++){
    v=adj[u][i];
    if(v==parent)continue;

    dfs(v,u);
    
    p = single[v]+1;
    bb = max(bb,diameter[v]);
    
    if(p>ff) ss=ff,ff=p;
    else if(p>ss) ss=p;
  }
  single[u] = ff;
  diameter[u] = max(bb,ff+ss);
}
LL ans=0;
void solve(int u,LL max_depth,LL max_so_far,int parent){
  assert(1<=u && u<=n);
  //single_path[i] = ith largest path
  //single_path_owner[i] = child owner of ith largest path
  LL single_path[3] = {0,0,0};
  LL single_path_owner[3] = {-1, -1, -1};
  //diameter[i] = ith largest diameter
  LL diameter_path[2] = {0, 0};
  LL diameter_path_owner[2] = {-1,-1};
  LL p,msf=0;
  int v;
  for(int i = 0; i<adj[u].size();i++){
    v = adj[u][i];
    assert(1<=v && v<=n);

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
    assert(1<=v && v<=n);
    if(v==parent)continue;
    p = (single_path_owner[0] == v) ? single_path[1] : single_path[0];

    msf = max(max_so_far, max_depth + p);
    if (single_path_owner[0] == v) msf = max(msf, single_path[1] + single_path[2]);
    else if (single_path_owner[1] == v) msf = max(msf, single_path[0] + single_path[2]);
    else msf = max(msf, single_path[0] + single_path[1]);

    if (diameter_path_owner[0] != v) msf = max(msf, diameter_path[0]);
    else msf = max(msf, diameter_path[1]);

    ans = max(ans, msf * diameter[v]);

    //max depth will be either from the root or to one of the children, which ever is maximum
    solve(v, max(max_depth,p) + 1, msf,u);
  }
}
int main(){
  icin(n);
  assert(n>=2 && n<=int(1e5));
  int a,b;
  for(int i=1;i<n;i++){
    icin(a);icin(b);
    assert(a>=1 && a<=n);
    assert(b>=1 && b<=n);
    adj[a].pb(b);
    adj[b].pb(a);
  }
  dfs(1,-1);
  for(int i=1;i<=n;i++){
    cout<<single[i]<<" "<<diameter[i]<<endl;
  }
  solve(1,0,0,-1);
  cout<<ans<<endl;
  return 0;
}