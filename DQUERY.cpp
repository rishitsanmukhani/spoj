#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long LL;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define BLOCK (200)
#define MAX int(1e6)

struct query{
	int l,r,i;
};
vector<int> a;
vector<query> v;
vector<int> ans;
vector<int> cnt;

bool cmp(query a,query b){
	if(a.l/BLOCK != b.l/BLOCK){
		return a.l < b.l;
	}
	return a.r<b.r;
}
int answer=0;
void add(int i){
	cnt[a[i]]++;
	if(cnt[a[i]]==1)answer++;
}
void remove(int i){
	cnt[a[i]]--;
	if(cnt[a[i]]==0)answer--;
}
int main(){
	int N,Q;
	icin(N);
	a.resize(N);
	for(int i=0;i<N;i++)icin(a[i]);
	icin(Q);
	v.resize(Q);
	for(int j=0;j<Q;j++){
		icin(v[j].l);
		icin(v[j].r);
		v[j].l--;
		v[j].r--;
		v[j].i=j;
	}

	sort(v.begin(),v.end(),cmp);
	ans.resize(Q);
	cnt.resize(MAX+1,0);
	int curL=0,curR=0,L,R;
	add(0);
	for(int i=0;i<Q;i++){
		L=v[i].l,R=v[i].r;
		while(curL<L)remove(curL),curL++;
		while(curL>L)add(curL-1),curL--;
		while(curR<R)add(curR+1),curR++;
		while(curR>R)remove(curR),curR--;
		ans[v[i].i]=answer;
	}
	for(int i=0;i<Q;i++)printf("%d\n",ans[i]);
	return 0;
}