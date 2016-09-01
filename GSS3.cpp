//Rishit Sanmukhani
//http://www.spoj.com/problems/GSS3/


#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef long long LL;


int getSegmentTreeSize(int N)
{
	int size = 1;
	for (; size < N; size <<= 1);
	return size << 1;
}

struct node
{
	LL bestl,bestr,best,sum;
};

node tree[131072];
LL A[50001];

node make_node(LL a)
{
	node temp;
	temp.bestl = temp.best = temp.bestr = temp.sum = a;
	return temp;
}

node merge(node& left,node& right)
{
	node temp;
	temp.bestl = left.bestl;
	if(left.sum + right.bestl > temp.bestl)
		temp.bestl = left.sum + right.bestl;


	temp.bestr = right.bestr;
	if(left.bestr + right.sum > temp.bestr)
		temp.bestr = left.bestr + right.sum;

	temp.sum = left.sum + right.sum;
	temp.best = max(left.bestr+right.bestl,max(left.best,right.best));
	return temp;
}

node build(int from,int to,int index)
{
	if(from==to)
	{
		tree[index] = make_node(A[from]);
		return tree[index];
	}

	int mid = (from+to)/2;
	node l = build( from,mid,index<<1 );
	node r = build( mid+1,to,(index<<1) + 1);
	
	tree[index] = merge(l,r);
	return tree[index];
}

node query(int from,int to,int index,int a,int b)
{
	if(from==a && to==b)
		return tree[index];

	int mid = (from+to)/2;
	if(a > mid)
		return query(mid+1,to,(index<<1)+1,a,b);
	if(b <= mid)
		return query(from,mid,index<<1,a,b);

	node l = query(from,mid,index<<1,a,mid);
	node r = query(mid+1,to,(index<<1)+1,mid+1,b);

	return merge(l,r);
}

void update(int from,int to,int index,int target)
{
	if(from==to)
	{
		tree[index] = make_node(A[from]);
		return;
	}

	int mid = (from+to)/2;
	if(target>mid)
		update(mid+1,to,(index<<1) +1,target);
	else
		update(from,mid,index<<1,target);

	tree[index] = merge(tree[index<<1],tree[(index<<1) + 1]);
}

int main(){
	int N;
	scanf("%d",&N);
	
	for(int i=1;i<=N;i++)
	scanf("%lld",&A[i]);
	
	build(1,N,1);
	
	int M,a,x,y;
	scanf("%d",&M);
	for(int i=0;i<M;i++)
	{
		scanf("%d %d %d",&a,&x,&y);
		if(a==0)
		{
			A[x] = y;
			update(1,N,1,x);
			continue;
		}
		printf("%lld\n",query(1,N,1,x,y).best);
	}

	return 0;
}