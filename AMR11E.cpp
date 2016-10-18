#include <bits/stdc++.h>

using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%d",&x)

const int N = 100000;
vector<int> is_prime(N+1);
void sieve(){
  fill(is_prime.begin(),is_prime.end(),0);
  for(int j=2,k=2;j<=N;j++){
    if(is_prime[j])continue;
    k=2;
    is_prime[j]=1;
    while(j*k<=N){
      is_prime[j*k]++,k++;
    }
  }
  is_prime[0]=is_prime[1]=0;
}
vector<int> lucky;
int main(){
  sieve();
  for(int i=2;i<=N;i++){
    if(is_prime[i]>2)lucky.push_back(i);
  }
  int t;
  icin(t);
  while(t--){
    int n;
    icin(n);
    printf("%d\n",lucky[n-1]);
  }
}