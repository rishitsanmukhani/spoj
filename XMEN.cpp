#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cstring>
#include <string>

using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)

typedef long long LL;

vector<int> A;
vector<pair<int,int> > B;

vector<int> v(int(1e5)+1);
#define STRICTLY_INCREASING
vector<int> LIS(vector<int>& v){
	vector<int> parent(v.size(),-1);
	vector<int> lis;
	vector<int> lis_index;
	for(int i=0;i<v.size();i++){
		#ifdef STRICTLY_INCREASING
			auto it = lower_bound(lis.begin(),lis.end(),v[i]);
		#else
			auto it = upper_bound(lis.begin(),lis.end(),v[i]);
		#endif
		if(it == lis.end()){
			if(lis.size()!=0){
				parent[i] = lis_index.back();
			}
			lis.push_back(v[i]);
			lis_index.push_back(i);
		}
		else{
			int index = it - lis.begin();
			*it = v[i];
			parent[i] =parent[lis_index[index]];
			lis_index[index] =i;
		}
	}
	vector<int> ret;
	for (int i=lis_index.back() ;i>=0; i=parent[i])ret.push_back(v[i]);
	reverse(ret.begin(), ret.end());
	return ret;
}

int main(){
	int T;
	icin(T);
	while(T--){
		int N;
		icin(N);
		A.resize(N+1);
		B.resize(N+1);
		for(int i=1;i<=N;i++)icin(A[i]);
		for(int i=1;i<=N;i++){
			icin(B[i].first);
			B[i].second = i;
		}
		sort(B.begin(),B.end());
		for(int i=0;i<N;i++){
			v[i] = B[A[i+1]].second;
		}
		printf("%d\n",LIS(v).size());
	}
	return 0;
}