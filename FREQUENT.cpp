#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define push_back pb
#define make_pair mp
typedef long long LL;

struct Node{
	int l,r;
	int val_l, val_r;
	int mode, mode_l, mode_r;
	void print(){
		printf("%d %d -> %d %d %d\n", l, r, mode_l, mode, mode_r);
	}
};
const int maxn=int(2e5)+1;
Node tree[3*maxn];
int A[maxn];

Node merge(Node& left,Node& right){
	Node res;
	res.l = left.l;
	res.r = right.r;
	res.val_l = left.val_l;
	res.val_r = right.val_r;

	if(left.val_l == right.val_l)
		res.mode_l = (left.mode_l + right.mode_l);
	else
		res.mode_l = left.mode_l;

	if(left.val_r == right.val_r)
		res.mode_r = (left.mode_r + right.mode_r);
	else
		res.mode_r = right.mode_r;

	res.mode = max(res.mode_l, res.mode_r);
	res.mode = max(res.mode, left.mode);
	res.mode = max(res.mode, right.mode);
	if(left.val_r == right.val_l){
		res.mode = max(res.mode, left.mode_r + right.mode_l);
	}
	return res;
}
void build(int from,int to,int index){
	if(from==to){
		tree[index].l = from;
		tree[index].r = to;
		tree[index].val_l = tree[index].val_r = A[from];
		tree[index].mode = tree[index].mode_l = tree[index].mode_r = 1;
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
int main(){
	while(1){
		int n,q;
		icin(n);
		if(!n)break;
		icin(q);
		for(int i=1;i<=n;i++){
			icin(A[i]);
		}
		build(1,n,1);
		// for(int i=1;i<=16;i++)tree[i].print();
		Node res;
		int x,y;
		for(int i=0;i<q;i++){
			icin(x);icin(y);
			res = query(1,n,1,x,y);
			printf("%d\n",res.mode);
		}
	}
	return 0;
}