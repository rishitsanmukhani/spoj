#include <bits/stdc++.h>

using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair
#define INF (int(1e9))
typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

struct Node{
  int chain_no,posn;
  int posn_in_base;
  Node(int _chain_no=0,int _posn=0,int _posn_in_base=0){
    chain_no=_chain_no,posn=_posn,posn_in_base=_posn_in_base;
  }
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
  Chain(int _head=-1,int _size=0){
    head=_head,size=_size;
  }
  void print(){
    printf("%d %d\n",head,size);
  }
};
const int maxn=1<<17,log_maxn=17;
int n,log_n,ptr;
int dp[maxn][log_maxn+1];
int vis[maxn],L[maxn],subtree_size[maxn];
int base[maxn],color[maxn];

vector<int> adj[maxn];
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
  int v;
  for(int i=0;i<adj[u].size();i++){
    v=adj[u][i];
    if(vis[v]==0){
      dp[v][0]=u,L[v]=L[u]+1;
      DFS(v);
      subtree_size[u] += subtree_size[v];
    }
  }
}
void process(){
  for(int i=1;i<=log_n;i++)
    for(int j=1;j<=n;j++)
      if(dp[j][i-1]!=-1)
        dp[j][i]=dp[dp[j][i-1]][i-1];
}
int nthAncestor(int a,int n){
  if(n>L[a])return -1;
  for(int i=log_n;i>=0;i--){
    if((1<<i)<=n)n=n-(1<<i),a=dp[a][i];
  }
  return a;
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
void HLD(int cur, int value){
  if(vis[cur])return;
  vis[cur]=1; 
  
  if(chains[chain_no].head==-1)
    chains[chain_no].head=cur;
  chains[chain_no].size++;
  nodes[cur].chain_no = chain_no;
  nodes[cur].posn = chains[chain_no].size;
  nodes[cur].posn_in_base = ptr;
  base[ptr]=value;
  ptr++;

  int sc=-1,nc;
  int v;
  for(int i=0;i<adj[cur].size();i++){
    v=adj[cur][i];
    if(vis[v]==0)
      if(sc==-1 || subtree_size[sc] < subtree_size[v])
        sc=v,nc= color[v] ? INF:L[v];
  }
  //Expanding the chain
  if(sc!=-1){
    HLD(sc,nc);
  }
  //Creating new chains
  for(int i=0;i<adj[cur].size();i++){
    v=adj[cur][i];
    if(vis[v]==0){
      chain_no++;
      HLD(v,color[v]?INF:L[v]);
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
  
  tree[index]=min(tree[index<<1],tree[(index<<1)+1]);
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

  return min(l,r);
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
  tree[index] = min(tree[index<<1],tree[(index<<1) + 1]);
}

int queryHLD(int u,int v){
  int uchain, vchain = nodes[v].chain_no,ans=INF,tmp;
  while(1){
    uchain = nodes[u].chain_no;
    if(uchain == vchain){
      tmp = query(1, n,1, nodes[v].posn_in_base, nodes[u].posn_in_base);
      ans = min(ans,tmp);
      break;
    }
    tmp=query(1,n,1, nodes[chains[uchain].head].posn_in_base, nodes[u].posn_in_base);
    ans = min(ans,tmp);
    u = chains[uchain].head;
    u = dp[u][0];
  }
  return ans;
}
int solve(int u){
  int ans=queryHLD(u,1);
  return (ans==INF)?-1:ans;
}
void change(int u){
  int pos = nodes[u].posn_in_base;
  if(color[u])base[pos]=L[u],color[u]=0;
  else base[pos]=INF,color[u]=1;
  update(1,n,1,pos);
}
int main(){
  memset(dp,-1,sizeof dp);
  int q;
  icin(n);
  icin(q);
  log_n=logBinary(n);

  int a,b;
  for(int i=1;i<n;i++){
    scanf("%d %d", &a, &b);
    adj[a].pb(b);
    adj[b].pb(a);
  }
  fill(color,color+maxn,1);
  
  DFS(1);
  process();
  memset(vis,0,sizeof vis);
  chain_no=1;
  ptr=1;
  HLD(1,INF);
  build(1,n,1);
  for(int i=0;i<q;i++){
    scanf("%d %d", &a, &b);
    if(a){
      int l=solve(b);
      if(l==-1) printf("-1\n");
      else printf("%d\n",nthAncestor(b,L[b]-l));
    }
    else change(b);
  }
  return 0;
}