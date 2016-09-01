#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>
#include <unordered_map>

using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)

typedef long long LL;
unordered_map<LL,LL> _map;

LL solve(LL n){
	if(n<12)return n;
	LL a,b,c;
	auto _a = _map.find(n/2);
	auto _b = _map.find(n/3);
	auto _c = _map.find(n/4);
	if(_a==_map.end()){
		a= solve(n/2);
		_map.insert(pair<LL,LL>(n/2,a));
	}else a = _a->second;
	if(_b==_map.end()){
		b= solve(n/3);
		_map.insert(pair<LL,LL>(n/3,b));
	}else b =_b->second;
	if(_c==_map.end()){
		c= solve(n/4);
		_map.insert(pair<LL,LL>(n/4,c));
	}else c = _c->second;
		
	return a+b+c;
}

int main(){
	long long N;
	while(cin>>N){
		printf("%lld\n",solve(N));
	}
	return 0;
}