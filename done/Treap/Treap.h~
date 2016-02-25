typedef struct pnode *node;
struct pnode{
	int x,y,cnt;
	node l,r;
	pnode(int x, int y):x(x),y(y),cnt(1),l(NULL),r(NULL) {}
};
int cnt(node &t) {
	return t ? t->cnt : 0;
}
void updateCnt(node &t) {
	if(t) {
		t->cnt=cnt(t->l)+cnt(t->r)+1;
	}
	
}
void printTree(node &t ) {
	if (t==NULL) {
		std::cout << "#";
		return;
	}
	std::cout << t->x;// << "(";
	//int k;
	//std::cin >> k;
	printTree(t->l);
	printTree(t->r);
	std::cout << t->x;// << ")";
}	
void split(node t, node &l, node &r, int  ind) {
	if (!t) {
		l=NULL;
		r=NULL;
		return;
	}
	if (ind<=cnt(t->l)) {
		split(t->l, l, t->l, ind);
		r=t;
	}
	else {
		split(t->r, t->r, r, ind-cnt(t->l)-1);
		l=t;
	}
	updateCnt(t);
}
void merge(node &t, node l, node r) {
	if (!l||!r) {
		t=l ? l : r;
	}
	else
	if (l->y > r->y) {
		merge(l->r, l->r, r);
		t=l;
	}
	else {
		merge(r->l,l,r->l);
		t=r;
	}
	updateCnt(t);
}
void insert(node &t, int heapKey, int val, int pos) {
	node tNew = new pnode(val,heapKey);
	node tl,tr;
	split(t,tl,tr,pos-1);
	merge(t,tNew,tr);
	
	merge(t,tl,t);
	//printTree(t);
}
int del(node &t, int pos) {
	node tl,tr,tt;
	split(t,tl,tr,pos);
	if (pos>0) {
	split(tl,tl,tt,pos-1);
	}
	int temp;
	printf("another bitches son is %d\n",tt->x);
	temp=cnt(tl);
	merge(t,tl,tr);
	return temp;
}

