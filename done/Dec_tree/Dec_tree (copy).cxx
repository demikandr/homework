#include <iostream>
#include <set>
#include <random>
#include <string>


typedef std::mt19937 RNG;
		
class Random{
	private:
		RNG rng;
		std::uniform_int_distribution<uint32_t> uint_dist;
	public:
		Random(int seed);
		Random();
		int getRandomInt();		
};

Random::Random(int seed) {
	rng.seed(seed);
}

Random::Random() {
	rng.seed(10);
}

int Random::getRandomInt() {
	return uint_dist(rng);
}

class Node {
	friend class Treap;
	public:
		Node(int val, int priority);
	protected:
		Node * left=NULL;
		Node * right=NULL;
		bool reversed=false;
		int val;
		int priority;
		int sum;
		int power=1;
		int orderedPrefixLength=1;
		int orderedSuffixLength=1;
		int rightestVal;
		int leftestVal;
};

typedef Node* PNode;

Node::Node(int val, int priority):val(val), priority(priority),sum(val), rightestVal(val), leftestVal(val) {}

class Treap {
	public:
		Treap();
		Treap(int seed);
		void push(int val, int pos);
		int getVal(int pos);
		void update(int val, int pos);
		int sum(int begin, int end);
		void nextPermutation(int begin, int end);
		void print();
	private:
		int _sum(PNode root,int begin, int end);
		Node * root=NULL;
		Random random;
		std::set<int> priorities;
		void _reverse(PNode root, int begin, int end);
		void _push(int val, int pos, int priority);
		void _split(PNode subRoot, PNode &leftRoot, PNode &rightRoot, int key);
		void _merge(PNode &subPRoot, PNode leftRoot, PNode rightRoot);
		void _pushReverse(PNode& node);
		void _updateNode(PNode& node);
};

Treap::Treap(): random(0){}

Treap::Treap(int seed): random(seed) {}

void Treap::_pushReverse(PNode& node) {
	if (!node) {
		return;
	}
	if (node->reversed) {
		std::swap(node->left,node->right);
		if (node->left) {
			node->left->reversed=!node->left->reversed;
		}
		if (node->right) {
			node->right->reversed=!node->right->reversed;
		}
		std::swap(node->leftestVal,node->rightestVal);
		std::swap(node->orderedPrefixLength,node->orderedSuffixLength);
	}
	node->reversed=false;
}

void Treap::_updateNode(PNode &node) {
	if (!node) {
		return;
	}
	node->power=1;
	node->sum=node->val;
	if (node->left) {
		_pushReverse(node->left);
		node->power+=node->left->power;
		node->sum+=node->left->sum;
		node->leftestVal=node->left->leftestVal;
	}
	else {
		node->leftestVal=node->val;
	}
	if (node->right) {
		_pushReverse(node->right);
		node->power+=node->right->power;
		node->sum+=node->right->sum;
		node->rightestVal=node->right->rightestVal;
	}
	else {
		node->rightestVal=node->val;
	}
	node->orderedPrefixLength=1;
	node->orderedSuffixLength=1;
	if (node->left && node->right) {
		node->orderedPrefixLength=node->left->orderedPrefixLength;
		if (node->left->orderedPrefixLength==node->left->power) {
			if (node->left->rightestVal<=node->val) {
				if (node->val<=node->right->leftestVal) {
					node->orderedPrefixLength+=1+node->right->orderedPrefixLength;
				}
				else {
					node->orderedPrefixLength+=1;
				}
			}
		}
		node->orderedSuffixLength=node->right->orderedSuffixLength;
		if (node->right->orderedSuffixLength==node->right->power) {
			if (node->val>=node->right->leftestVal) {
				if (node->left->rightestVal>=node->val) {
					node->orderedSuffixLength+=1+node->left->orderedSuffixLength;
				}
				else {
					node->orderedSuffixLength+=1;
				}
			}
		}
	}
	else if  (node->left) {
		node->orderedPrefixLength=node->left->orderedPrefixLength;
		if (node->left->orderedPrefixLength==node->left->power) {
			if (node->left->rightestVal<=node->val) {
				node->orderedPrefixLength+=1;
			}
		}
		if (node->left->rightestVal>=node->val) {
			node->orderedSuffixLength=1+node->left->orderedSuffixLength;
		}
	}
	else if (node->right) {
		node->orderedSuffixLength=node->right->orderedSuffixLength;
		if (node->right->orderedSuffixLength==node->right->power) {
			if (node->val>=node->right->leftestVal) {
				node->orderedSuffixLength+=1;
			}
		}
		if (node->val<=node->right->leftestVal) {
			node->orderedPrefixLength=1+node->right->orderedPrefixLength;
		}
	}
		
		
}
			
void Treap::_merge(PNode &subRoot, PNode leftRoot, PNode rightRoot) {
	if (leftRoot == NULL) {
		subRoot=rightRoot;
	}
	else if (rightRoot == NULL) {
		subRoot=leftRoot;
	}
	else if (leftRoot->priority < rightRoot->priority) {
		_pushReverse(leftRoot);
		_merge(leftRoot->right, leftRoot->right, rightRoot);
		_updateNode(leftRoot);
		subRoot=leftRoot;
	}
	else {
		_pushReverse(rightRoot);
		_merge(rightRoot->left, leftRoot, rightRoot->left);
		_updateNode(rightRoot);
		subRoot=rightRoot;
	}
}			
		
void Treap::_split(PNode subRoot, PNode &leftRoot, PNode &rightRoot, int key) {
	if (!subRoot) {
		leftRoot=NULL;
		rightRoot=NULL;
		return;
	}
	_pushReverse(subRoot);
	if ((subRoot->left && (subRoot->left->power >= key) )|| ((!subRoot->left)&&(key==0))) {
		_split(subRoot->left, leftRoot, subRoot->left, key);
		_updateNode(subRoot);
		rightRoot=subRoot;
	}
	else {
		if (subRoot->left) {
			key-=subRoot->left->power;
		}
		key--;
		_split(subRoot->right, subRoot->right, rightRoot, key);
		_updateNode(subRoot);
		leftRoot=subRoot;
	}
}

void Treap::_push(int val, int pos, int priority){
	PNode leftNode, rightNode, node=new Node(val, priority);
	_split(root, leftNode, rightNode, pos);	
	_merge(node, node, rightNode);
	_merge(root, leftNode, node);
}

void Treap::push(int val, int pos) {
	int tRand=random.getRandomInt();
	while (priorities.find(tRand)!=priorities.end()) {
		tRand=random.getRandomInt();
	}
	priorities.insert(tRand);
	_push(val, pos, tRand);
}

void Treap::update(int val, int pos) {
	PNode leftNode, rightNode,node;
	_split(root, leftNode, rightNode, pos);	
	_split(rightNode, node, rightNode, 1);
	(*node).val=val;
	_updateNode(node);
	_merge(node, node, rightNode);
	_merge(root, leftNode, node);
}

int Treap::_sum(PNode root, int begin, int end) {
	PNode leftNode, rightNode,node;
	_split(root, leftNode, rightNode, begin);
	_split(rightNode, node, rightNode, end-begin);
	int sum=node->sum;
	_merge(node, node, rightNode);
	_merge(root, leftNode, node);
	return sum;
}
int Treap::sum(int begin, int end) {
	return _sum(root, begin, end);
}

void Treap::_reverse(PNode root, int begin, int end) {
	PNode leftNode, rightNode,node;
	_split(root, leftNode, rightNode, begin);	
	_split(rightNode, node, rightNode, end-begin);
	(*node).reversed=!(*node).reversed;
	_merge(node, node, rightNode);
	_merge(root, leftNode, node);
}

int Treap::getVal(int pos) {
	return sum(pos, pos+1);
}

void Treap::print() {
	if (root) {
		for (int i=0;i<(*root).power;++i) {
			std::cout << getVal(i) << ' ';
		}
		//std::cout << std::endl << root->orderedSuffixLength << ' ' << root->orderedPrefixLength;
	}
	else {
		std::cout << "tree is empty";
	}
		
}
void Treap::nextPermutation(int begin, int end) {
	int orderedPrefixBegin;
	PNode leftNode, rightNode,node;
	_split(root, leftNode, rightNode, begin);			//Выделили
	_split(rightNode, node, rightNode, end-begin);		//подотрезок
	_pushReverse(node);
	orderedPrefixBegin=end-node->orderedSuffixLength;	//в абсолютных координатах
	if (node->orderedSuffixLength!=node->power) {
		PNode leftSubNode, rightSubNode,leftEl, rightEl, subNode;
		_split(node, leftSubNode, node, orderedPrefixBegin-begin);//leftSubNode node[orderedSuffix]
		_pushReverse(leftSubNode);
		_pushReverse(node);	
		node->reversed=!node->reversed;		
		_pushReverse(node);						
		subNode=node;
		_pushReverse(leftSubNode);
		int add=orderedPrefixBegin, fuckingValIndex;
		while (true) {
			if (subNode->left) {
				_pushReverse(subNode->left);
				if (subNode->left->rightestVal > leftSubNode->rightestVal) {
					subNode=subNode->left;
					_pushReverse(subNode);
					continue;
				}
				add+=subNode->left->power;
			}
			if (subNode->val > leftSubNode->rightestVal) {
				fuckingValIndex=add;
				break;
			}
			add+=1;
			subNode=subNode->right;
			_pushReverse(subNode);
		}
		_split(leftSubNode,leftSubNode,leftEl,orderedPrefixBegin-1-begin);
		_split(node,node,rightSubNode,fuckingValIndex-orderedPrefixBegin);
		_split(rightSubNode,rightEl,rightSubNode,1);
		_merge(rightSubNode,leftEl,rightSubNode);
		_merge(leftSubNode,leftSubNode,rightEl);
		_merge(node,leftSubNode,node);
		_merge(node,node,rightSubNode);
	}
	else {
		node->reversed=!node->reversed;
	}
	_merge(node, node, rightNode);
	_merge(root, leftNode, node);
}
int main(int argc, char **argv)
{
	Treap treap;
	std::string command;
	int val, pos, begin, end;
	while (!std::cin.eof()) {
		std::cin >> command;
		switch(command[0]) {
			case 'u':
				std::cin >> val >> pos;
				treap.update(val, pos);
				break;
			case 's':
				std::cin >> begin >> end;
				std::cout << treap.sum(begin, end);
				break;
			case 'g':
				std::cin >> pos;
				std::cout << treap.getVal(pos);
				break;
			case 'p':
				if (command[1]=='u') {
					std::cin >> val >> pos;
					treap.push(val, pos);
				}
				else {
					treap.print();
				}
				break;
			case 'n':
				std::cin >> begin >> end;
				treap.nextPermutation(begin, end);
				break;
		}
		//~ std::cout << std::endl;
		//~ treap.print();
		std::cout << std::endl;
	}
	return 0;
}

