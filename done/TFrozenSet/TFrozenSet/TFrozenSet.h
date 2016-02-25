#include <random>
#include <vector>
#include <iostream>


typedef std::mt19937 MyRandNumGen;
MyRandNumGen randNumGen;
std::uniform_int_distribution<uint32_t> randNum(0,1000000008);

const long long MAX_HASH=2e9;
template <class Key = int>
class Hash {	
	private:
		long long p=1000000009;
		std::vector<std::pair<long long, long long> > secondHashArgs;
		std::pair<long long, long long> firstHashArgs;
	public:
		Hash() {
			randNumGen.seed(0);
			}
		void secondHashResize(int size){
			secondHashArgs.resize(size);
		}
		void newFirstHash() {
			firstHashArgs.first=randNum(randNumGen);
			firstHashArgs.second=randNum(randNumGen);
		}
		void newSecondHash(int ind) {
			secondHashArgs[ind].first=randNum(randNumGen);
			secondHashArgs[ind].second=randNum(randNumGen);
		}
		int firstHash(Key key) {
			return (((long long)key)*firstHashArgs.first+firstHashArgs.second)%p;
		}
		
		int secondHash(int ind, Key key) {
			return (((long long) key)*secondHashArgs[ind].first+secondHashArgs[ind].second)%p;
		}
		void printArgs() {
			std::cout << firstHashArgs.first << ' ' << firstHashArgs.second << std::endl;
			for (int i=0;i<secondHashArgs.size();++i) {
				std::cout << secondHashArgs[i].first << ' ' << secondHashArgs[i].second << std::endl;
			}
		}
};
template < typename InputIterator, class Key, class hash=Hash<Key> >
class TFrozenSet {
	private:
		std::vector< std::vector <Key > > hashTable;
		std::vector< std::vector <bool> > used;
		hash hf;
	public:
		TFrozenSet (InputIterator first, InputIterator last, const hash &hf = hash());
		bool Contains( const Key & key) {
			int firstHash=hf.firstHash(key)%hashTable.size();
			if (hashTable[firstHash].empty())
				return false;
			int secondHash=hf.secondHash(firstHash,key)%hashTable[firstHash].size();
			return (key==hashTable[firstHash][secondHash])&&(used[firstHash][secondHash]);
		}
};
template < typename InputIterator, class Key, class hash >
TFrozenSet<InputIterator, Key, hash>::TFrozenSet(InputIterator first, InputIterator last, const hash & hf) {
	TFrozenSet::hf=hf;
	int countOfEl=0;
	for (InputIterator it=first; it!=last; ++it) {
		++countOfEl;
	}
	std::vector<std::vector< Key > > firstHashVector(countOfEl);
	while (true) {
		TFrozenSet::hf.newFirstHash();
		for (InputIterator it=first; it!=last; ++it) {
			firstHashVector[TFrozenSet::hf.firstHash(*it)%countOfEl].push_back(*it);
		}
		int sumOfVectorsSize=0;
		for (int i=0;i<countOfEl;++i) {
			sumOfVectorsSize+=firstHashVector[i].size()*firstHashVector[i].size();
		}
		if (sumOfVectorsSize < 4*countOfEl) {
			break;
		}
		for (int i=0;i<countOfEl;++i) {
			firstHashVector[i].clear();
		}
	}
	TFrozenSet::hf.secondHashResize(countOfEl);
	used.resize(countOfEl);
	hashTable.resize(countOfEl);
	for (int i=0;i<countOfEl;++i) {
		TFrozenSet::hf.newSecondHash(i);
		hashTable[i].resize(firstHashVector[i].size()*firstHashVector[i].size());
		used[i].resize(firstHashVector[i].size()*firstHashVector[i].size());
		bool secondStep=false;
		while ((!secondStep)&&(!firstHashVector[i].empty())) {
			secondStep=true;
			for (int j=0;j<used[i].size();++j) {
				used[i][j]=false;
			}
			used[i].assign(firstHashVector[i].size()*firstHashVector[i].size(),false);
			for (int j=0;j<firstHashVector[i].size();++j) {
				int newSecondHash=(TFrozenSet::hf.secondHash(i,firstHashVector[i][j]))%(used[i].size());
				if ((used[i][newSecondHash])&&(hashTable[i][newSecondHash]!=firstHashVector[i][j])) {
					secondStep=false;
					TFrozenSet::hf.newSecondHash(i);
					break;
				}
				else {
					used[i][newSecondHash]=true;
					hashTable[i][newSecondHash]=firstHashVector[i][j];
				}
			}
		}
	}
}

	
				
				
		
		
	
	
		
			
