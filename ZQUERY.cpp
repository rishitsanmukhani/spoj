#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <cassert>
using namespace std;

#define GC getchar_unlocked
int read(){
	register char c=0;
	while(c<33)c=GC();
	bool flag=0;
	if(c=='-')flag=1,c=GC();
	int a=0;
	while(c>33){
		a=(a<<3)+(a<<1)+c-48;
		c=GC();
	}
	if(flag)a=-a;
	return a;
}
#define icin(x) (x=read())
#define MAX int(5e4)
#define NMAX int(5e4)
#define BLOCK (333)
#define NBLOCKS int(ceil(float(NMAX)/BLOCK))

typedef long long LL;

int N,M,K;
int a[NMAX+2],Prev[NMAX+2],Next[NMAX+2];
int latest[MAX+2],query[MAX+2];

int last[NBLOCKS+2][MAX+2],dp[NBLOCKS+2][NMAX+2];
int main(){
	icin(N);icin(K);
	memset(Next,-1,sizeof Next);
	memset(latest,-1,sizeof latest);
	memset(query,-1,sizeof query);
	a[0]=0;
	N++;
	for(int i=1;i<N;i++){
		icin(a[i]);
		if(i)a[i]+=a[i-1];
		Prev[i]=latest[a[i]];
		if(Prev[i]!=-1)Next[Prev[i]]=i;
		latest[a[i]]=i;
	}

	int b=int(ceil(float(N)/BLOCK));
	memset(last,-1,sizeof last);
	// for(int i=1;i<=b;i++){
	// 	for(int j=0;j<min(BLOCK*i,N);j++){
	// 		last[i][a[j]]=j;
	// 	}
	// }
	for(int i=0;i<b;i++){
		for(int j=0;j<min(BLOCK*(i+1),N);j++){
			last[i+1][a[j]]=j;
		}
		int j=i*BLOCK;
		if(j>=N)break;
		dp[i][j]=0;
		latest[a[j]]=j;
		query[a[j]]=i;
		for(j=(i*BLOCK)+1;j<N;j++){
			if(query[a[j]]<i){
				latest[a[j]]=j;query[a[j]]=i;
				dp[i][j]=dp[i][j-1];
			}
			else{
				if(j-latest[a[j]] > dp[i][j-1])dp[i][j]=j-latest[a[j]];
				else dp[i][j]=dp[i][j-1];	
			}
		}
	}
	memset(query,-1,sizeof query);
	int l,r,ans;	
	int block,rblock,tmp;
	for(int i=0;i<K;i++){
		icin(l);icin(r);
		l--;r--;
		block=(l/BLOCK)+1,rblock=r/BLOCK,tmp;
		if(r<BLOCK*block){
			ans=0;
			for(int j=l;j<=r;j++){
				if(j+ans>r)break;
				tmp=last[block][a[j]];
				if(query[tmp]!=i){
					while(tmp>r)tmp=Prev[tmp];
					if((tmp-j)>ans)ans=tmp-j;
					query[tmp]=i;
				}
			}	
		}
		else{
			ans=dp[block][r];
			for(int j=l;j<block*BLOCK;j++){
				if(j+ans>r)break;
				tmp=last[rblock][a[j]];
				if(query[tmp]!=i){
					while(tmp<=r && Next[tmp]!=-1)tmp=Next[tmp];
					if(tmp>r)tmp=Prev[tmp];
					query[tmp]=i;
					if(tmp-j>ans)ans=tmp-j;
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
} 