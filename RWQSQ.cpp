#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>
using namespace std;

template<typename T>
class sparse_table{
public:
	T** table;
	T* data;
	int X,Y;
	//table[0...N-1][0...logN]; Here table[i][j] represent the index of the minimum value in the segment of data[i...(i+2^j-1)]
	//Index is 0-based
	sparse_table(const int& N,T* input){
		data = input;
		X = N;
		int j=0;
		while(1<<j <= N) j++;
		Y = j;
		table = new T*[X];
		for(int i=0;i<X;i++){
			table[i] = new T[Y];
			table[i][0] = i;
		}
		preProcess();
	}
	//table[i][j] is obtained by comparing the segment data[i...(i+(1<<(j-1))-1)] and data[i+(1<<(j-1))...(i+(1<<j)-1)]
	void preProcess(){
		for(int j=1;j<Y;j++){
			
			for(int i=0;i+(1<<j)-1<X;i++){
				if(data[table[i][j-1]] <= data[table[i+(1<<(j-1))][j-1]])
				table[i][j] = table[i][j-1];
				else
				table[i][j] = table[i+(1<<(j-1))][j-1];
			}	
		}		
	}
	//RMQ = Range minimum query in a...b
	int RMQ(int a,int b){
		int k = log2(b-a+1);
		if(data[table[a][k]] <= data[table[b-(1<<k)+1][k]])
		return table[a][k];
		else
		return table[b-(1<<k)+1][k];
	}
};
int A[100000];

#define icin(x) scanf("%d",&x)

int main()
{
	int N,Q;
	icin(N);
	for(int i=0;i<N;i++){
		icin(A[i]);
	}
	sparse_table<int> T(N,A);
	icin(Q);
	int a,b;
	for(int i=0;i<Q;i++){
		icin(a);icin(b);
		if(b<a)
			swap(a,b);
		cout<<A[T.RMQ(a,b)]<<endl;
	}
	return 0;
}