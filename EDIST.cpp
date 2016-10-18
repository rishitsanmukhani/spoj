#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

long long dp[2001][2001];

inline int diff(char a,char b)
{
	if(a==b)
	return 0;
	else
	return 1;
}
inline int minimum(int a,int b,int c)
{
	int m=a;
	if(b<m)
	m=b;
	if(c<m)
	m=c;
	return m;
}

int edit_distance(string a,string b)		//Minimum cost of converting string a to string b
{
	int m,n;
	m=a.size();
	n=b.size();

	//c1 = Cost of insertion
	//c2 = cost of deletion	
	//c3 = cost of replacement
	long long c1,c2,c3;
	c1=c2=c3=1;
	//cin>>c1>>c2>>c3;
	
	for(int i=0;i<=n;i++)
	dp[0][i] = c1*i;						
	
	for(int j=0;j<=m;j++)
	dp[j][0] = c2*j;	
	
	

	for(int i=1;i<=m;++i)
	{
		for(int j=1;j<=n;++j)
		{
			dp[i][j] = minimum(c1 + dp[i][j-1] , c2 + dp[i-1][j] , c3*diff(a[i-1],b[j-1]) + dp[i-1][j-1]);
		}
	}

	return dp[m][n];
}

int main()
{
	int T;
	cin>>T;
	while(T--)
	{
		string a,b;
		cin>>a;
		cin>>b;

		cout<<edit_distance(a,b)<<endl;	
	}
}