#include <bits/stdc++.h>
using namespace std;

#define GC getchar_unlocked
int read(){
	register char c=0;
	while(c<33)c=GC();
	int a =0;
	while(c>33){
		a=a*10+c-48;
		c=GC();
	}
	return a;
}

#define icin(x) (x=read())
#define pb push_back
#define mp make_pair

typedef long long LL;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

const int maxn=int(5e5)+1;

unsigned int seed = 7;
static unsigned int fastrand(){
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}

class Treap{
	struct _Node{
		int x, cnt, sz;
		int y;
		_Node *l, *r;
		_Node(int _x){
			x = _x;
			cnt = 0;
			sz = 1;
			y = fastrand();
			l = r = NULL;
		}
		~_Node(){
			delete l;
			delete r;
		}
		void inc(){
			++cnt;
		}
		bool dec(){
			--cnt;
			if(cnt>0)return false;
			return true;
		}
		int size(){
			return sz;
		}
		void recalc(){
			sz = 1;
			if(l) sz += l->size();
			if(r) sz += r->size();
		}
	};
	typedef struct _Node Node;
	typedef Node* pNode;

	void split(pNode v, int x, pNode &l, pNode &r) {
		l = r = NULL;
		if(!v) return;
		if(v->x <= x){
			split(v->r, x, v->r, r);
			l = v;
		}else{
			split(v->l, x, l, v->l);
			r = v;
		}
		v->recalc();
	}
	pNode merge(pNode l, pNode r){
		if(!l || !r) return l ? l : r;
		if(l->y < r->y){
			l->r = merge(l->r, r);
			l->recalc();
			return l;
		}else{
			r->l = merge(l, r->l);
			r->recalc();
			return r;
		}
	}
	public:
	pNode root;
	Treap(){
		root = NULL;
	}
	~Treap(){
		delete root;
	}
	void insert(int x){
		pNode l, m, r;
		split(root, x-1, l, m);
		split(m, x, m, r);
		if(!m) m = new Node(x);
		m->inc();
		root = merge(merge(l, m), r);
	}
	void erase(int x){
		pNode l, m, r;
		split(root, x-1, l, m);
		split(m, x, m, r);
		if(m->dec()){
			delete m;
			m = NULL;
		}
		root = merge(merge(l, m), r);
	}
	int count(int x){
		pNode l, r;
		split(root, x-1, l, r);
		int res = 0;
		if(r)res += r->size();
		root = merge(l, r);
		return res;
	}
};
class SegmentTree{
	struct Node{
		int l,r;
		Treap t;
		Node(){
			l=r=0;
		}
		void init(int _l, int _r, vi& v){
			l=_l, r=_r;
			for(int i=l;i<=r;++i)
				t.insert(v[i]);
		}
		void init(const Node& left, const Node& right, vi& v){
			init(left.l, right.r, v);
		}
		void change(int old_val, int new_val){
			t.erase(old_val);
			t.insert(new_val);
		}
		int count(int x){
			return t.count(x);
		}
	};
public:
	vi v;
	vector<Node> tree;
	SegmentTree(){
		v.resize(maxn);
		tree.resize(maxn<<2);
	}
	void build(int l, int r, int idx){
		if(l==r){
			tree[idx].init(l, r, v);
			return;
		}
		int mid = (l+r)>>1;
		build(l, mid, idx<<1);
		build(mid+1, r, (idx<<1)+1);
		tree[idx].init(tree[(idx<<1)], tree[(idx<<1)+1], v);
	}
	void update(int l, int r, int idx, int pos, int old_val, int new_val){
		if(l==r){
			tree[idx].change(old_val, new_val);
			return;
		}
		tree[idx].change(old_val, new_val);
		int mid = (l+r)>>1;
		if(pos<=mid){
			update(l, mid, (idx<<1), pos, old_val, new_val);
		}
		else{
			update(mid+1, r, (idx<<1)+1 , pos, old_val, new_val);	
		}
	}
	int query(int l, int r, int idx, int a, int b, int x){
		if(l==a && r==b){
			return tree[idx].count(x);
		}
		int mid = (l+r)>>1;
		if(a > mid){
			return query(mid+1, r,(idx<<1)+1, a, b, x);
		}
		else if(b <= mid){
			return query(l, mid, (idx<<1), a, b, x);
		}
		else{
			int ans = query(l, mid, (idx<<1) , a, mid, x);
			ans += query(mid+1, r, (idx<<1)+1, mid+1, b, x);
			return ans;
		}
	}
};
int main(){
	int n;
	icin(n);
	SegmentTree t;
	for(int i=1;i<=n; ++i){
		icin(t.v[i]);
	}
	t.build(1, n, 1);
	int q;
	icin(q);
	while(q--){
		int k, a, b, c;
		icin(k);icin(a);icin(b);
		if(k){
			t.update(1, n, 1, a, t.v[a], b);
			t.v[a]=b;
		}
		else{
			icin(c);
			printf("%d\n", t.query(1, n, 1, a, b, c));
		}
	}
	return 0;
}