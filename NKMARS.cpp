#include <bits/stdc++.h>

using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define iREP(i,a,b) for(int i=a;i>b;i--)
#define pb push_back
#define mp make_pair
#define sz(x) ((int)x.size())
#define LSOne(x) (x & -x)

#define INF (1e9)
#define EPS (1e-9)
#define PI (acos(-1.0))

typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

struct Event{
  // 1 = left
  // 2 = right
  int type;
  LL x,y1,y2;
  int id;
  void init(LL _x,int _type,LL _y1,LL _y2){
    x=_x;y1=_y1,y2=_y2;
    type=_type;
  }
  bool operator<(const Event& _)const{
    if(x!=_.x)
      return x<_.x;
      return type<_.type;
  }
  bool operator==(const Event& _)const{
    return (x==_.x && type==_.type);
  }
};
vector<Event> v;
int n;
const int max_range=int(3e4)+100;
int R[max_range]={0};
LL range(){
  LL ans=0;
  LL pre_y=-1;
  for(int i=0;i<max_range;i++){
    if(R[i]){
      if(pre_y==-1)pre_y=i;
    }
    else{
      if(pre_y!=-1)ans += (i-1-pre_y);
      pre_y=-1;
    }
  }
  return ans;
}
void mark(int a,int b){
  for(int i=a;i<=b;i++)R[i]++;
}
void unmark(int a,int b){
  for(int i=a;i<=b;i++)R[i]--;
}
void solve(){
  Event e;
  LL ans=0;
  LL prev_x=-1,x;
  for(int i=0;i<v.size();i++){
    e=v[i];
    x=e.x;
    if(prev_x==-1)prev_x=x;
    ans += range()*(x-prev_x);
    prev_x=x;
    if(e.type==1){
      mark(e.y1,e.y2);
    }
    else if(e.type==2){
      unmark(e.y1,e.y2);
    }
  }
  printf("%lld\n",ans);
}

int main(){
  icin(n);
  LL x1,x2,y1,y2;
  Event e;
  for(int i=1;i<=n;i++){
    scanf("%lld %lld %lld %lld",&x1,&y1,&x2,&y2);
    e.init(x1,1,y1,y2);
    e.id=i;v.pb(e);
    e.init(x2,2,y1,y2);
    e.id=i;v.pb(e);
  }
  sort(v.begin(),v.end());
  solve();
  return 0;
}



