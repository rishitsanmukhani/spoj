#include <bits/stdc++.h>

using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define F first
#define S second
#define pb push_back
#define mp make_pair
#define popcount __builtin_popcount
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int,int> pii;

const int maxm=20,maxn=100;
pii loc[maxm];
pair<pii,int> sol[maxn];
bitset<maxn> can[maxm];

inline int square(int n){
	return n*n;
}

int main(){
	int k,r,m;
	icin(k);icin(r);icin(m);
	r*=r;
	for(int i=0;i<m;i++){
		icin(loc[i].F);icin(loc[i].S);
	}
	int n;
	icin(n);
	for(int i=0;i<n;i++){
		icin(sol[i].F.F);icin(sol[i].F.S);
		icin(sol[i].S);
		for(int j=0;j<m;j++){
			if(square(sol[i].F.F-loc[j].F)+square(sol[i].F.S-loc[j].S)<=r)
				can[j][i]=1;
			else
				can[j][i]=0;
		}
	}
	int maxi=0,cnt=0;
	for(int mask=0;mask<(1<<m);mask++){
		if(popcount(mask)!=k)continue;
		bitset<100> b;
		for(int i=0;i<m;i++){
			if(mask & (1<<i))
				b |= can[i];
		}
		cnt=0;
		for(int i=0;i<n;i++)
			if(b[i])cnt+=sol[i].S;
		maxi=max(maxi,cnt);
	}

	printf("%d\n",maxi);
	return 0;
}