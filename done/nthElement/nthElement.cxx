#include <vector>
#include <iostream>
#include <assert.h>
#include <map>
#include <algorithm>

class Node {
	friend class PersistanceSegmentTree;
	protected:
		Node(int val);
		Node( Node* node);
		Node * left=NULL;
		Node * right=NULL;
		int power;
};

typedef Node* PNode;

Node::Node(int val):power(val) {}
Node::Node(PNode node):left(node->left), right(node->right), power(node->power) {}

class PersistanceSegmentTree {
	private:
		int MAXN;
		std::vector<PNode> roots;
		std::map <int, int> sourceToCompressioned, compressionedToSource;
		void _buildTree(PNode& root, int begin, int end);
		void _inc(int pos, PNode& root, int begin, int end, PNode oldRoot);
		int _nthElement(PNode leftTreeNode, PNode rightTreeNode, int begin, int end, int add);
		
	public:
		PersistanceSegmentTree(std::vector<int> arr);
		int getNthElement(int begin, int end, int n);
};

void PersistanceSegmentTree::_buildTree(PNode& root, int begin, int end) {
	assert(end>begin);
	root=new Node(0);
	if (end-begin==1){
		return;
	}
	int mid=begin+(end-begin)/2;
	_buildTree(root->left, begin, mid);
	_buildTree(root->right, mid, end);
}

void PersistanceSegmentTree::_inc(int pos, PNode & root, int begin, int end, PNode oldRoot) {
	assert(end>begin);
	root=new Node(oldRoot);
	root->power+=1;
	if (end-begin==1) {
		return;
	}
	int mid=begin+(end-begin)/2;
	if (pos<mid) {
		_inc(pos, root->left, begin, mid, root->left);
	}
	else {
		_inc(pos, root->right, mid, end, root->right);
	}
}
		
		
PersistanceSegmentTree::PersistanceSegmentTree(std::vector<int> arr) {
	std::vector<int> tArr=arr;
	std::sort(tArr.begin(), tArr.end());
	for (int i=0;i<(int) tArr.size();++i) {
		if (sourceToCompressioned.find(tArr[i])==sourceToCompressioned.end()) {
			sourceToCompressioned[tArr[i]]=i;
			compressionedToSource[i]=tArr[i];
		}
	}
	MAXN=arr.size();	
	roots.resize(MAXN);
	_buildTree(roots[0], 0, MAXN);
	for (int i=1;i<=(int) arr.size(); ++i) {
		_inc(sourceToCompressioned[arr[i-1]],  roots[i], 0, MAXN, roots[i-1]);
	} 
}
		
int PersistanceSegmentTree::_nthElement(PNode leftTreeNode, PNode rightTreeNode, int begin, int end, int add) { 
	if (end-begin==1) {
		return begin;
	}
	int mid=begin+(end-begin)/2;
	if (add<rightTreeNode->left->power-leftTreeNode->left->power) {
		return _nthElement(leftTreeNode->left, rightTreeNode->left, begin, mid, add);
	}
	add-=rightTreeNode->left->power-leftTreeNode->left->power;
	return _nthElement(leftTreeNode->right, rightTreeNode->right, mid, end, add);
}
		
int PersistanceSegmentTree::getNthElement(int begin, int end, int n) {
	return compressionedToSource[_nthElement(roots[begin], roots[end] ,0, MAXN, n)];
}

int main() {
	
	int sizeOfArray, begin, end, n;
	std::cin >> sizeOfArray;
	std::vector<int> arr(sizeOfArray);
	for (int i=0;i<sizeOfArray;++i) {
		std::cin >> arr[i];
	}
	PersistanceSegmentTree nes(arr);
	while(!std::cin.eof()) {
		std::cin >> begin >> end >> n;
		std::cout << nes.getNthElement(begin, end, n) << std::endl;
	}
	return 0;

}
