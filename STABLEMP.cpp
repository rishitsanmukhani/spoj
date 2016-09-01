#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <string>
#include <cstdlib>
#include <stack>

using namespace std;

typedef long long LL;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)

int W[501][501],M[501][501];
vector<int> mar;

int main(){
	int T;
	icin(T);
	while(T--){
		int N,tmp;
		icin(N);
		for(int i=1;i<=N;i++){
			icin(tmp);
			W[i][0]=0;
			for(int j=1;j<=N;j++){
				icin(tmp);
				W[i][tmp]=j;
			}
		}
		for(int i=1;i<=N;i++){
			icin(tmp);
			M[i][0]=0;
			for(int j=1;j<=N;j++){
				icin(M[i][j]);
			}
		}
		mar.resize(N+1,0);
		stack<int> fmen;
		for(int i=1;i<=N;i++)fmen.push(i);
		int m,w;
		while(!fmen.empty()){
			m=fmen.top();fmen.pop();
			
			M[m][0]++;
			w=M[m][M[m][0]];

			if(W[w][0]==0){
				mar[m]=w;
				W[w][0]=m;
			}
			else{
				if(W[w][W[w][0]]<W[w][m]){
					fmen.push(m);
				}
				else{
					fmen.push(W[w][0]);
					W[w][0]=m;
					mar[m]=w;
				}
			}
		}
		for(int i=1;i<=N;i++){
			printf("%d %d\n",i,mar[i]);
		}
	}
	return 0;
}