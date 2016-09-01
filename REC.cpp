#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;

#define lcin(x) scanf("%lld",&x)
typedef long long LL;
LL MOD=1;

void mult(LL A[2][2],LL B[2][2],LL C[2][2]){
	for(int i=0;i<2;i++){
		for(int j=0;j<2;j++){
			C[i][j]=0;
			for(int k=0;k<2;k++){
				C[i][j] = (C[i][j] + A[i][k]*B[k][j] )%MOD;
			}
		}
	}
}

int start=0,end;

void divide(char p[110]){
	int carry=0,digit=0;
	for(int i=start;i<=end;i++){
		digit = carry*10 + (p[i]-'0');
		p[i] = (digit>>1) + '0';
		if(digit%2==0)
		carry=0;
		else
		carry=1;
	}
	if(p[start]=='0')
	start++;
}
void sub(char p[110]){
	for(int i=end;i>=start;i--)
	{
		if(p[i]!='0')
		{
			p[i] = p[i]-1;
			break;
		}
		p[i]='9';
	}
	if(p[start]=='0'){
		start++;
	}
}
void power(LL A[2][2],char p[110],LL B[2][2]){
	if(p[start]=='1' && start==end){
		for(int i=0;i<2;i++)
			for(int j=0;j<2;j++)
				B[i][j]=A[i][j];
	}else if((p[end]-'0')%2 == 0){
		LL C[2][2];
		divide(p);
		power(A,p,C);
		mult(C,C,B);
	}
	else{
		LL C[2][2];
		sub(p);
		divide(p);
		power(A,p,B);
		mult(B,B,C);
		mult(A,C,B);
	}
}
int getVal(char s[110]){
	int l = strlen(s);
	int val=0;
	for(int i=0;i<l;i++){
		val = (val*10 + s[i]-'0')%MOD;
	}
	return val;
}

char A[110],B[110],N[110];
int main()
{
	int T,a,b,n;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%s",A);
		scanf("%s",B);
		scanf("%s",N);
		lcin(MOD);

		if(N[0]=='0' && strlen(N)==1){
			printf("%lld\n",1%MOD);
			continue;
		}
		a = getVal(A);
		b = getVal(B);

		end = strlen(N)-1;
		LL A[2][2],B[2][2];
		A[0][0]=a;
		A[0][1]=b;
		A[1][0]=0;
		A[1][1]=1;
		start=0;
		power(A,N,B);
		LL ans = (B[0][0] + B[0][1])%MOD;
		printf("%lld\n",ans);
	}
	return 0;
}