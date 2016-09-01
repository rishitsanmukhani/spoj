#include <bits/stdc++.h>
using namespace std;
#define icin(x) scanf("%d",&x)

const int MAX_N = int(1e9);
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

const int DIFF=int(1e4);
vector<int> segment(DIFF+1);
vector<int> value(DIFF+1);
void segmented_sieve(int& m,int& n){
  for(int i=m;i<=n;i++){
    segment[i-m]=1;
    value[i-m]=i;
  }
  int a,b,p,num,cnt;
  for(int i=0;i<primes.size();i++){
    p=primes[i]; 
    if(p*p>n)break;
    if(m%p) a=(m/p)+1;
    else a=m/p;
    b=(n/p);
    a=max(a,2);
    for(int j=a;j<=b;j++){
      num=value[j*p-m];
      cnt=1;
      while(num%p==0){
        cnt++;
        num/=p;
      }
      segment[j*p-m]*=cnt;
      value[j*p-m]=num;
    }
  }
  for(int i=m;i<=n;i++){
    if(value[i-m]!=1)segment[i-m]<<=1;
  }
}
int main(){
  sieve();
  int m,n,k;
  icin(m);icin(n);icin(k);
  if(k==1){
    if(m==1)printf("1\n");
    else printf("0\n");
  }
  else{
    m=max(m,2);
    if(n>=m){
      int ans=0;
      segmented_sieve(m,n);    
      for(int i=m;i<=n;i++){
        if(segment[i-m]==k)ans++;
      }
      cout<<ans<<endl;
    }
    else{
      printf("0\n");
    }
  }
  return 0;
}