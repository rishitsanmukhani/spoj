#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 100;

typedef long long LL;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x);

LL A[100001];

struct node
{
	int l,r;
	LL sum;
	LL lazy; 
};
node tree[4*100001];

node make_node(LL value,int l,int r)
{
	node temp;
	temp.l=l;
	temp.r=r;
	temp.sum = value;
	temp.lazy=0;

	return temp;
}

node merge(node& left,node& right)
{
	node temp;
	temp.l=left.l;
	temp.r = right.r;
	temp.sum = left.sum + right.sum;
	temp.lazy = 0;
	return temp;
}

node build(int from,int to,int index)
{
	if(from==to)
	{
		tree[index] = make_node(A[from],from,to);
		return tree[index];
	}

	int mid = (from+to)/2;
	node l = build( from,mid,index<<1 );
	node r = build( mid+1,to,(index<<1) + 1);
	
	tree[index] = merge(l,r);
	return tree[index];
}

LL query(int from,int to,int index,int a,int b,LL value)
{
	LL ans = 0;
	if(from==a && to==b){
		return tree[index].sum + value*(b-a+1);
	}

	int mid = (from+to)/2;
	if(a > mid)
	{
		ans+=query(mid+1,to,(index<<1)+1,a,b,value+tree[index].lazy);
	}
	else if(b <= mid){
		ans+=query(from,mid,index<<1,a,b,value+tree[index].lazy);
	}
	else{
		ans += query(from,mid,index<<1,a,mid,value+tree[index].lazy);
		ans += query(mid+1,to,(index<<1)+1,mid+1,b,value+tree[index].lazy);
	
	}
	return ans;
}

void update(int from,int to,int index,int a,int b,LL value)
{
	tree[index].sum += value*(b-a+1);
	
	if(from==to)
		return;
	if(from==a && to==b)
	{
		tree[index].lazy += value;
		return;
	}

	int mid = (from+to)/2;
	if(a>mid)
		update(mid+1,to,(index<<1) +1,a,b,value);
	else if(b<=mid)
		update(from,mid,index<<1,a,b,value);
	else
	{
		update(from,mid,index<<1,a,mid,value);
		update(mid+1,to,(index<<1)+1,mid+1,b,value);
	}
}


int main()
{
	LL T;
	lcin(T);
	int N,C;
	while(T--)
	{
		icin(N);
		icin(C);
		memset(A,0,sizeof(A));

		build(1,N,1);

		int a,p,q;
		LL v;
		for(int i=0;i<C;i++)
		{
			icin(a);
			icin(p);
			icin(q);
			if(a==0)
			{
				lcin(v);
				update(1,N,1,p,q,v);
			}
			else
			{
				printf("%lld\n",query(1,N,1,p,q,0));
			}
		}
	}
	return 0;
}