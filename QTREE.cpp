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

struct Edge{
  int u,v,c,idx;
  Edge(int _u=0,int _v=0,int _c=0,int _idx=0){
    u=_u;v=_v;c=_c;idx=_idx;
  }
  void print(){
    printf("%d %d %d %d\n",u,v,c,idx);
  }
};
struct Node{
  int chain_no,posn;
  int posn_in_base;
  void clear(){
    chain_no=0;
    posn=0;
    posn_in_base=0;
  }
  void print(){
    printf("%d %d %d\n",chain_no,posn,posn_in_base);
  }
};
struct Chain{
  int head,size;
  void clear(){
    head=-1;
    size=0;
  }
  void print(){
    printf("%d %d\n",head,size);
  }
};
const int maxn=1<<14,log_maxn=14;
int n,log_n,ptr;
int dp[maxn][log_maxn+1];
int vis[maxn],L[maxn],edge_to_node[maxn],subtree_size[maxn];
int base[maxn];

vector<Edge> adj[maxn];
Chain chains[maxn];
Node nodes[maxn];
int chain_no;

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
void DFS(int u){
  if(vis[u])return;
  vis[u]=1;
  subtree_size[u]=1;
  Edge e;
  for(int i=0;i<adj[u].size();i++){
    e=adj[u][i];
    if(vis[e.v]==0){
      dp[e.v][0]=u;
      L[e.v]=L[u]+1;
      edge_to_node[e.idx]=e.v;
      DFS(e.v);
      subtree_size[u] += subtree_size[e.v];
    }
  }
}
void process(){
  for(int i=1;i<=log_n;i++)
    for(int j=1;j<=n;j++)
      if(dp[j][i-1]!=-1)
        dp[j][i]=dp[dp[j][i-1]][i-1];
}
int LCA(int a,int b){
  if(L[a]<L[b])swap(a,b);
  for(int i=log_n;i>=0;i--)
    if(L[a]-(1<<i)>=L[b])
      a = dp[a][i];
  if(a==b)return a;
  for(int i = log_n; i >= 0; i--)
    if(dp[a][i]!=dp[b][i])
      a=dp[a][i],b=dp[b][i];
  a=dp[a][0];
  b=dp[b][0];
  return a;
}
void HLD(int cur, int cost){
  if(vis[cur])return;
  vis[cur]=1; 
  
  if(chains[chain_no].head==-1)
    chains[chain_no].head=cur;
  chains[chain_no].size++;
  nodes[cur].chain_no = chain_no;
  nodes[cur].posn = chains[chain_no].size;
  nodes[cur].posn_in_base = ptr;
  base[ptr]=cost;
  ptr++;

  int sc=-1,nc;
  Edge e;
  for(int i=0;i<adj[cur].size();i++){
    e=adj[cur][i];
    if(vis[e.v]==0)
      if(sc==-1 || subtree_size[sc] < subtree_size[e.v])
        sc=e.v,nc=e.c;
  }
  //Expanding the chain
  if(sc!=-1){
    HLD(sc,nc);
  }
  //Creating new chains
  for(int i=0;i<adj[cur].size();i++){
    e=adj[cur][i];
    if(vis[e.v]==0){
      chain_no++;
      HLD(e.v,e.c);
    }
  }
}

int tree[6*maxn];
void build(int from,int to,int index){
  if(from==to){
    tree[index] = base[from];
    return;
  }
  int mid = (from+to)>>1;
  build( from,mid,index<<1 );
  build( mid+1,to,(index<<1) + 1);
  
  tree[index]=max(tree[index<<1],tree[(index<<1)+1]);
}
int query(int from,int to,int index,int a,int b){
  if(from==a && to==b)return tree[index];

  int mid = (from+to)>>1;
  if(a > mid)
    return query(mid+1,to,(index<<1)+1,a,b);
  if(b <= mid)
    return query(from,mid,index<<1,a,b);

  int l = query(from,mid,index<<1,a,mid);
  int r = query(mid+1,to,(index<<1)+1,mid+1,b);

  return max(l,r);
}
void update(int from,int to,int index,int target){
  if(from==to){
    tree[index] = base[from];
    return;
  }
  int mid = (from+to)>>1;
  if(target>mid)
    update(mid+1,to,(index<<1) +1,target);
  else
    update(from,mid,index<<1,target);
  tree[index] = max(tree[index<<1],tree[(index<<1) + 1]);
}

int queryHLD(int u,int v){
  if(u == v)return 0;
  int uchain, vchain = nodes[v].chain_no,ans=-1,tmp;
  while(1){
    uchain = nodes[u].chain_no;
    if(uchain == vchain){
      if(u==v)
        break;
      tmp=query(1, n,1, nodes[v].posn_in_base+1, nodes[u].posn_in_base);
      if(tmp > ans) ans = tmp;
      break;
    }
    tmp=query(1,n,1, nodes[chains[uchain].head].posn_in_base, nodes[u].posn_in_base);
    if(tmp > ans) ans = tmp;
    u = chains[uchain].head;
    u = dp[u][0];
  }
  return ans;
}
int solve(int u,int v){
  int lca = LCA(u,v);
  return max(queryHLD(u,lca),queryHLD(v,lca));
}
void change(int i,int val){
  int u = edge_to_node[i];
  int pos = nodes[u].posn_in_base;
  base[pos]=val;
  update(1,n,1,pos);
}
int main(){
  int t;
  icin(t);
  while(t--){
    memset(vis,0,sizeof vis);
    memset(L,0,sizeof L);
    memset(edge_to_node,0,sizeof edge_to_node);
    memset(subtree_size,0,sizeof subtree_size);
    memset(base,0,sizeof base);
    memset(dp,-1,sizeof dp);      
    for(int i=0;i<maxn;i++){
      adj[i].clear();
      nodes[i].clear();
      chains[i].clear();
    }

    icin(n);
    log_n=logBinary(n);

    int a,b,w;
    for(int i=1;i<n;i++){
      scanf("%d %d %d", &a, &b, &w);
      adj[a].pb(Edge(a,b,w,i));
      adj[b].pb(Edge(b,a,w,i));
    }
    DFS(1);
    process();
    memset(vis,0,sizeof vis);
    chain_no=1;
    ptr=1;
    HLD(1,-1);
    build(1,n,1);
    while(1) {
      char s[100];
      scanf("%s", s);
      if(s[0]=='D')break;
      scanf("%d %d", &a, &b);
      if(s[0]=='Q') printf("%d\n",solve(a, b));
      else change(a,b);
    }
  }
}