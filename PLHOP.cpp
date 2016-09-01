#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;
LL MOD=1;
int N;

void mult(LL A[50][50],LL B[50][50],LL C[50][50]){
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			C[i][j]=(A[i][0]+B[0][j]);
			for(int k=1;k<N;k++){
				C[i][j] = min(C[i][j],(A[i][k]+B[k][j]));
			}
		}
	}
}

void power(LL A[50][50],int p,LL B[50][50]){
	if(p==1){
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				B[i][j]=A[i][j];
	}else if(p%2==0){
		LL C[50][50];
		power(A,p/2,C);
		mult(C,C,B);
	}
	else{
		LL C[50][50];
		power(A,(p-1)/2,B);
		mult(B,B,C);
		mult(A,C,B);
	}
}

LL A[50][50],ans1[50][50],ans2[50][50];

int main()
{
	int T,k;
	icin(T);
	for(int z=1;z<=T;z++)
	{
		icin(k);
		icin(N);
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				lcin(A[i][j]);
		power(A,k,ans1);
		ans2 = ans1*A;

		printf("Region #%d:\n",z);
		for(int i=0;i<N;i++){
			int j;
			for(j=0;j<N-1;j++)
				printf("%lld ",min(ans1[i][j],ans2[i][j]));
			printf("%lld\n",min(ans1[i][j],ans2[i][j]));
		}
		printf("\n");
	}
	return 0;
}