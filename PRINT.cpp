#include <bits/stdc++.h>
using namespace std;
#define icin(x) scanf("%d",&x)

const int MAX_N = int(2147483647);
const int N = sqrt(MAX_N)+1;
vector<int> is_prime(N+1);
vector<int> primes;
void sieve(){
  primes.clear();
  fill(is_prime.begin(),is_prime.end(),1);
  for(int j=2,k=2;j<=N;j++){
    if(is_prime[j]==0)continue;
    primes.push_back(j);
    k=2;
    while(j*k<=N){
      is_prime[j*k]=0;k++;
    }
  }
  is_prime[0]=is_prime[1]=0;
}

const int DIFF=int(1e6);
vector<int> segment(DIFF+1);
void segmented_sieve(int& m,int& n){
  fill(segment.begin(),segment.end(),1);
  int a,b,p;
  for(int i=0;i<primes.size();i++){
    p=primes[i]; 
    if(p*p>n)break;
    if(m%p) a=(m/p)+1;
    else a=m/p;
    b=(n/p);
    a=max(a,2);
    for(int j=a;j<=b;j++){
      segment[j*p-m]=0;
    }
  }
}
int main(){
  sieve();
  int t;
  icin(t);
  while(t--){
    int m,n;
    icin(m);
    icin(n);
    m=max(m,2);
    if(n>=m){
      segmented_sieve(m,n);    
      for(int i=m;i<=n;i++){
        if(segment[i-m])printf("%d\n",i);
      }
    }
  }
  return 0;
}