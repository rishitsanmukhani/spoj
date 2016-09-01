#include <iostream>
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
		int j=1;
		while(1<<j <= N) j++;
		Y = j;
		table = new T*[X];
		for(int i=0;i<X;i++){
			table[i] = new T[Y];
			table[i][0] = i;
		}
		preProcess();
	}
	~sparse_table(){
		data=NULL;
		for(int i=0;i<X;i++)
			delete table[i];
		delete table;
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
		int k=0;
		while((1<<k) <= (b-a+1)) k++;
		k--;
		if(data[table[a][k]] <= data[table[b-(1<<k)+1][k]])
		return table[a][k];
		else
		return table[b-(1<<k)+1][k];
	}
};
int A[1000000];

#define icin(x) scanf("%d",&x)

int main()
{
	int t;
	icin(t);
	for(int z=1;z<=t;z++)
	{
		int N,Q;
		icin(N);icin(Q);
		for(int i=0;i<N;i++)
		icin(A[i]);

		sparse_table<int> T(N,A);
		int a,b;
		printf("Scenario #%d:\n\n",z);
		for(int i=0;i<Q;i++)
		{
			icin(a);icin(b);
			if(b<a)
				swap(a,b);
			printf("%d\n",A[T.RMQ(a-1,b-1)]);
		}
	}
	return 0;
}