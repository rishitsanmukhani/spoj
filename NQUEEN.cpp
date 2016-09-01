//Solution without using dancing links(without reducing to exact cover problem)

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdint>
#include <chrono>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair

int N;
int flag;
vector<int> pos(51),inp(51),_row(51);
//The diagonal and the reverse diagonal marking
vector<int> dia(105);
vector<int>	_dia(105);

//Places the i-th Queen on the board
void solve(int i){
	if(inp[i]){
		if(i==N) flag=1;
		else solve(i+1);
	}
	else{
		for(int row=1;row<=N;row++){
			if(flag)return;
			if(_row[row] || dia[row-i+N] || _dia[row+i])continue;

				_row[row]=1;
				dia[row-i+N]=1;
				_dia[row+i]=1;

				pos[i]=row;
				if(i==N) flag=1;
				else solve(i+1);

				_row[row]=0;
				dia[row-i+N]=0;
				_dia[row+i]=0;
		}
	}
}
int main(int argc, char** argv){
	// if(argc<=1)return 0;
	// std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	// N=atoi(argv[1]);
	while(icin(N)!=EOF){
		flag=0;
		fill(_row.begin(),_row.end(),0);
		fill(dia.begin(),dia.end(),0);
		fill(_dia.begin(),_dia.end(),0);
		for(int i=1;i<=N;i++){
			icin(inp[i]);
			pos[i]=inp[i];
			_row[inp[i]]=1;
		}
		solve(1);
		for(int i=1;i<N;i++){
			printf("%d ",pos[i]);
		}
		printf("%d\n",pos[N]);

	}
	// cout<<(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now()-t1)).count()/1000000000.0;
	return 0;
}