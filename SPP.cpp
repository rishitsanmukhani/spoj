#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;

// #define MOD (int(1e9))
LL MOD = (LL(1e9));
void norm(LL& x){
	if(x>=MOD){
		x %= MOD;
	}
	else if(x<0){
		x %= MOD;
		x += MOD;
	}
}
class Matrix{
public:
	vector<vector<LL> > v;
	int m,n;
	Matrix(int _m, int _n, int val=0):m(_m), n(_n){
		v.assign(_m, vector<LL>(n, val));
	}
	Matrix& operator+=(const Matrix& rhs){
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				v[i][j] += rhs.v[i][j];
		return *this;
	}
	Matrix& operator-=(const Matrix& rhs){
		for(int i=0;i<m;i++)
			for(int j=0;j<n;j++)
				v[i][j] -= rhs.v[i][j];
		return *this;
	}
	void print(){
		for(int i=0;i<m;i++){
			for(int j=0;j<n;j++){
				cout<<v[i][j]<<" ";
			}
			cout<<endl;
		}
	}
};
inline Matrix operator+(Matrix lhs, const Matrix& rhs){
	lhs += rhs;
	return lhs;
}
inline Matrix operator-(Matrix lhs, const Matrix& rhs){
	lhs -= rhs;
	return lhs;
}
inline Matrix operator*(const Matrix& lhs, const Matrix& rhs){
	assert(lhs.n == rhs.m);
	Matrix res(lhs.m, rhs.n, 0);
	for(int i=0;i<lhs.m;i++){
		for(int j=0;j<rhs.n;j++){
			for(int k=0;k<lhs.n;k++){
				res.v[i][j] += lhs.v[i][k]*rhs.v[k][j];
				norm(res.v[i][j]);
			}
		}
	}
	return res;
}
Matrix identity(const int& m){
	Matrix res(m, m, 0);
	for(int i=0;i<m;i++)
		res.v[i][i]=1;
	return res;
}
Matrix power(Matrix m, LL p){
	assert(m.n == m.n);
	Matrix res(identity(m.m));
	while(p){
	  if(p&1LL)res = (res * m);
	  p >>= 1LL;
	  m = (m * m);
	}
	return res;		
}

int main(){
	int t;
	icin(t);
	while(t--){
		int k;
		icin(k);
		Matrix F(k+1, 1, 0), T(k+1, k+1, 0);
		F.v[0][0]=0;	//S[0] = 0
		for(int i=1;i<=k;i++){
			lcin(F.v[i][0]);
		}
		T.v[0][0] = 1, T.v[0][1] = 1; //S[i] = S[i-1] + A[i]
		for(int i=1;i<k;i++){
			T.v[i][i+1]=1;
		}
		for(int i=1;i<=k;i++){
			lcin(T.v[k][k+1-i]);
		}
		LL n,m;
		lcin(m);lcin(n);lcin(MOD);
		Matrix Fm(power(T, m-1) * F), Fn(power(T, n) * F);
		printf("%lld\n",(Fn.v[0][0] - Fm.v[0][0] + MOD)%MOD);
	}
	return 0;
}