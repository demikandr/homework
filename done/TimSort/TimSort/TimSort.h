#include <algorithm>
#include <vector>
//~ #include <assert.h>


template <typename T, typename Iterator, typename Compare>
class TimSort {
private:
    typedef std::vector < std::pair < Iterator, Iterator > > RunType;
    RunType run;
    std::vector < std::pair<Iterator, int> > stack;
    bool _orderedStack();
    void _pushStack(const std::pair<Iterator, int> pushedRun, Compare comp);
    void _insertionSort(const Iterator beginIt, const Iterator endIt, Compare comp);
	int  _getMinrun(const int sizeOfVectror);
	void _breakAndSort(const Iterator beginIt, const Iterator endIt, const int minrun, Compare comp);
	void _mergePair(int indexOfRun, Compare comp);
	void _mergeAll(Compare comp);
    void _forceMerge(Compare comp);
    void _findDownRun(const Iterator beginIt, const Iterator endIt, const int minrun, Iterator &loopIt, RunType &run, Compare comp);
    void _findUpRun(const Iterator beginIt, const Iterator endIt, const int minrun, Iterator &loopIt, RunType &run, Compare comp);
	void _findAndPushRun(const Iterator beginIt, const Iterator endIt, const int minrun, Iterator &loopIt, RunType &run, Compare comp);
public:
	TimSort(const Iterator beginIterator, const Iterator endIterator, Compare comp);
	//TimSort(const Iterator beginIterator, const Iterator endIterator);
} ;

template <typename T, typename Iterator, typename Compare>
TimSort<T,Iterator, Compare>::TimSort(const Iterator beginIt, const Iterator endIt, Compare comp) {
	if (endIt-beginIt<=1)
		return;
	_breakAndSort(beginIt,endIt,_getMinrun(endIt-beginIt), comp);
	_mergeAll(comp);
}

template <typename T, typename Iterator, typename Compare>
int TimSort<T,Iterator, Compare>::_getMinrun(const int sizeOfVector) {
	return 64;
}
/*int TimSort<T,Iterator, Compare>::_getMinrun(const int sizeOfVector) {
    int r = 0, n=sizeOfVector;
	while(n >= 64) {
		r |= (n & 1);
		n >>= 1;
	}
	return n + r;
}*/

template <typename T, typename Iterator, typename Compare>
void TimSort<T,Iterator, Compare>::_mergePair(const int firstRun, Compare comp) {
    //~ assert(stack.size()>1);
    const int secondRun =   firstRun+1;
    Iterator firstIt    =   stack[firstRun].first;
    Iterator firstEndIt =   stack[firstRun].first+stack[firstRun].second;
    Iterator secondIt   =   stack[secondRun].first;
    Iterator secondEndIt=   stack[secondRun].first+stack[secondRun].second;
    std::vector<T>  mergeResult;
    //~ assert(secondIt==firstEndIt);
    while ( (firstIt != firstEndIt) && (secondIt != secondEndIt) ) {
        if (comp(*secondIt, *firstIt)) {
            mergeResult.push_back(*secondIt);
            ++secondIt;
        }
        else {
            mergeResult.push_back(*firstIt);
            ++firstIt;
        }
    }

    //~ assert(firstIt<=firstEndIt);
    while (firstIt != firstEndIt) {
        mergeResult.push_back(*firstIt);
        ++firstIt;
    }
    while (secondIt != secondEndIt) {
        mergeResult.push_back(*secondIt);
        ++secondIt;
    }
    for (int i = 0; i < (int) mergeResult.size(); ++i) {
        *(stack[firstRun].first+i)=mergeResult[i];
    }
    //~ assert((int)mergeResult.size()==stack[firstRun].second+stack[secondRun].second);
    stack[firstRun].second=mergeResult.size();
    //~ assert(stack[firstRun].first+stack[firstRun].second==/stack[secondRun].first+stack[secondRun].second);


    //assert(std::is_sorted(mergeResult.begin(),mergeResult.end()));
    //assert(std::is_sorted(firstIt,secondEndIt));
    //assert(false);
}
template<typename T, typename Iterator, typename  Compare>
bool TimSort<T,Iterator, Compare>::_orderedStack() {
    if (stack.size() == 1)
        return true;
    if (stack[stack.size()-1].second < stack[stack.size()-2].second) {
        if (stack.size()==2)
            return true;
        if (stack[stack.size()-2].second + stack[stack.size()-1].second < stack[stack.size() - 3].second) {
            return true;
        }
    }
    return false;
}
template <typename T, typename Iterator, typename Compare>//DONE
void TimSort<T,Iterator, Compare>::_pushStack(std::pair <Iterator, int> pushedRun, Compare comp) {
    stack.push_back(pushedRun);
	while (!_orderedStack()) {
        int lastInd=(int) stack.size() - 1;
		if ( ( stack.size() > 2 ) && (stack[lastInd].second > stack[lastInd - 2].second ) ) {
			_mergePair(lastInd - 2, comp);
			stack[lastInd - 1] = stack[lastInd];
			stack.pop_back();
		}
		else {
			_mergePair(lastInd - 1, comp);
			stack.pop_back();	
		}
	}
}

template <typename T, typename Iterator, typename Compare>
void TimSort<T,Iterator, Compare>::_forceMerge(Compare comp) {
    //assert(false==true);
	for (int i = (int) stack.size()-2; i>=0; --i) {
		_mergePair(i, comp);

	}
}

template <typename T, typename Iterator, typename Compare>
void TimSort <T, Iterator, Compare>::_mergeAll(Compare comp) {
	if (run.size() == 1)
		return;

	for ( int i = 0 ; i < (int) run.size() ; ++i ) {
		_pushStack( std::make_pair( run[i].first , run[i].second - run[i].first ), comp );
	}
	_forceMerge(comp);
}

template <typename T, typename Iterator, typename Compare> //DONE
void TimSort<T,Iterator, Compare>::_insertionSort(const Iterator beginIt, const Iterator endIt, Compare comp) {
	if ( ( endIt - beginIt ) < 2 )
		return;
	for ( Iterator it= beginIt+1; it != endIt; ++it) {
        Iterator siftIt=it;
		while  ( ( siftIt != beginIt ) && comp( *(siftIt) , *(siftIt-1) ) ) {
			std::swap( *siftIt, *( siftIt - 1 ) );
			--siftIt;
		}
	}
}

template <typename T, typename Iterator, typename Compare>
void TimSort <T, Iterator, Compare>::_findDownRun(const Iterator beginIt, const Iterator endIt, const int minrun, Iterator &loopIt, RunType &run, Compare comp) {
    while ( ( loopIt != endIt ) && ( !comp(*(loopIt-1), *(loopIt) ) ) ) {
            ++loopIt;
    }
    std::reverse(beginIt,loopIt);
    if ( ( loopIt - beginIt < minrun)  && ( loopIt != endIt ) ) {
        Iterator endOfRunIt = (  endIt - beginIt < minrun  ) ? endIt : beginIt + minrun ;
        _insertionSort(beginIt, endOfRunIt, comp);
        loopIt = endOfRunIt;
    }
    run.push_back( std::make_pair(beginIt, loopIt) );
}
template <typename T, typename Iterator, typename Compare>
void TimSort <T, Iterator, Compare>::_findUpRun(const Iterator beginIt, const Iterator endIt, const int minrun, Iterator &loopIt, RunType &run, Compare comp) {

    while (( loopIt != endIt ) && (!comp(*(loopIt), *(loopIt-1) ) ) ) {
            ++loopIt;
    }
    if ( ( loopIt - beginIt < minrun)  && ( loopIt != endIt ) ) {
        Iterator endOfRunIt = (  endIt - beginIt < minrun  ) ? endIt : beginIt + minrun ;
        _insertionSort(beginIt, endOfRunIt, comp);
        loopIt = endOfRunIt;
    }
    run.push_back( std::make_pair(beginIt, loopIt) );
}
template <typename T, typename Iterator, typename Compare> //DONE
void TimSort <T, Iterator, Compare>::_findAndPushRun(const Iterator beginIt, const Iterator endIt, const int minrun, Iterator &loopIt, RunType &run, Compare comp) {
    loopIt++;
    if (loopIt==endIt) {
        run.push_back( std::make_pair(beginIt, loopIt) );
        return;
    }
	if ( comp( *loopIt, *beginIt ) ) {
		_findDownRun(beginIt, endIt, minrun, loopIt, run, comp);
	}
    else {
        _findUpRun(beginIt, endIt, minrun, loopIt, run, comp);
    }
}

template <typename T, typename Iterator, typename Compare> //DONE
void TimSort <T, Iterator, Compare>::_breakAndSort(const Iterator beginIt, const Iterator endIt, const int minrun, Compare comp) {
	Iterator loopIt = beginIt;
	while ( loopIt != endIt ) {
		_findAndPushRun( loopIt, endIt, minrun, loopIt, run, comp );
	}
}

