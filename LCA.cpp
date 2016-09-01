#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
 
using namespace std;
 
#define icin(x) scanf("%d",&x)
 
const int maxNodes=1<<12, logMaxNodes=12;
int numNodes, logNumNodes, root;
 
vector<int> children[maxNodes];		// children[i] contains the children of node i
int A[maxNodes][logMaxNodes+1];		// A[i][j] is the 2^j-th ancestor of node i, or -1 if that ancestor does not exist
int L[maxNodes];					// L[i] is the level of node i
 
//To calculate the binary logarithm
//Range of n is 0...2^32-1
int logBinary(unsigned int n){
	if(n==0)
	return -1;
	int p = 0;
	if (n >= 1<<16) { n >>= 16; p += 16; }
	if (n >= 1<< 8) { n >>=  8; p +=  8; }
	if (n >= 1<< 4) { n >>=  4; p +=  4; }
	if (n >= 1<< 2) { n >>=  2; p +=  2; }
	if (n >= 1<< 1) {           p +=  1; }
	return p;
}
 
//DFS to assign the level to the nodes
void DFS(int i, int level){
	L[i] = level;
	for(int j = 0; j < children[i].size(); j++)
	DFS(children[i][j], level+1);
}
 
int LCA(int p, int q)
{
	//ensure node p is at least as deep as node q
	if(L[p] < L[q])
	swap(p, q);
 
	//"binary search" for the ancestor of node p situated on the same level as q
	for(int i = logNumNodes; i >= 0; i--)
	if(L[p] - (1<<i) >= L[q]) p = A[p][i];
	
	if(p == q)
	return p;
 
	//"binary search" for the LCA
	for(int i = logNumNodes; i >= 0; i--){
		if(A[p][i] != -1 && A[p][i] != A[q][i]){
			p = A[p][i];
			q = A[q][i];
		}
	}
	return A[p][0];
}
 
int main()
{
	int T;
	icin(T);
	for(int z=1;z<=T;z++){
 
		icin(numNodes);
		logNumNodes=logBinary(numNodes);
		
		int M,tmp;
		
		//A[tmp][0] denotes the parent of the tmp which is i
		for(int i=1;i<=numNodes;i++){
			children[i].clear();
			icin(M);
			for(int j=0;j<M;j++){
				icin(tmp);
				A[tmp][0]=i;
				children[i].push_back(tmp);
			}
		}
		root = 1;
		//precompute A using dynamic programming
		for(int j = 1; j <= logNumNodes; j++){
			for(int i = 1; i <=numNodes; i++){
				if(A[i][j-1] != -1)
					A[i][j] = A[A[i][j-1]][j-1];
				else
					A[i][j] = -1;
			}
		}
		DFS(root,0);
 
		int Q,a,b;
		icin(Q);
		printf("Case %d:\n",z);
		for(int i=0;i<Q;i++){
			icin(a);
			icin(b);
			printf("%d\n",LCA(a,b));
		}
	}
	return 0;
}
 