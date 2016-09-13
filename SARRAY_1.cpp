#include <bits/stdc++.h>
using namespace std;

const int maxn=int(1e5)+10;

class SuffixArray{
public:
	int n;
	char S[maxn];
	int RA[maxn], tempRA[maxn];		// rank array
	int SA[maxn], tempSA[maxn];		// suffix array
	int c[maxn];									// counting sort

	void init(){
		n = (int)strlen(S);
		S[n++] = '$';

		for(int i=0;i<n;i++) RA[i] = S[i];
		for(int i=0;i<n;i++) SA[i] = i;
		for(int k=1;k<n;k<<=1){
			countingSort(k);
			countingSort(0);
			int r;
			tempRA[SA[0]] = r = 0;
			for(int i=1;i<n;i++)
				tempRA[SA[i]] = ((RA[SA[i]] == RA[SA[i-1]]) && (RA[SA[i]+k] == RA[SA[i-1]+k])) ? r : ++r;
			for(int i=0;i<n;i++)
				RA[i] = tempRA[i];
			if(RA[SA[n-1]] == n-1)
				break;
		}
	}
	void countingSort(int k){
		int maxi = max(256, n);
		fill(c, c + maxi, 0);
		for(int i=0;i<n;i++)
			c[i+k<n ? RA[i+k] : 0]++;
		for(int i=0, sum=0;i<maxi;i++){
			int t = c[i];
			c[i] = sum;
			sum += t;
		}
		for(int i=0;i<n;i++)
			tempSA[c[SA[i]+k<n ? RA[SA[i]+k] : 0]++] = SA[i];
		for(int i=0;i<n;i++)
			SA[i] = tempSA[i];
	}
};

int main(){
	SuffixArray sa;
	scanf("%s", sa.S);
	sa.init();
	for(int i=1;i<sa.n;i++){
		printf("%d\n", sa.SA[i]);
	}
	return 0;
}