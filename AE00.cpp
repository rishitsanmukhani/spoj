#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)

int main(){
	int n;
	icin(n);
	int c=0;
	for(int i=1;i*i<=n;i++){
		c += n/i-(i-1);
	}
	printf("%d\n",c);
}