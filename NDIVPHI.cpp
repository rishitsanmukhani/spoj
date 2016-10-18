#include <bits/stdc++.h>

using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
#define pb push_back
#define INF ((int)1e9)
typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;

const int maxn=int(120)+1;
vector<int> primes(1,1);
int p[maxn];
void sieve(){
	fill(p, p+maxn, 1);
	for(int i=2;i<maxn;i++){
		if(p[i]!=1)continue;
		primes.pb(i);
		for(int j=i<<1;j<maxn;j+=i){
			p[j]=0;
		}
	}
	p[1]=p[0]=0;
}


struct bigint{
	char s[50];
	int len;
	bigint(){len=0;}
	void init(int64_t n){
		len=0;
		while(n){
			s[len++]=(n%10)+'0';
			n/=10;
		}
	}
	bigint& operator*=(int32_t d){
		int val=0;
		for(int i=0;i<len;i++){
			val += (s[i] - '0')*d;
			s[i] = (val%10)+'0';
			val /= 10;
		}
		while(val){
			s[len++]=((val%10)+'0');
			val /= 10;
		}
		return *this;
	}
	bool operator<(const bigint& rhs)const{
		if(len==rhs.len){
			for(int i=len-1;i>=0;i--){
				if(s[i]<rhs.s[i])return true;
				else if(s[i]>rhs.s[i])return false;
			}
			return true;
		}
		return len<rhs.len;
	}
	void print(){
		for(int i=len-1;i>=0;i--)
			printf("%c",s[i]);
		printf("\n");
	}
};

vector<bigint> v;
bigint res;
void precompute(){
	sieve();
	v.resize(primes.size());
	res.init(1);
	int len=0;
	for(int i=0;i<primes.size();i++){
		res *= primes[i];
		v[i].len = res.len;
		len += res.len;
		memcpy(v[i].s, res.s, res.len);
	}
}
void solve(){
	int a=0, b=v.size()-1,mid;
	while(a<b){
		mid = (a+b)>>1;
		if(v[mid]<res){
			a=mid+1;
		}
		else{
			b=mid;
		}
	}
	v[a-1].print();
}
int main(){
	precompute();
	int t=20;
	while(t--){
		scanf(" %s ",res.s);
		res.len = strlen(res.s);
		reverse(res.s, res.s+res.len);
		solve();
	}
	return 0;
}