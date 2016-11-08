#include <bits/stdc++.h>
using namespace std;

#define GC getchar_unlocked
int read(){
	register char c=0;
	while(c<33)c=GC();
	int a =0;
	while(c>33){
		a=a*10+c-48;
		c=GC();
	}
	return a;
}

#define icin(x) (x=read())
#define pb push_back
#define mp make_pair
#define sz(x) ((int)x.size())
#define LSOne(x) (x & -x)

typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

//Use one based indexing
class FenwickTree{
public:
  vector<int> ft;
  int n;
  FenwickTree(int _n):n(_n){
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
    ft.assign(n+1,0);
  }
};

const int maxn=int(3e4)+1;
FenwickTree f(maxn);

struct Query{
	int id;
	int i, j, k;
};
vector<Query> query;
vi ans;
vpii a;
int main(){
	int n;
	icin(n);
	a.resize(n);
	for(int i=0;i<n;i++){
		icin(a[i].first);
		a[i].second = i+1;
	}
	sort(a.begin(), a.end(), greater<pair<int, int> >());
	int q;
	icin(q);
	query.resize(q);
	ans.resize(q);
	for(int i=0;i<q;i++){
		query[i].id = i;
		icin(query[i].i);
		icin(query[i].j);
		icin(query[i].k);
	}
	sort(query.begin(), query.end(), [](const Query& a, const Query& b){return a.k>b.k;});
	int idx=0;
	for(int i=0;i<q;i++){
		int k = query[i].k;
		while(idx<n && a[idx].first > k){
			f.adjust(a[idx].second, 1);
			idx++;
		}
		ans[query[i].id] = f.rsq(query[i].i, query[i].j);
	}
	for(auto a:ans){
		printf("%d\n", a);
	}
	return 0;
}