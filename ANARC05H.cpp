#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>

using namespace std;

string s;

int solve(int index,int max_sum){
	if(index==-1)return 1;
	int ans=0,tmp_sum=0;
	for(int i=index;i>=0;i--){
		tmp_sum += s[i]-'0';
		if(tmp_sum>max_sum)
			break;
		ans += solve(i-1,tmp_sum);
	}
	return ans;
}


int main(){
	int len;
	int T=0;
	while(1){
		T++;
		cin>>s;
		len=s.size();
		if(s=="bye")break;
		vector<int> v(len);
		v[0] = s[0]-'0';
		for(int i=1;i<len;i++){
			v[i] = v[i-1] + s[i]-'0';
		}
		int ans=solve(len-1,v[len-1]);
		printf("%d. %d\n",T,ans);
	}
	return 0;
}