#include <vector>
#include <algorithm>

template <typename T>
class TTopElements {
private:
	std::vector <T> topElements;
	const int countOfMax;
public:
    TTopElements(const int topSize);
    void Add(const T & elem);
    void GetCurrentTop(std::vector<T> & top);
};

template <typename T>
TTopElements<T>::TTopElements(const int topSize) : countOfMax(topSize) {
}

template <typename T>
void TTopElements<T>::Add(const T & elem) {
	topElements.push_back(elem);
	if (topElements.size()>2*countOfMax) {
		std::nth_element(topElements.begin(),topElements.begin()+countOfMax-1,topElements.end(), std::greater<T>());
		topElements.resize(countOfMax);
	}
}

template <typename T>
void TTopElements<T>::GetCurrentTop(std::vector<T> & top) {
    std::nth_element(topElements.begin(),topElements.begin()+countOfMax-1,topElements.end(), std::greater<T>());
    topElements.resize(countOfMax);
	top=topElements;
}
			
