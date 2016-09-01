#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

//For each possible position, there can be covering of row, column and two cross diagonal. So max number of nodes are N*N*4
const int maxnode = 55 * 55 * 4;	//N*N*4
//Number of rows -> number of possible position of queen
const int maxr = 55 * 55;					//N*N
//row-N,column-N, two diagonals-2*(2*N-1)
const int maxc = 55 * 6;					//6*N-2
int N;

//L,R,U,D - Directional pointers
//COL[i] - column of node i
//ROW[i] - row of node i
int U[maxnode],D[maxnode],L[maxnode],R[maxnode],COL[maxnode],ROW[maxnode];
//S[i] - number of nodes in each column(equals number of ones)
//H[i] - start point(header) of each row
int H[maxr],S[maxc];
//sz+1 - total number of nodes
int sz;

void init(int r,int c){
	for(int i=0; i<=c; ++i){
		S[i]=0;
		U[i]=D[i]=i;
		L[i+1]=i;
		R[i]=i+1;
	}
	L[0]=c;
	R[c]=0;
	sz=c;
	while(r)H[r--]=-1;
}
void remove(int c){
	L[R[c]]=L[c],R[L[c]]=R[c];
	for(int i=D[c]; i!=c; i=D[i])
		for(int j=R[i]; j!=i; j=R[j])
			U[D[j]]=U[j],D[U[j]]=D[j],--S[COL[j]];
}
void resume(int c){
	for(int i=U[c]; i!=c; i=U[i])
		for(int j=L[i]; j!=i; j=L[j])
			++S[COL[U[D[j]]=D[U[j]]=j]];
	L[R[c]]=R[L[c]]=c;
}

//Count of the number of column covered
int _count=0;
vector<int> ans;
bool Dance(int d){
	if(_count==N)return 1;
	
	if(!R[0])return 0;
	int c,tmp=maxnode;

	//Choosing the column with least number of the nodes
	for(int i=R[0]; i!=0; i=R[i]){
			if(i<=N){
				if(S[i]<tmp)tmp=S[c=i];
			}		
	}
	remove(c);

	for(int i=D[c]; i!=c; i=D[i]){
		//Trying ROW[i]
		ans.push_back(ROW[i]);
		_count++;
		//Covering all the column corresponding to nodes in this row
		for(int j=R[i]; j!=i; j=R[j]){
			if(j<=N)_count++;
			remove(COL[j]);
		}
		
		//If the answer is found the return
		if(Dance(d+1))return 1;
		//Else try next row removing current row
		else ans.erase(ans.end()-1);
		
		//Uncover all the column corresponding to nodes in current row
		for(int j=L[i]; j!=i; j=L[j]){
			if(j<=N)_count--;
			resume(COL[j]);
		}
		_count--;
	}
	resume(c);
	

	return 0;
}
//If A[r][c] =1 -> create a node
void createNode(int r,int c){
	//Assign row and column to node
	++S[COL[++sz]=c];
	ROW[sz]=r;
	//Up and down pointers
	U[sz]=U[c];
	D[U[c]]=sz;
	D[sz]=c;
	U[c]=sz;
	//If first node in row, initialize the header of row
	if(H[r]<0)H[r]=L[sz]=R[sz]=sz;
	//Else left and right pointers
	else{
		L[sz]=L[H[r]];
		R[L[H[r]]]=sz;
		R[sz]=H[r];
		L[H[r]]=sz;
	}
}
bool p[maxc];
//p1-column, p2-row, p3-main diag, p4-secondary diag
void place(int &p1,int &p2,int &p3,int &p4,int i,int j){
	p1=j,p2=N+i,p3=N+N+i-j+N,p4=N+N+2*N-1+i+j-1;
}
int main(int argc, char** argv){
	int p1,p2,p3,p4;
	while(scanf("%d",&N)!=EOF){
		for(int i=1;i<=6*N-2;i++)p[i]=0;
		init(N*N,6*N-2);
		for(int i=1;i<=N;i++){
			int j;
			scanf("%d",&j);
			if(j){
				place(p1,p2,p3,p4,i,j);
				p[p1]=p[p2]=p[p3]=p[p4]=1;
				createNode((i-1)*N+j,p1),createNode((i-1)*N+j,p2),createNode((i-1)*N+j,p3),createNode((i-1)*N+j,p4);
			}
		}
		for(int i=1;i<=N;i++){
			for(int j=1;j<=N;j++){
				place(p1,p2,p3,p4,i,j);
				if(p[p1] || p[p2] || p[p3] || p[p4])continue;
				createNode((i-1)*N+j,p1),createNode((i-1)*N+j,p2),createNode((i-1)*N+j,p3),createNode((i-1)*N+j,p4);	
			}
		}
		ans.clear();
		_count=0;
		Dance(1);
		int A[N+1];
		for(int i=0;i<N;i++){
			int r=(ans[i]-1)/N;
			A[r+1] = ans[i]-N*r;
		}
		for(int i=1;i<=N;i++)printf("%d ",A[i]);
		printf("\n");
	}
	return 0;
}