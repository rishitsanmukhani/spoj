#include <bits/stdc++.h>

using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define mp make_pair

typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int,int> pii;

vi v1, v2, vis;
int p[1000];
int n;
int solve(){
	vis.assign(n, 0);
	
	int min_global = v2[0], ans=0;
	vi v;
	for(int i=0;i<n;i++){
		if(vis[i])continue;
		vis[i]=1;

		int min_local = v1[i], sum=v1[i], pos;
		v.pb(v1[i]);
		pos = p[v1[i]];
		while(pos!=i){
			vis[pos] = 1;
			v.pb(v1[pos]);
			sum += v1[pos];
			min_local = min(min_local, v1[pos]);
			pos = p[v1[pos]];

		}

		sum -= min_local;
		int k = v.size();	
		ans += min(sum + (k-1)*min_local, sum + (k-1)*min_global + 2*(min_local+min_global)); 
		v.clear();
	}
	return ans;
}
int main(){
	int t=0;
	while(1){
		t++;
		icin(n);
		if(n==0)
			break;
		v1.resize(n);
		v2.resize(n);
		for(int i=0;i<n;i++){
			icin(v1[i]);
			v2[i]=v1[i];
		}
		sort(v2.begin(), v2.end());
		for(int i=0;i<n;i++){
			p[v2[i]]=i;
		}
		printf("Case %d: %d\n\n", t, solve());
	}

	return 0;
}