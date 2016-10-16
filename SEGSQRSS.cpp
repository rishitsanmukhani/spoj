#include <bits/stdc++.h>
using namespace std;
#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;
#define INF ((int)1e9)

struct SegmentTree{
	struct Node{
		int l, r;
		LL sum[2];
		LL lazy[2];
		void init(int i, int x){
			l = r = i;
			sum[0] = x*x;
			sum[1] = x;
			lazy[0] = 0;
			lazy[1] = INF;
		}
		void merge(Node& left, Node& right){
			l = left.l, r = right.r;
			sum[0] = left.sum[0] + right.sum[0];
			sum[1] = left.sum[1] + right.sum[1];
			lazy[0] = 0;
			lazy[1] = INF;
		}
		void update(LL x_add, LL x_rep){
			if(x_rep!=INF){
				sum[0] = (r-l+1)*x_rep*x_rep;
				sum[1] = (r-l+1)*x_rep;
				lazy[0] = 0;
				lazy[1] = x_rep;
			}
			lazy[0] += x_add;
			sum[0] = sum[0] + 2*sum[1]*x_add + (r-l+1)*x_add*x_add;
			sum[1] = sum[1] + (r-l+1)*x_add;
		}
	};
	vector<Node> tree;
	vector<int> A;
	void build(int l, int r, int idx){
		if(l==r){
			tree[idx].init(l, A[l]);
			return;
		}
		int mid = (l+r)>>1;
		build(l, mid, (idx<<1));
		build(mid+1, r, (idx<<1)|1);
		
		tree[idx].merge(tree[idx<<1], tree[(idx<<1)|1]);
	}
	Node query(int l, int r, int idx, int a, int b){
		if(l==a && r==b){
			return tree[idx];
		}
		propogate(idx);
		int mid = (l+r)>>1;
		if(a>mid){
			return query(mid+1, r, (idx<<1)|1, a, b);
		}
		else if(b<=mid){
			return query(l, mid, (idx<<1), a, b);
		}
		else{
			Node left = query(l, mid, (idx<<1), a, mid);
			Node right = query(mid+1, r,(idx<<1)|1 , mid+1, b);
			Node res;
			res.merge(left, right);
			return res;
		}
	}
	void update(int l, int r, int idx, int a, int b, int x_add,int x_rep){
		if(l==a && r==b){
			tree[idx].update(x_add, x_rep);
			return;
		}
		propogate(idx);
		int mid = (l+r)>>1;
		if(a>mid){
			update(mid+1, r, (idx<<1)|1, a, b, x_add, x_rep);
		}
		else if(b<=mid){
			update(l, mid, (idx<<1), a, b, x_add, x_rep);
		}
		else{
			update(l, mid, (idx<<1), a, mid, x_add, x_rep);
			update(mid+1, r, (idx<<1)|1, mid+1, b, x_add, x_rep);
		}
		tree[idx].merge(tree[idx<<1], tree[(idx<<1)|1]);
	}
	void propogate(int idx){
		tree[(idx<<1)].update(tree[idx].lazy[0], tree[idx].lazy[1]);
		tree[(idx<<1)|1].update(tree[idx].lazy[0], tree[idx].lazy[1]);
		tree[idx].lazy[0]=0;
		tree[idx].lazy[1]=INF;
	}
};

int main(){
	int t;
	icin(t);
	SegmentTree T;
	for(int tc=1;tc<=t;tc++){
		printf("Case %d:\n",tc);
		int n, q;
		icin(n);icin(q);
		T.A.resize(n);
		T.tree.resize(4*n);
		for(int i=1;i<=n;i++){
			icin(T.A[i]);
		}
		T.build(1, n, 1);
		int c,a,b,x=0;
		for(int i=0;i<q;i++){
			icin(c);icin(a);icin(b);
			if(c==2){
				printf("%lld\n",T.query(1, n, 1, a, b).sum[0]);
			}
			else if(c==1){
				icin(x);
				T.update(1, n, 1, a, b, x, INF);
			}
			else{
				icin(x);
				T.update(1, n, 1, a, b, 0, x);
			}
		}
	}
	return 0;
}