#include <vector>

template <class T>
class KHeap {
private:
    int k;
    std::vector<T> heap;
    void sift_up();
    void sift_down();
public:
    KHeap(int k): k(k) {}
    void push(const T &pushed_el);
    void pop();
    T    getMin();
};

template <class T>
void KHeap<T>::sift_up() {
    int ind=heap.size()-1;
    while(ind!=0) {
        int parent = (ind - 1) / k;
        if (heap[ind] < heap[parent]) {
            std::swap(heap[ind], heap[parent]);
            ind=parent;
        }
        else {
            return;
        }
    }
}

template <class T>
void KHeap<T>::sift_down() {
    int parent=0;
    int child=parent;
    while(true) {
        for (int i = 1; (i <= k)&&(parent*k + i < heap.size()); ++i)
            if  (heap[child] > heap[parent*k + i]) {
                child = parent*k + i;
            }
        if (child != parent) {
            std::swap(heap[child], heap[parent]);
            parent=child;
        }
        else {
            return;
        }
    }

}
template <class T>
void KHeap<T>::push(const T &pushed_el) {
    heap.push_back(pushed_el);
    sift_up();
}

template <class T>
void KHeap<T>::pop() {
    heap.front()=heap.back();
    heap.pop_back();
    sift_down();
}
template <class T>
T KHeap<T>::getMin() {
    return heap.front();
}
