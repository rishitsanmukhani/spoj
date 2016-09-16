#include <bits/stdc++.h>
using namespace std;

#define MOD (int(1e9))
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;

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
Matrix power(Matrix m, int p){
	assert(m.n == m.n);
	Matrix res(identity(m.m));
	while(p){
	  if(p&1)res = (res * m);
	  p >>= 1;
	  m = (m * m);
	}
	return res;		
}

int main(){
	int t;
	icin(t);
	while(t--){
		int k,n;
		icin(k);
		Matrix F(k, 1, 0), T(k, k, 0);
		for(int i=0;i<k-1;i++){
			T.v[i][i+1]=1;
		}
		for(int i=0;i<k;i++){
			lcin(F.v[i][0]);
		}
		for(int i=0;i<k;i++){
			lcin(T.v[k-1][k-1-i]);
		}
		icin(n);
		F = power(T, n-1) * F;
		printf("%lld\n",F.v[0][0]);
	}
	return 0;
}