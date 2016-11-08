#include <bits/stdc++.h>
using namespace std;
#define icin(x) (scanf("%d",&x))
typedef long long LL;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;

string s;
bool is_double(int a, int b){
	int cnt=0;
	while(a<b){
		if(s[a]!=s[b])cnt++;
		a++, b--;
	}
	if(cnt>1)return false;
	if(cnt==0 && a!=b)return false;
	return true;
}
bool solve(){
	int n = s.size();
	for(int i=0;i<n-1;i++){
		if(is_double(0, i) && is_double(i+1, n-1)){
			return true;
		}
	}
	return false;
}
int main(){
	while(1){
		cin>>s;
		if(s=="*END*")break;
		if(solve()){
			printf("%s is a double near palindrome.\n", s.c_str());
		}
		else{
			printf("%s is not a double near palindrome.\n", s.c_str());
		}
	}
	return 0;
}