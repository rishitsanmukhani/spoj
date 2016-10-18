#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define push_back pb
#define make_pair mp
typedef long long LL;

struct Node{
	int l,r;
	int m1,m2;
};
const int maxn=int(2e5)+1;
Node tree[3*maxn];
int A[maxn];

Node merge(Node& left,Node& right){
	Node res;
	res.l=left.l;res.r = right.r;
	res.m1 = max(left.m1, right.m1);
	res.m2 = max(left.m1 + right.m1 - res.m1, max(left.m2, right.m2));
	return res;
}
void build(int from,int to,int index){
	if(from==to){
		tree[index].l = from;
		tree[index].r = to;
		tree[index].m1 = A[from];
		tree[index].m2 = -1;
		return;
	}
	int mid = (from+to)>>1;
	build(from, mid, index<<1);
	build(mid+1, to, (index<<1) + 1);
	tree[index] = merge(tree[index<<1],tree[(index<<1)+1]);
}
Node query(int from,int to,int index,int a,int b){
	if(from==a && to==b){
		return tree[index];
	}
	int mid = ((from+to)>>1);
	if(a > mid){
		return query(mid+1,to,(index<<1)+1,a,b);
	}
	else if(b <= mid){
		return query(from,mid,index<<1,a,b);
	}
	else{
		Node left = query(from,mid,index<<1,a,mid);
		Node right =  query(mid+1,to,(index<<1)+1,mid+1,b);
		return merge(left,right);
	}
}
void update(int from,int to,int index,int a){
	if(from==to){
		tree[index].m1 = A[from];
		return;
	}
	int mid = (from+to)>>1;
	if(a>mid)
		update(mid+1,to,(index<<1)+1,a);
	else
		update(from,mid,index<<1,a);
	tree[index] = merge(tree[index<<1],tree[(index<<1)+1]);
}
int main(){
	int n,q;
	icin(n);
	for(int i=1;i<=n;i++){
		icin(A[i]);
	}
	build(1,n,1);

	icin(q);
	Node res;
	char a;
	int x,y;
	for(int i=0;i<q;i++){
		cin>>a;
		scanf("%d %d",&x,&y);
		switch(a){
			case 'Q':{
				res = query(1,n,1,x,y);
				printf("%d\n",res.m1 + res.m2);
				break;
			}
			case 'U':{
				A[x]=y;
				update(1,n,1,x);
				break;
			}
		}
	}
	return 0;
}