#include <vector>
#include <algorithm>
#include <queue>

template <typename T>
class TTopElements {
private:
	std::vector <T> heap;
	size_t countOfMax;
public:
    TTopElements(size_t topSize);
    void Add(const T & elem);
    void GetCurrentTop(std::vector<T> & top);
};

template <typename T>
TTopElements<T>::TTopElements(size_t topSize) {
	countOfMax=topSize;
}

template <typename T>
void TTopElements<T>::Add(const T & elem) {
	heap.push_back(elem);
	std::push_heap(heap.begin(),heap.end(),std::greater<T>());
	if (heap.size() > countOfMax) {
		std::pop_heap(heap.begin(),heap.end(),std::greater<T>());
		heap.pop_back();
	}
}

template <typename T>
void TTopElements<T>::GetCurrentTop(std::vector<T> & top) {
	for (typename std::vector <T>::iterator it=heap.begin();it!=heap.end();++it)
		top.push_back(*it);
			
}


