#include <vector>
#include <iostream>
#include <algorithm>
#include <assert.h>
#include <stdio.h>
#include <map>

class NNode {
	friend class PersistanceSegmentTree;
	protected:
		NNode(long long int val);
		NNode( NNode* NNode);
		NNode * left;
		NNode * right;
		long long int power;
};

typedef NNode* PNNode;

NNode::NNode(long long int val):power(val), left(NULL), right(NULL) {}
NNode::NNode(PNNode NNode):left(NNode->left), right(NNode->right), power(NNode->power) {}

class PersistanceSegmentTree {
	private:
		long long int MAXN;
		std::vector<PNNode> roots;
		//~ std::map <long long int, long long int> sourceToCompressioned, compressionedToSource;
		void _buildTree(PNNode& root, long long int begin, long long int end);
		void _inc(long long int pos, PNNode& root, long long int begin, long long int end, PNNode oldRoot);
		long long int _nthElement(PNNode leftTreeNNode, PNNode rightTreeNNode, long long int begin, long long int end, long long int add);
		
	public:
		PersistanceSegmentTree(std::vector<long long int> arr);
		long long int getNthElement(long long int begin, long long int end, long long int n);
};

void PersistanceSegmentTree::_buildTree(PNNode& root, long long int begin, long long int end) {
	assert(end>begin);
	root=new NNode((long long int) 0);
	if (end-begin==1){
		return;
	}
	long long int mid=begin+(end-begin)/2;
	_buildTree(root->left, begin, mid);
	_buildTree(root->right, mid, end);
}

void PersistanceSegmentTree::_inc(long long int pos, PNNode & root, long long int begin, long long int end, PNNode oldRoot) {
	assert(end>begin);
	root=new NNode(oldRoot);
	root->power+=1;
	if (end-begin==1) {
		return;
	}
	long long int mid=begin+(end-begin)/2;
	if (pos<mid) {
		_inc(pos, root->left, begin, mid, root->left);
	}
	else {
		_inc(pos, root->right, mid, end, root->right);
	}
}
		
		
PersistanceSegmentTree::PersistanceSegmentTree(std::vector<long long int> arr) {
	//~ prlong long intf("fuck1\n");
	//~ for (size_t i=0;i<arr.size();++i) {
		//~ std::cout << arr[i] << ' ';
	//~ }
	std::vector<long long int> tArr=arr;
	std::sort(tArr.begin(), tArr.end());
	//~ for (long long int i=0;i<(long long int) tArr.size();++i) {
		//~ if (sourceToCompressioned.find(tArr[i])==sourceToCompressioned.end()) {
			std::map <int, int> sourceToCompressioned;
			sourceToCompressioned[tArr[0]]= 0;
			//~ compressionedToSource[i]=tArr[i];
		//~ }
	//~ }
	MAXN=arr.size();	
	roots.resize(MAXN);
	_buildTree(roots[0], 0, MAXN);
	for (long long int i=1;i<=(long long int) arr.size(); ++i) {
		_inc(arr[i-1],  roots[i], 0, MAXN, roots[i-1]);
	} 
}
		
long long int PersistanceSegmentTree::_nthElement(PNNode leftTreeNNode, PNNode rightTreeNNode, long long int begin, long long int end, long long int add) { 
	
	if (end-begin==1) {
		return begin;
	}
	long long int mid=begin+(end-begin)/2;
	if (add<rightTreeNNode->left->power-leftTreeNNode->left->power) {
		return _nthElement(leftTreeNNode->left, rightTreeNNode->left, begin, mid, add);
	}
	add-=rightTreeNNode->left->power-leftTreeNNode->left->power;
	return _nthElement(leftTreeNNode->right, rightTreeNNode->right, mid, end, add);
}
		
long long int PersistanceSegmentTree::getNthElement(long long int begin, long long int end, long long int n) {
	return _nthElement(roots[begin+1], roots[end+1] ,0, MAXN, n-1);
}

class Node {
	friend class PersistantSegmentTree;
	protected:
		Node();
		Node(long long int a);
		Node(Node* pnode);
		long long int sum, max;
		Node* left,* right;
		void update();
};
	
typedef Node *PNode;

Node::Node(const long long int val): sum(val),max(val),  left(NULL), right(NULL) {}
Node::Node(): sum(0), max(0),  left(NULL), right(NULL) {}
Node::Node(const PNode pnode):sum(pnode->sum), max(pnode->max), left(pnode->left), right(pnode->right) {}

void Node::update() {
	sum=0;
	max=0;
	if (left) {
		sum+=left->sum;
		max=std::max(max, left->max);
	}
	if (right) {
		sum+=right->sum;
		max=std::max(max, right->max);
	}
}


class PersistantSegmentTree {
	private:
		long long int sizeOfTree;
		std::vector < PNode > segmentTree;
		void _build(PNode& segmentTree, long long int begin, long long int end);
		long long int _getSum(const PNode segmentTree, long long int begin, long long int end, long long int l, long long int r) const;
		long long int _getMax(const PNode segmentTree, long long int begin, long long int end, long long int l, long long int r) const;
		void _add(const PNode oldSegmentTree, PNode& newSegmentTree, long long int begin, long long int end, long long int pos, long long int val);
		std::vector <long long int> getCompressedVector(const std::vector <long long int>& source);
		std::vector < std::pair < long long int, long long int > > tSource;
	public:
		PersistanceSegmentTree nthElementTree;
		PersistantSegmentTree(const std::vector<long long int>& source);
		long long int getSum(long long int version, long long int l, long long int r) const;
		long long int getMax(long long int version, long long int l, long long int r) const;
		long long int getMedian(long long int l, long long int r);		
		long long int getMovingMean(long long int l, long long int r);
};

void PersistantSegmentTree::_build(PNode& segmentTree, long long int begin, long long int end) {
	segmentTree=new Node();
	if (end-begin==1) {
		return;
	}
	long long int m=begin+(end-begin)/2;
	_build(segmentTree->left, begin, m);
	_build(segmentTree->right, m, end);
	segmentTree->update();
}

void PersistantSegmentTree::_add(const PNode oldSegmentTree, PNode& newSegmentTree, long long int begin, long long int end, long long int pos, long long int val) {
	if (end-begin==1) {
		newSegmentTree=new Node(val);
		return;
	}
	newSegmentTree=new Node(oldSegmentTree);
	long long int m=begin+(end-begin)/2;
	if (pos<m) {
		_add(oldSegmentTree->left, newSegmentTree->left, begin, m, pos, val);
	}
	else {
		_add(oldSegmentTree->right, newSegmentTree->right, m, end, pos, val);
	}
	newSegmentTree->update();
}

std::vector <long long int> PersistantSegmentTree::getCompressedVector(const std::vector <long long int>& source) {
	//prlong long intf("fuck2\n");
	tSource.resize(source.size());
	for (size_t i=0;i<source.size();++i) {
		tSource[i]=std::make_pair(source[i], i);
	}
	sort(tSource.begin(), tSource.end());
	std::vector<long long int> ttSource(source.size()+1);
	for (size_t i=0;i<source.size();++i) {
		ttSource[tSource[i].second+1]=i+1;
	}
	ttSource[0]=0;
	//~ for (size_t i=0;i<ttSource.size();++i) {
		//~ std::cout << ttSource[i] << ' ';
	//~ }
	//prlong long intf("fuck2.1\n");
	return ttSource;
}

PersistantSegmentTree::PersistantSegmentTree(const std::vector < long long int >& source):nthElementTree(getCompressedVector(source)),segmentTree(source.size()) {//поправь конструктор percictanseSegmentTree
	//prlong long intf("fuck3\n");
	sizeOfTree=source.size();
	_build(segmentTree[0], 0, sizeOfTree);
	//~ std::vector < std::pair < long long int, long long int > > tSource(sizeOfTree);
	//~ for (long long int i=0;i<sizeOfTree;++i) {
		//~ tSource[i]=std::make_pair(source[i], i);
	//~ }
	//~ sort(tSource.begin(), tSource.end());
	for (long long int i=0;i<sizeOfTree;++i) {
		_add(segmentTree[i], segmentTree[i+1], 0, sizeOfTree, tSource[i].second, tSource[i].first);
	}
}



long long int PersistantSegmentTree::_getSum(const PNode segmentTree, long long int begin, long long int end, long long int l, long long int r) const {
	if ((l<=begin)&&(end<=r)) {
		return segmentTree->sum;
	}
	if ((r<=begin)||(end<=l)) {
		return 0;
	}
	long long int m=begin+(end-begin)/2;
	return _getSum(segmentTree->left, begin, m, l, r)+_getSum(segmentTree->right, m, end, l, r);
}

long long int PersistantSegmentTree::_getMax(const PNode segmentTree, long long int begin, long long int end, long long int l, long long int r) const {
	if ((l<=begin)&&(end<=r)) {
		return segmentTree->max;
	}
	if ((r<=begin)||(end<=l)) {
		return 0;
	}
	long long int m=begin+(end-begin)/2;
	return std::max(_getMax(segmentTree->left, begin, m, l, r), _getMax(segmentTree->right, m, end, l, r));
}

long long int PersistantSegmentTree::getSum(long long int version, long long int l, long long int r) const  {
	return _getSum(segmentTree[version], 0, sizeOfTree, l, r);
}

long long int PersistantSegmentTree::getMax(long long int version, long long int l, long long int r) const  {
	return _getMax(segmentTree[version], 0, sizeOfTree, l, r);
}

long long int PersistantSegmentTree::getMedian(long long int l, long long int r) {

	return getMax(nthElementTree.getNthElement(l, r, (r-l+1)/2) , l, r);
}

long long int PersistantSegmentTree::getMovingMean(long long int l, long long int r) {
	return (getSum(nthElementTree.getNthElement(l, r, r-l-(r-l)/10), l, r)-getSum(nthElementTree.getNthElement(l, r, (r-l)/10), l, r))/((r-l)-((r-l)/10)*2);
}

int main(int argc, char **argv)
{
	long long int n, m;
	scanf("%lld%lld",&n,&m);
	std::vector < long long int> source(n);
	for (long long int i=0;i<n;++i) {
		 //std::cin >> source[i];
		 scanf("%lld", &source[i]);
	}
	PersistantSegmentTree arr(source);
	
	for (long long int i=0;i<m;++i) {
		long long int l,r;
		scanf("%lld%lld", &l, &r);
		--l;
		//std::cout << abs( arr.getMedian(l,r) - arr.getMovingMean(l,r)) << std::endl;
		printf("%lld\n", abs( arr.getMedian(l,r) - arr.getMovingMean(l,r)));
		//~ if (i>90000) {
			//~ exit(0);
		//~ }
		//std::cout << arr.nthElementTree.getNthElement(l, r, (r-l+1)/2) << ' ' <<arr.getMedian(l,r) << ' ' << arr.getMovingMean(l,r) << std::endl;
		//~ for (size_t j=0;j<=source.size();++j) {
			//~ prlong long intf("%d %lld %lld\t", arr.getPower(j, l, r), arr.getSum(j, l, r), arr.getMax(j,l,r));
		//~ }
		 
	}
	//prlong long intf("fuck\n");
	//exit(0);
	return 0;
}
