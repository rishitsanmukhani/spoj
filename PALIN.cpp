#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)

int main(){
	int t;
	icin(t);
	while(t--){
		string s;
		cin>>s;
		if(s=="9"){
			printf("11\n");
		}
		else{
			bool flag=false;
			int a=0,b=s.size()-1;
			while(a<b){
				if(s[b]>s[a]){
					flag=false;
				}
				if(s[b]<s[a]){
					flag=true;
				}
				a++;b--;
			}
			if(!flag){
				s = "0"+s;
				int idx=(s.size()>>1);
				while(idx>=0){
					if(s[idx]=='9')
						s[idx]='0';
					else{
						s[idx]=s[idx]+1;
						break;
					}
					idx--;
				}
			}
			if(s[0]=='0')s.erase(s.begin());
			a=0,b=s.size()-1;
			while(a<b){
				s[b]=s[a];
				a++,b--;
			}
			printf("%s\n",s.c_str());
		}
	}
}