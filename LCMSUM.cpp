#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;
 

// lcm(a, b) & gcd(a, b) = a*b
// sum(i) (s.t gcd(i, n) = 1) = n*phi(n)/2 [n>1]
// lcm(1, n) + ... + lcm(n, n) = n * (sum(d*phi(d)/2) + 1) (s.t d|n && d>1)
const int N=int(1e6);
int phi[N+1];
LL f[N+1];
void totientSieve(){
	for(int i=1;i<=N;i++)
		phi[i]=i;
	for(int j=2;j<=N;j++){
		if(phi[j]!=j)
			continue;
		for(int k = j; k<=N;k+=j)
				phi[k] -= (phi[k]/j);
	}
	phi[0]=0;
}
int main(){
	totientSieve();
	for(int i=2;i<=N;i++){
		for(int j=i;j<=N;j+=i){
			f[j] += i*LL(phi[i]);
		}
	}
	for(int i=1;i<=N;i++){
		f[i] = i*((f[i]>>1) + 1LL);
	}
	int t;
	icin(t);
	while(t--){
		int n;
		icin(n);
		printf("%lld\n", f[n]);
	}
	return 0;
}