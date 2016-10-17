#include <bits/stdc++.h>
using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;

const int N = int(1e4);
int SQ[N+1], v[N+1];

void precompute_sq(){
	SQ[1]=1;
	for(int i=2;i<=N;i++){
		if(i>=(SQ[i-1]+1)*(SQ[i-1]+1))
			SQ[i] = SQ[i-1]+1;
		else SQ[i]=SQ[i-1];

	}
}
int main(){
	precompute_sq();
	int t;
	icin(t);
	while(t--){
		int l, k;
		icin(l);icin(k);
		for(int i=1;i<=l;i++){
			v[i]=1;
		}
		while(k--){
			v[l]--;
			v[SQ[l]]++;
			if(v[l]==0)l--;
		}
		int res=0;
		for(int i=1;i<=l;i++){
			res += v[i]*i;
		}
		printf("%d\n", res);
	}
	return 0;
}