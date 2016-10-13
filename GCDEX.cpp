#include <bits/stdc++.h>
using namespace std;
 
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;
 
// gcd(1, n) + ... + gcd(n-1, n) = sum(d*phi(n/d)) (s.t d | n && d!=1) 
const int N=int(1e6);
vector<LL> phi(N+1), f(N+1), psum(N+1);
void totientSieve(){
	for(int i=1;i<=N;i++)
		phi[i]=i;
	for(int j=2,k=2;j<=N;j++){
		if(phi[j]!=j)continue;
		k=2;
		while(j*k<=N){
			phi[j*k]=(phi[j*k] *(j-1))/j;
			k++;
		}
		phi[j]--;
	}
	phi[0]=0;
}
int main(){
	totientSieve();
	for(int i=1;i<=N;i++){
		for(int j=2;j*i<=N;j++){
			f[i*j] += i*phi[j];
		}
	}
	for(int i=1;i<=N;i++){
		psum[i] = psum[i-1] + f[i];
	}
	while(1){
		int n;
		icin(n);
		if(n==0)return 0;
		printf("%lld\n", psum[n]);
	}
	return 0;
}