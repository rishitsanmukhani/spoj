#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;


#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair

const int N = 100000;
vector<int> is_prime(N+1);
void sieve(){
	fill(is_prime.begin(),is_prime.end(),1);
	for(int j=2,k=2;j<=N;j++){
		if(is_prime[j]==0)continue;
		k=2;
		while(j*k<=N){
			is_prime[j*k]=0;k++;
		}
	}
	is_prime[0]=is_prime[1]=0;
}
vector<int> dist(int(1e5));
int a,b;


void bfs(int n){
	queue<int> q;
	dist[n]=0;
	q.push(n);
	while(!q.empty()){
		int val = q.front(),num;
		q.pop();
		string tmp;
		for(int j=0;j<4;j++){
			itoa(val,(char*)tmp.c_str(),10);
			for(int i=0;i<10;i++){
				tmp[j]=i+'0';
				num=atoi(tmp.c_str());

				if((!is_prime[num]) || val==num || dist[num]!=-1 || num<1000)continue;
				dist[num] = dist[val]+1;
				q.push(num);
			}
		}
		if(dist[b]!=-1)return;
	}
}
int main(){
	sieve();
	int T;
	icin(T);
	while(T--){
		icin(a);
		icin(b);
		fill(dist.begin(),dist.end(),-1);
		bfs(a);
		printf("%d\n",dist[b]);
	}
	return 0;
}