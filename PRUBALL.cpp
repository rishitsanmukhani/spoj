#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int dp[51][1001];	
//n = Number of the eggs
//k = number of the floors
//dp[n][k] = minimum numbers of the trials to determine the critical floor
int critical_floor(int n,int k)
{
	memset(dp,0,sizeof dp);

	//We have to drop and check at each floor
	for(int j=1;j<=k;j++)
		dp[1][j] = j;
	
	for(int i=1;i<=n;i++)
		dp[i][0] = 0;
	
	for(int i=2;i<=n;i++)
	{
		for(int j=1;j<=k;j++)
		{
			int tmp = max(dp[i][j-1],dp[i-1][0]);
			for(int z=2;z<=j;z++)
			{
				if( max(dp[i][j-z] , dp[i-1][z-1]) < tmp )
					tmp = max(dp[i][j-z] , dp[i-1][z-1]);
			}
			dp[i][j] = 1 + tmp;
		}
	}
	return dp[n][k];
}

int main()
{
	critical_floor(50,1000);
	int t;
	cin >> t;
	for(int i=1;i<=t;i++)
	{
		int index,n,k;
		cin >> index>>n>>k;
		cout<<index << " "<<dp[n][k]<<endl;
	}
}