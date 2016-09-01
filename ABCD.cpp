#include <bits/stdc++.h>

using namespace std;
#define icin(x) scanf("%d",&x)
#define pb push_back
typedef vector<int> vi;
typedef long long LL;

int main(){
  int n;
  icin(n);
  string s,ans;
  cin>>s;
  ans.resize(n<<1,'A');
  for(int i=0;i<2*n;i+=2){
    int A[4]={0};
    A[s[i]-'A']=1;
    A[s[i+1]-'A']=1;
    int idx=i;
    for(int j=0;j<4;j++){
      if(A[j]==0)ans[idx++]=j+'A';
    }
    if(idx>=2 && ans[idx-2]==ans[idx-3])
      swap(ans[idx-2],ans[idx-1]);
  }
  cout<<ans<<endl;
  return 0;
}