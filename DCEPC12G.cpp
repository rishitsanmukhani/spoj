#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define push_back pb
#define make_pair mp
typedef long long LL;

const int N = int(1e7);
vector<int> phi(N+1);
void totientSieve(){
	for(int i=1;i<=N;i++)phi[i]=i;
	for(int j=2,k=2;j<=N;j++){
		if(phi[j]!=j)continue;
		k=2;
		while(j*k<=N){
			phi[j*k] -= phi[j*k]/j;
			k++;
		}
		phi[j]--;
	}
	phi[0]=0;
}

int main(){
	totientSieve();
	phi[30]=phi[30]*phi[30];
	int t;
	icin(t);
	while(t--){
		int n;
		icin(n);
		printf("%d\n", phi[n]);
	}
	return 0;
}
