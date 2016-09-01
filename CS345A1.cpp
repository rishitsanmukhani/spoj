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

struct Point{
  LL x, y;
  Point(LL _x=0.0, LL _y=0.0){
    init(_x,_y);
  }
  void init(LL _x=0.0, LL _y=0.0){
    x=_x,y=_y;
  }
  bool operator <(const Point& _)const{
    if(x!=_.x)
      return x <_.x;
    return y <_.y;
  }
  bool operator == (const Point& _)const{
   return (x==_.x && y==_.y);
  }
  void print()const{
    printf("%lld %lld\n",x,y);
  }
};

struct Event{
  // 1=h-segment-start
  // 2=vertical segment
  // 3=h-segment-end
  Point p;
  int type;
  LL y1,y2;
  void init(Point _p,int _type){
    p=_p;
    type=_type;
  }
  bool operator<(const Event& _)const{
    if(p.x!=_.p.x)
      return p.x<_.p.x;
      return type<_.type;
  }
  bool operator==(const Event& _)const{
    return (p==_.p && type==_.type);
  }
};
vector<Event> v;

//Use one based indexing
class FenwickTree{
public:
  vector<int> ft;
  int n;
  FenwickTree(int _n){
    n=_n;
    ft.assign(n+1,0);
  }
  int rsq(int b){
    int sum=0;
    for(;b;b-=LSOne(b))sum += ft[b];
    return sum;
  }
  int rsq(int a,int b){
    return rsq(b)-(a==1 ?0:rsq(a-1));
  }
  void adjust(int k,int v){
    for(;k<sz(ft);k+=LSOne(k)) ft[k]+=v;
  }
  void clear(){
    ft.assign(n,0);
  }
};
const int maxn=int(1e8)+1;
FenwickTree f(maxn);

void solve(){
  Event e;
  LL ans=0;
  for(int i=0;i<v.size();i++){
    e=v[i];
    if(e.type==1){
      f.adjust(e.p.y,1);
    }
    else if(e.type==3){
      f.adjust(e.p.y,-1);
    }
    else{
      ans += f.rsq(e.y1,e.y2);
    }
  }
  printf("%lld\n",ans);
}
int n;
int main(){
  icin(n);
  LL x1,x2,y1,y2;
  double _x1,_x2,_y1,_y2;
  Event e;
  for(int i=0;i<n;i++){
    scanf("%lf %lf %lf",&_x1,&_x2,&_y1);
    x1=_x1*double(maxn) +1;
    x2=_x2*double(maxn) +1;
    y1=_y1*double(maxn) +1;
    if(x1>x2)swap(x1,x2);
    e.init(Point(x1,y1),1);v.pb(e);
    e.init(Point(x2,y1),3);v.pb(e);
  }
  for(int i=0;i<n;i++){
    scanf("%lf %lf %lf",&_y1,&_y2,&_x1);
    y1=_y1*double(maxn) +1;
    y2=_y2*double(maxn) +1;
    x1=_x1*double(maxn) +1;
    if(y1>y2)swap(y1,y2);
    e.init(Point(x1,y1),2);
    e.y1=y1;
    e.y2=y2;
    v.pb(e);
  }
  sort(v.begin(),v.end());
  solve();
  return 0;
}



