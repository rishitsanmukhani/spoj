#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

vector<int> computePrefixFunction(const string &p)
{
	//v[i] = length of the longest suffix of p[0...i-1] matched with the prefix of the string p[0....i-1]
	vector<int> v(p.size());
	int n =  p.size(),k = 0;
	v[0] = 0;

	//k = number of the character matched
	for(int i=1;i<n;i++)
	{
		while (k > 0 && p[k] != p[i])
			k = v[k-1];

		if(p[i] == p[k])
			k++;
		v[i] = k;
	}
	return v;
}

void KMP(const string &T,const string &p)
{
	int n = T.size(), m = p.size();
	vector<int> v = computePrefixFunction(p);
	int flag=0;
	//k = number of the character matched
	int k = 0;
	for(int i=0;i<n;i++)
	{
		while(k > 0 && T[i] != p[k])
			k = v[k-1];

		if(p[k] == T[i])
			k++;
		if(k==m)
		{
			//cout<<"Pattern Matched at "<<i-m+1<<endl;
			cout<<i-m+1<<endl;
			flag=1;
			k = v[k-1];
		}
	}if(flag==0)
	cout<<endl;

}

int main()
{
	int n;
	while(cin>>n)
	{
		string T,p;
		cin >> p;
		cin >> T;
		KMP(T,p);
	}
	return 0;
}