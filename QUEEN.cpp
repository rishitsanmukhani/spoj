#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define gc getchar
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair
#define MAX 10000000

#define SET(x,i) (x|=(1<<i))
#define CHK(x,i) !(bool(x & (1<<i)))
int row,col;
int N,M;
char v[1002][1002];
int dist[1002][1002],last[1002][1002];

void check(int r,int c,queue<pair<int,int> >& q,int d,int l){
	if(v[r][c]!='X'){
		if(dist[r][c]==MAX)q.push(mp(r,c));
		if(dist[r][c]>d){
			dist[r][c]=d;
			last[r][c]=0;
			SET(last[r][c],l);	
			return;
		}
		if(dist[r][c]==d){
			SET(last[r][c],l);
			return;
		}
	}
}

int bfs(int r,int c){
	queue<pair<int,int> > q;
	q.push(mp(r,c));
	dist[r][c]=0;
	while(!q.empty()){
		r=q.front().first;
		c=q.front().second;
		q.pop();
		check(r-1,c,q,dist[r][c] + int(CHK(last[r][c],0)),0);
		check(r-1,c+1,q,dist[r][c] + int(CHK(last[r][c],1)),1);
		check(r,c+1,q,dist[r][c] + int(CHK(last[r][c],2)),2);
		check(r+1,c+1,q,dist[r][c] + int(CHK(last[r][c],3)),3);
		check(r+1,c,q,dist[r][c] + int(CHK(last[r][c],4)),4);
		check(r+1,c-1,q,dist[r][c] + int(CHK(last[r][c],5)),5);
		check(r,c-1,q,dist[r][c] + int(CHK(last[r][c],6)),6);
		check(r-1,c-1,q,dist[r][c] + int(CHK(last[r][c],7)),7);
		if(v[r][c]=='F')
			return dist[r][c];
	}
	return -1;
}

int main(){
	int T;
	icin(T);
	while(T--){
		icin(N);icin(M);
		for(int j=0;j<=M+1;j++){
			v[0][j]=v[N+1][j]='X';
			last[0][j]=last[N+1][j]=0;
			dist[0][j]=dist[N+1][j]=MAX;
		}
		gc();
		for(int i=1;i<=N;i++){
			v[i][0]='X';last[i][0]=0;dist[i][0]=MAX;
			for(int j=1;j<=M;j++){
				v[i][j]=gc();
				last[i][j]=0;
				dist[i][j]=MAX;
				if(v[i][j]=='S')row=i,col=j;
			}
			gc();
			v[i][M+1]='X';
			last[i][M+1]=0;
			dist[i][M+1]=MAX;
		}
		printf("%d\n",bfs(row,col));
	}
	return 0;
}