#include <bits/stdc++.h>

using namespace std;

#define GC getchar_unlocked
int read(){
	register char c=0;
	while(c<33)c=GC();
	int a=0;
	while(c>33){
		a=(a<<3)+(a<<1)+c-48;
		c=GC();
	}
	return a;
}
#define icin(x) (x=read())
#define pb push_back
#define mp make_pair

typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef pair<int,int> pii;

int main(){
	int n, k, a, b;
	icin(n);icin(k);
	vector<bitset<1001> > v(n+1), v_in(n+1);
	for(int i=1;i<=k;++i){
		icin(a);icin(b);
		if(a==b || v[b][a]){
			printf("%d %d\n", a, b);
		}
		else if(v[a][b]){
			continue;
		}
		else{
			v[a][b] = 1;
			v[a] |= v[b];
			v_in[b][a] = 1;
			v_in[b] |= v_in[a];
			for(int j=1;j<=n;j++){
				if(v_in[a][j]) v[j] |= v[a];
				if(v[b][j]) v_in[j] |= v_in[b];
			}
		}
	}
	printf("0 0\n");
	return 0;
}