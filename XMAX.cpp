#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;

LL v[int(1e5)];
int n;

LL gaussianElimination(){
	int r=0;
	LL mask=1LL<<62, res=0;
	for(;mask>=1 && r<n;mask>>=1){
		int i = r;
		while(i<n && (v[i]&mask)==0)
			i++;
		if(i>=n)
			continue;
		swap(v[r], v[i]);
		while(++i<n){
			if(v[i]&mask)v[i] ^= v[r];
		}
		res = max(res, res^v[r]);
		r++;
	}
	return res;
}
int main(){
	icin(n);
	for(int i=0;i<n;i++)lcin(v[i]);
	sort(v, v+n, greater<LL>());
	printf("%lld\n",gaussianElimination());
	return 0;
}