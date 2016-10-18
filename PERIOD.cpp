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
			k = v[k-1];
		}
	}
	cout<<endl;

}

int main()
{
	int t,j=1;
	cin >> t;
	while(j<=t)
	{
		int n;
		cin >> n;
		string p;
		cin >> p;
		cout<<"Test case #"<<j<<endl;
		std::vector<int> v;
		
		v = computePrefixFunction(p); 
		for(int i=1;i<n;i++)
		{
			if(v[i]>0 && (v[i]%((i+1) - v[i])==0) )
				cout<<i+1<<" "<<(v[i]/(i+1-v[i])) + 1<<endl;
		}
		j++;
	}
	/*std::vector<int> v;
	v = computePrefixFunction("aabaabaabaab");
	for(int i=0;i<v.size();i++)
		cout<<v[i]<<" ";
	cout<<endl;*/
	/*int n;
	cin >> n;
	while(n--)
	{
		string T,p;
		cin >> p;
		cin >> T;
		
		KMP(T,p);
	}*/
	return 0;
}