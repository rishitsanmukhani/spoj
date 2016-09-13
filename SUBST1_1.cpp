//Rishit Sanmukhani
//Suffix array made in nlogn time using counting sort.
//Also LCP array is made in nlogn (where logn is for each pair) time.


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
	vector< pair<pair<int,int>,int> > L,tmp;
	//array[i] = index of the suffix which comes in the ith position lexicographically
	vector<int> array;
	suffixArray(const string& s): N(s.size()), s(s), P(1,vector<int>(N)), L(N),array(N),tmp(N){
		//sort index is the ascii character itself
		for(int i=0;i<N;i++) P[0][i] = int(s[i]);
		//count = length of the prefix according to which the sorting is done
		int count=1,step = 1;

		P.push_back(vector<int>(N));
		
		for(int i=0;i<N;i++){
			L[i].first.first = P[step-1][i];
			L[i].first.second = (i+count<N) ? P[step-1][i+count] : -1;
			L[i].second = i;
		}
		
		sort(L.begin(),L.end());
		
		P[step][L[0].second] = 0; 
		for(int i=1;i<N;i++)
			P[step][L[i].second] = (L[i].first == L[i-1].first) ? P[step][L[i-1].second] : i;
	
		count <<= 1;
		++step;
		for(;count <= N;count <<= 1,++step){
			
			P.push_back(vector<int>(N));
			
			for(int i=0;i<N;i++){
				L[i].first.first = P[step-1][i];
				L[i].first.second = (i+count<N) ? P[step-1][i+count] : -1;
				L[i].second = i;
			}
			
			countingSort();

			P[step][L[0].second] = 0; 
			for(int i=1;i<N;i++){
				P[step][L[i].second] = (L[i].first == L[i-1].first) ? P[step][L[i-1].second] : i;
			}
		}
		for(int i=0;i<N;i++)
		array[i] = L[i].second;
	}
	//Linear time - Stable sort
	void countingSort(){
		
		int cnt[N+1];
		//first round of counting sort on second argument
		memset(cnt,0,sizeof cnt);

		for(int i=0;i<N;i++)
			cnt[L[i].first.second + 1]++;
		int total=0,old;
		for(int i=0;i<=N;i++){
			old = cnt[i];
			cnt[i] = total;
			total += old;
		}
		for(int i=0;i<N;i++){
			tmp[cnt[L[i].first.second + 1]] = L[i];
			cnt[L[i].first.second + 1]++;
		}
		
		//second round of counting sort on first argument
		memset(cnt,0,sizeof cnt);
		
		for(int i=0;i<N;i++)
		cnt[tmp[i].first.first + 1]++;
		
		total=0;
		for(int i=0;i<=N;i++){
			old = cnt[i];
			cnt[i] = total;
			total += old;
		}
		for(int i=0;i<N;i++){
			L[cnt[tmp[i].first.first + 1]] = tmp[i];
			cnt[tmp[i].first.first + 1]++;
		}
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
	int t;
	scanf("%d",&t);
	while(t--){
		string s;
		cin>>s;
		suffixArray suffix(s);
		vector<int> v = suffix.getSuffixArray();
		int ans = (s.size()-v[0]),len_v=v.size(),len_s=s.size();
		for(int i=1;i<len_v;i++)
			ans += (len_s-suffix.longestCommonPrefix(v[i], v[i-1])-v[i]);
		cout <<ans<< endl;
	}	
	return 0;
}