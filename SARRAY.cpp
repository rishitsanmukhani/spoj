#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>
#include <cstdio>
#include <vector>
using namespace std;

class suffixArray{
public:
	const int N;
	string s;
	//P[i][j] = sort index of the substring of length 2^i starting from j
	//i = 0...log(N) and j = 0...N-1
	vector< vector<int> > P;
	vector< pair<pair<int,int>,int> > L;
	//array[i] = index of the suffix which comes in the ith position lexicographically
	vector<int> array;
	suffixArray(const string& s): N(s.size()), s(s), P(1,vector<int>(N)), L(N),array(N){
		//sort index is the ascii character itself
		for(int i=0;i<N;i++) P[0][i] = int(s[i]);
		//count = length of the prefix according to which the sorting is done
		for(int count=1,step = 1;count <= N;count <<= 1,++step){
			
			P.push_back(vector<int>(N));
			
			for(int i=0;i<N;i++){
				L[i].first.first = P[step-1][i];
				L[i].first.second = (i+count<N) ? P[step-1][i+count] : -1;
				L[i].second = i;
			}
			
			sort(L.begin(),L.end());
			
			P[step][L[0].second] = 0; 
			for(int i=1;i<N;i++){
				P[step][L[i].second] = (L[i].first == L[i-1].first) ? P[step][L[i-1].second] : i;
			}
		}
		for(int i=0;i<N;i++)
		array[i] = L[i].second;
	}

	vector<int> getSuffixArray(){
		return array;
	}

	int longestCommonPrefix(int i, int j){
		int ans=0;
		if (i==j)
			return N-i;

		for (int k = P.size()-1;k >= 0 && i<N && j<N;k--){
			if (P[k][i] == P[k][j]){
				i += 1<<k;
				j += 1<<k;
				ans += 1<<k;
			}
		}
		return ans;
	}
};

int main(){
	string s;
	cin>>s;
	suffixArray suffix(s);
	vector<int> v = suffix.getSuffixArray();
	for(int i=0; i<v.size(); i++)
	printf("%d\n",v[i]);
	
	return 0;
}