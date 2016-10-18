#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define bitcount(x) __builtin_popcount(x)
#define pb push_back
#define MOD (int(1e9)+7)
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

const int maxn = int(2e4);
vi A(maxn),B(maxn);
vi v1, v2;
LL solve(){
	LL ans=0;
	for(int i=0;i<v1.size();i++){
		ans += max(v1[i],v2[i]);
	}
	return ans;
}
int main(){
	while(1){
		int n1,n2;
		icin(n1);
		if(!n1)break;
		for(int i=0;i<n1;i++)
			icin(A[i]);
		icin(n2);
		for(int i=0;i<n2;i++)
			icin(B[i]);
		v1.clear();
		v2.clear();
		int a=0,b=0;
		int i,j;
		LL ans=0;
		for(i=0,j=0;i<n1 && j<n2;){
			if(A[i]<B[j])a+=A[i],i++;
			else if(A[i]>B[j])b+=B[j],j++;
			else ans += A[i], v1.pb(a),a=0,v2.pb(b),b=0,i++,j++;
		}
		while(i<n1)a+=A[i],i++;
		while(j<n2)b+=B[j],j++;
		if(a!=0 || b!=0)v1.pb(a), v2.pb(b);
		printf("%lld\n",ans+solve());
	}
	return 0;
}