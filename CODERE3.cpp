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

vector<pair<int,int> > LIS(vector<int>& v){
	//ans[i].first = last element of the LIS of v[0...i]
	//ans[i].second = size of LIS
	vector<pair<int,int> > ans(v.size());
	
	vector<int> parent(v.size(),-1);
	vector<int> lis;
	vector<int> lis_index;
	for(int i=0;i<v.size();i++){
		auto it = lower_bound(lis.begin(),lis.end(),v[i]);
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
		ans[i].first = lis.back();
		ans[i].second = lis.size();
	}
	return ans;
}

int main(){
	int T;
	icin(T);
	while(T--){
		int n;icin(n);
		vector<int> v(n);
		for(int i=0;i<n;i++)icin(v[i]);

		vector<pair<int,int> > dp1 = LIS(v);
		reverse(v.begin(),v.end());
		vector<pair<int,int> > dp2 = LIS(v);
		int ans=0,last = dp1.size()-1;
		for(int i=0;i<=last-1;i++){
			int len=0;
			if(dp1[i].first==dp2[last-i-1].first)len = dp1[i].second + dp2[last-1-i].second-1;
			else len = dp1[i].second + dp2[last-i-1].second;
			ans = max(len,ans);
		}
		ans = max(ans,dp1[last].second);
		ans = max(ans,dp2[last].second);
		printf("%d\n",ans);
	}
	return 0;
}