#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair
#define sz(x) ((int)x.size())
#define LSOne(x) (x & -x)
typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> pii;

//Use one based indexing
class FenwickTree{
public:
  vvi ft;
  int n;
  FenwickTree(int _n){
    n=_n;
    ft.assign(n,vi(n,0));
  }
  int rsq(int x,int y){
    int sum=0;
    for(;x;x-=LSOne(x))sum += rsqY(x,y);
    return sum;
  }
  int rsqY(int x,int y){
    int sum=0;
    for(;y;y-=LSOne(y))sum += ft[x][y];
    return sum;
  }
  int rsq(int _x,int _y,int x,int y){
    return rsq(x,y)-rsq(x,_y-1)-rsq(_x-1,y)+rsq(_x-1,_y-1);
  }
  void update(int x,int y,int v){
    for(;x<=n;x+=LSOne(x))updateY(x,y,v);
  }
  void updateY(int x,int y,int v){
    for(;y<=n;y+=LSOne(y))ft[x][y] += v; 
  }
  void clear(){
    ft.assign(n,vi(n,0));
  }
};

const int maxn=1025;
FenwickTree f(maxn);

int A[maxn][maxn];
int main(){
  int t;
  icin(t);
  while(t--){
    f.clear();
    memset(A,0,sizeof A);

    int n,x,y,num,_x,_y;
    icin(n);
    while(1){
      char s[10];
      scanf("%s",s);
      if(s[1]=='E'){
        scanf("%d %d %d",&x,&y,&num);
        x++,y++;
        f.update(x,y,num-A[x][y]);
        A[x][y]=num;
      }
      else if(s[1]=='U'){
        scanf("%d %d %d %d",&_x,&_y,&x,&y);
        x++,y++,_x++,_y++;
        printf("%d\n",f.rsq(_x,_y,x,y));
      }
      else
        break;
    }
    printf("\n");
  }
  return 0;
}