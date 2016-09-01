#include <bits/stdc++.h>
using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI (acos(-1.0))

#define icin(x) scanf("%d",&x)

double DEG_to_RAD(double d){ return d * PI / 180.0; }

double RAD_to_DEG(double r){ return r * 180.0 / PI; }

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

struct Vec{
  double x, y;
  Vec(double _x=0.0, double _y=0.0): x(_x), y(_y){}
};

// convert 2 points to Vector a->b
Vec toVec(Point a, Point b){
  return Vec(b.x - a.x, b.y - a.y);
}

Vec scale(Vec v, double s){
  return Vec(v.x * s, v.y * s);
}

// translate p according to v
Point translate(Point p, Vec v){
  return Point(p.x + v.x , p.y + v.y);
}

double dot(Vec a, Vec b){
  return (a.x * b.x + a.y * b.y);
}

double norm_sq(Vec v){
  return v.x * v.x + v.y * v.y;
}
// angle AOB in rad
double angle(Point a, Point o, Point b){
  Vec oa = toVec(o, a), ob = toVec(o, b);
  return acos(dot(oa, ob)/ sqrt(norm_sq(oa)* norm_sq(ob)));
}

double cross(Vec a, Vec b){
  return a.x * b.y - a.y * b.x;
}

// returns true if point r is on the left side of line pq
bool ccw(Point p, Point q, Point r){
  return cross(toVec(p, q), toVec(p, r))> 0;
}

bool collinear(Point p, Point q, Point r){
  return fabs(cross(toVec(p, q), toVec(p, r)))<EPS;
}

Point pivot;
bool angleCmp(Point a, Point b){
  if (collinear(pivot, a, b))
    return dist(pivot, a) < dist(pivot, b);
  double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
  double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
  return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0;
}

vector<Point> CH(vector<Point> P){
  int i, j, n = (int)P.size();
  //Corner case of <=3 points (the convex hull is itself)
  if (n <= 3){
    if (!(P[0] == P[n-1])) P.push_back(P[0]);
    return P;
  }

  // P0 = Point with lowest Y and if tie: rightmost X
  int P0 = 0;
  for (i = 1; i < n; i++)
    if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
      P0 = i;

  swap(P[0],P[P0]); // Now P[0] is the pivot

  // Sort points by angle w.r.t. pivot P0
  pivot = P[0];
  sort(++P.begin(), P.end(), angleCmp);    // Do not sort P[0]

  //  ccw tests
  vector<Point> S;
  S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);   // initial S
  i = 2;                                         // then, we check the rest
  while (i < n){           // Note: N must be >= 3
    j = (int)S.size()-1;
    if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);  // left turn, accept
    else S.pop_back();
  }   // or pop the top of S until we have a left turn
  return S;
}
vector<Point> P,S;

double perimeter(const vector<Point> &P){
  double result = 0.0;
  for (int i = 0; i < (int)P.size()-1; i++)
    result += dist(P[i], P[i+1]);
  return result;
}

int main(){
  int n;
  icin(n);
  P.resize(n);
  for(int i=0;i<n;i++){
    scanf("%lf %lf",&P[i].x,&P[i].y);
  }
  S = CH(P);
  cout<<round(perimeter(S))<<endl;
  return 0;
}