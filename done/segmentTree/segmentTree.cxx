#include <string>
#include <iostream>
#include <assert.h>
#include <vector>

class Node {
	friend class SegmentTree;
	public:
		Node(long long int val);
	protected:
		Node * left=NULL;
		Node * right=NULL;
		long long int hash;
		long long int rHash;
};

typedef Node* PNode;

Node::Node(long long int val):hash(val), rHash(val) {}

class SegmentTree {
	private:
		PNode root;
		int size;
		std::vector<long long int> nthP;
		long long int p=127, q=10e9+7;
		long long int _nthP(int degree);
		void _buildTree(PNode& root, int begin, int end, std::string& string);
		void _updateNode(PNode node, int begin, int end);
		void _updateChar(PNode& root, int begin, int end, int pos, char newChar);
		long long int _getHash(PNode root, int begin, int end, int stringBegin, int stringEnd);
		long long int _getRHash(PNode root, int begin, int end, int stringBegin, int stringEnd);
		
	public:
		SegmentTree(std::string string);
		void updateChar(int pos, char newChar);
		bool isPalindrome(int stringBegin, int stringEnd);
};

void SegmentTree::_updateNode(PNode node, int begin, int end) {
	assert(end-begin>1);
	assert(node);
	int mid=begin+(end-begin)/2;
	assert(node->left);
	assert(node->right);
	node->hash=(node->left->hash*_nthP(end-mid)+node->right->hash)%q;
	node->rHash=(node->right->rHash*_nthP(mid-begin)+node->left->rHash)%q;	
}

void SegmentTree::_buildTree(PNode& root, int begin, int end, std::string& string) {
	assert(end>begin);
	root=new Node(string[begin]);
	if (end-begin==1){
		return;
	}
	int mid=begin+(end-begin)/2;
	_buildTree(root->left, begin, mid, string);
	_buildTree(root->right, mid, end, string);
	_updateNode(root, begin, end);
}

SegmentTree::SegmentTree(std::string string) {
	nthP.push_back(1);
	for (int i=1;i<=(int) string.size();++i) {
		nthP.push_back((nthP.back()*p)%q);
	}
	_buildTree(root, 0, string.size(), string);
	size=string.size();
	
}

long long int SegmentTree::_nthP(int degree) {
	return nthP[degree];
}
		
void SegmentTree::_updateChar(PNode& root, int begin, int end, int pos, char newChar) {
	assert(end>begin);
	if (end-begin==1) {
		root->hash=newChar;
		root->rHash=newChar;
		return;
	}
	int mid=begin+(end-begin)/2;
	if (pos<mid) {
		_updateChar(root->left, begin, mid, pos, newChar);
	}
	else {
		_updateChar(root->right, mid, end, pos, newChar);
	}
	_updateNode(root, begin, end);
}	

void SegmentTree::updateChar(int pos, char newChar) {
	//std::cout << ' ' << pos << ' '<< (int) newChar;
	assert(pos<size);          
	_updateChar(root, 0, size, pos, newChar);
}

long long int SegmentTree::_getHash(PNode root, int begin , int end, int stringBegin, int stringEnd) {
	assert(end-begin>0);
	if ((stringBegin<=begin)&&(end<=stringEnd)) {
		return root->hash*_nthP(stringEnd-end)%q;
	}
	if ((end<=stringBegin) || (stringEnd<=begin)) {
		return 0;
	}
	int mid=begin+(end-begin)/2;
	return (_getHash(root->left, begin, mid, stringBegin, stringEnd)+_getHash(root->right, mid, end, stringBegin, stringEnd))%q;
}

long long int SegmentTree::_getRHash(PNode root, int begin, int end, int stringBegin, int stringEnd) {
	assert(end-begin>0);
	if ((stringBegin<=begin)&&(end<=stringEnd)) {
		return root->rHash*_nthP(begin-stringBegin)%q;
	}
	if ((end<=stringBegin)||(stringEnd<=begin)) {
		return 0;
	}
	int mid=begin+(end-begin)/2;
	return (_getRHash(root->left, begin, mid, stringBegin, stringEnd)+_getRHash(root->right, mid, end, stringBegin, stringEnd))%q;
}

bool SegmentTree::isPalindrome(int begin, int end) {
	assert(end<=size);
	assert(end>begin);
	return (_getHash(root, 0, size, begin, end)==_getRHash(root, 0, size, begin, end));
}

int main(int argc, char **argv){
	std::string basicString, command;
	int pos, begin, end;
	char val;
	std::cin >> basicString;
	SegmentTree string(basicString);
	while(!std::cin.eof()) {
		std::cin >> command;
		switch (command[0]) {
			case 'u':
				std::cin >> val >> pos;
				string.updateChar(pos, val);
				break;
			case 'i':
				std::cin >> begin >> end;
				std::cout << string.isPalindrome(begin, end) << std::endl;
				break;
		}
	
	}
	return 0;
}

