#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define push_back pb
#define make_pair mp
typedef long long LL;

const int maxn=int(1e5);
int A[maxn],ans[maxn];

int p[31];
void precompute_power(){
	p[0]=1;
	for(int i=1;i<31;i++)p[i] = p[i-1]<<1;
}

int val[31];
int add(int a){
	int res=0;
	for(int i=0;i<31;i++){
		val[i] += int(bool(p[i] & a));
		if(val[i]==0)res+=p[i];
	}
	return res;
}
void rem(int a){
	for(int i=0;i<31;i++){
		val[i] -= int(bool(p[i] & a));
	}	
}
int main(){
	precompute_power();
	int t;
	icin(t);
	while(t--){
		int n,k;
		icin(n);icin(k);
		for(int i=0;i<n;i++){
			icin(A[i]);
		}
		if(k>=(n>>1)){
			k=(n>>1);
		}
		for(int i=0;i<31;i++)val[i]=-(k<<1)-1;

		for(int i=-k;i<=k;i++){
			ans[0] = add(A[(n+i)%n]);
		}
		for(int i=1;i<n;i++){
			rem(A[(n + i-k-1)%n]);
			ans[i] = add(A[(i+k)%n]);
		}
		for(int i=0;i<n;i++)
			printf("%d ",ans[i]);
		printf("\n");
	}
	return 0;
}