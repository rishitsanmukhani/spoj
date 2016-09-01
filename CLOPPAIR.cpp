#include <bits/stdc++.h>

using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define REP(i,a,b) for(int i=a;i<b;i++)
#define iREP(i,a,b) for(int i=a;i>b;i--)
#define pb push_back
#define mp make_pair

#define INF (1e9)
#define EPS (1e-9)
#define PI (acos(-1.0))

typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;
typedef vector<pii> vpii;

struct Point{
  double x, y;
  int id;
  Point(double _x=0.0, double _y=0.0){
    init(_x,_y);
  }
  void init(double _x=0.0, double _y=0.0){
    x=_x,y=_y;
  }
  bool operator <(const Point& _)const{
    if(fabs(x - _.x)> EPS)
      return x <_.x;
    return y <_.y;
  }
  bool operator == (const Point& _)const{
   return (fabs(x - _.x)<EPS && (fabs(y - _.y)<EPS));
  }
  void print()const{
    printf("%f %f %d\n",x,y,id);
  }
};
struct comp{
  bool operator() (const Point& p1,const Point& p2){
    if(fabs(p1.y - p2.y)> EPS)
      return p1.y < p2.y;
    return p1.x < p2.x;
  }
};
double dist_sq(const Point& p1,const Point& p2){
  return (p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y);
}
vector<Point> P;
set<Point,comp> s;
int n;

void solve(){
  sort(P.begin(),P.end());
  double ans=INF;
  int idx=0,a=-1,b=-1;
  for(int i=0;i<n;i++){
    double x=P[i].x,y=P[i].y;
    while(idx<i && ((x-P[idx].x) - ans)>-EPS){
      s.erase(P[idx]),idx++;
    }
    auto it=s.lower_bound(Point(-INF,y-ans));
    while(it!=s.end() && (fabs(it->y-y)-ans)<EPS){
      double d = dist_sq(*it,P[i]);
      if(d - ans < EPS){
        ans = d,a=it->id,b=P[i].id;
      }
      ++it;
    }
    s.insert(P[i]);
  }
  if(a>b)swap(a,b);
  printf("%d %d %0.6f\n",a,b,sqrt(ans));
}

int main(){
  icin(n);
  double x,y;
  for(int i=0;i<n;i++){
    scanf("%lf %lf",&x,&y);
    P.pb(Point(x,y));
    P[i].id=i;
  }
  solve();
  return 0;
}



