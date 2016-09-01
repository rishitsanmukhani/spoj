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
};

double dist(Point p1, Point p2){
  return hypot(p1.x - p2.x, p1.y - p2.y);
}
struct Line{
  double a, b, c;
  Line(double _a=0.0,double _b=0.0,double _c=0.0){
    init(_a,_b,_c);
  }
  void init(double _a=0.0,double _b=0.0,double _c=0.0){
    a=_a,b=_b,c=_c;
  }
};
bool areParallel(Line l1, Line l2){
  return (fabs(l1.a-l2.a)<EPS) && (fabs(l1.b-l2.b)<EPS);
}
bool areSame(Line l1, Line l2){
  return areParallel(l1 ,l2) && (fabs(l1.c - l2.c)<EPS);
}
bool areIntersect(Line l1, Line l2, Point &p){
  if(areParallel(l1, l2))
    return false;
  p.x = (l2.b * l1.c - l1.b * l2.c)/ (l2.a * l1.b - l1.a * l2.b);
  if(fabs(l1.b)> EPS)
    p.y = -(l1.a * p.x + l1.c);
  else
    p.y = -(l2.a * p.x + l2.c);
  return true;
}
void pointsToLine(Point p1, Point p2, Line &l){
  if(fabs(p1.x - p2.x)<EPS){              // vertical line
    l.init(1.0,0.0,-p1.x);
  }
  else{
    l.a = -(double)(p1.y - p2.y)/(p1.x - p2.x);
    l.b = 1.0;                            // Fix b = 1.0
    l.c = -(double)(l.a * p1.x)- p1.y;
  }
}

int main(){
  int t;
  icin(t);
  while(t--){
    Point p1,p2,p3,p4;
    Line l1,l2;
    scanf("%lf %lf %lf %lf",&p1.x,&p1.y,&p2.x,&p2.y);
    pointsToLine(p1,p2,l1);
    scanf("%lf %lf %lf %lf",&p3.x,&p3.y,&p4.x,&p4.y);
    pointsToLine(p3,p4,l2);
    if(p1==p2 && p3==p4){
      if(p1==p3)
        printf("POINT\n");
      else
        printf("NO\n");
      continue;
    }
    else if(p1==p2){
      if(fabs(dist(p1,p3) + dist(p1,p4)-dist(p3,p4))<EPS)
        printf("POINT\n");
      else
        printf("NO\n");
      continue;
    }
    else if(p3==p4){
      if(fabs(dist(p1,p3) + dist(p2,p3)-dist(p1,p2))<EPS)
        printf("POINT\n");
      else
        printf("NO\n");
      continue;
    }
    Point p;
    bool flag = areIntersect(l1,l2,p);
    if(flag){
      double d=dist(p1,p2),d1=dist(p,p1),d2=dist(p,p2);
      bool status=true;
      if(fabs(d - (d1+d2))>EPS)
        status=false;
      d=dist(p3,p4),d1=dist(p,p3),d2=dist(p,p4);
      if(fabs(d - (d1+d2))>EPS)
        status=false;
      if(status)
        printf("POINT\n");
      else
        printf("NO\n");
    }
    else{
      bool status=areSame(l1,l2);
      if(status){
        if(p2<p1)swap(p1,p2);
        if(p4<p3)swap(p3,p4);
        if(p3<p1)swap(p1,p3),swap(p2,p4);
        if(p2==p3)
          printf("POINT\n");
        else if(p3<p2)
          printf("SEGMENT\n");
        else
          printf("NO\n");
      }
      else{
        printf("NO\n");
      }
    }
  }
  return 0;
}



