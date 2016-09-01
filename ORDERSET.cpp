#include <bits/stdc++.h>
using namespace std;

#define icin(x) scanf("%d",&x)
#define lcin(x) scanf("%lld",&x)
typedef long long LL;
typedef vector<int> vi;

uint32_t seed = 7;
static uint32_t fastrand(){
  seed ^= seed << 13;
  seed ^= seed >> 17;
  seed ^= seed << 5;
  return seed;
}

class Treap{
	struct _Node{
		int x, y, cnt, rank;
		_Node *l, *r;
		_Node(int _x){
			x = (_x);
			y = fastrand();
			cnt = 1;
			rank = 1;
			l = r = NULL;
		}
		~_Node(){
			delete l;
			delete r;
		}
		void recalc(){
			cnt = 1;
			rank = 1;
			if(l) cnt += l->cnt, rank += l->cnt;
			if(r) cnt += r->cnt;
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
		pNode l, r;
		split(root, x, l, r);
		root = merge(merge(l, new Node(x)), r);
	}
	void erase(int x){
		pNode l, m, r;
		split(root, x-1, l, m);
		split(m, x, m, r);
		delete m;
		root = merge(l, r);
	}
	int size() const{
		return root ? root->cnt : 0;
	}
	bool find(int x, pNode v){
		if(!v) return false;
		else if(v->x == x) return true;
		else if(x < v->x) return find(x, v->l);
		else return find(x, v->r);
	}
	int kth(int k, pNode v){
		if(v->rank == k) return v->x;
		else if(k < v->rank) return kth(k, v->l);
		else return kth(k - v->rank, v->r);
	}
	int count(int x){
		pNode l, r;
		split(root, x-1, l, r);
		int res = 0;
		if(l)res = l->cnt;
		root = merge(l, r);
		return res;
	}
};
int main(){
	Treap t;
	int q,x;
	icin(q);
	char c;
	for(int i=0;i<q;i++){
		cin>>c;
		icin(x);
		switch(c){
			case 'I':{
				if(!t.find(x, t.root))
					t.insert(x);
				break;
			}
			case 'D':{
				if(t.find(x, t.root))
					t.erase(x);
				break;
			}
			case 'K':{
				if(x>t.size())
					printf("invalid\n");
				else
					printf("%d\n", t.kth(x, t.root));
				break;
			}
			case 'C':{
				printf("%d\n", t.count(x));
				break;				
			}
		}
	}
}