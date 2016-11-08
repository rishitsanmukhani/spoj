#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define push_back pb
#define make_pair mp
typedef long long LL;
LL power(LL b,LL e,LL mod){
	LL res = 1;
	while(e){
		if(e&1){
			res = (res*b);
			if(res>=mod)res%=mod;
		}
		e>>=1;
		b = (b*b);
		if(b>=mod)b%=mod;
	}	
	return res;
}
int main(){
	int t;
	icin(t);
	while(t--){
		LL p,n;
		scanf("%lld %lld", &n, &p);
		if(n>=p){
			printf("0\n");
			continue;
		}
		LL res = p-1;
		for(int i=p-1;i>n;i--){
			res = (res * power(i, p-2, p));
			if(res>=p)res%=p;
		}
		printf("%lld\n", res);
	}
	return 0;
}