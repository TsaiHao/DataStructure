#ifndef MYVECTOR_H
#define MYVECTOR_H

#include <utility>
#include <random>
#include <exception>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <memory>

typedef int Rank;
const int DEFAULT_CAPACITY = 10;

template <typename T>
class myVector{
private:
    Rank _size;
    int _capacity;
    T* _elem = nullptr;

protected:
    void copy_from(T* A, int lo, int hi);     //
    void expand();      //
    void shrink();      //
    void bubbleSort(Rank lo = 0, Rank hi = -1);      //bubble sort from lo to hi
    void merge(Rank lo, Rank mi, Rank hi);
    void mergeSort(Rank lo, Rank hi);       //merge sort form lo to hi
    //Rank partition(Rank lo, Rank hi);
    void quickSort(Rank lo, Rank hi);
    //void heapSort(Rank lo, Rank hi);

public:
    myVector(int c = DEFAULT_CAPACITY): _size(0), _elem(new T[c]), _capacity(c) {}
    myVector(T* A, Rank lo, Rank hi) { copy_from(A, lo, hi); }
    myVector(T* A, Rank n) { copy_from(A, 0, n); }
    myVector(const myVector<T>& V, Rank hi, Rank lo = 0) { copy_from(V._elem, lo, hi); }
    myVector(const myVector<T>& V) { copy_from(V._elem, 0, V._size); }
    myVector(std::istream&);
    ~myVector() { delete[] _elem; }

    Rank size() const { return _size; } //
    bool empty() const { return _size <=0 || _elem == nullptr; }    //
    int disordered();   //
    Rank find(const T& e) const { return find(e, 0, static_cast<Rank>(_size)); }    //
    Rank find(const T& e, Rank lo, Rank hi) const;  //
    Rank search(const T& e) const {return empty() ? -1 : search(e, static_cast<Rank>(0), static_cast<Rank>(_size)); }
    Rank search(const T& e, Rank lo, Rank hi, int method = 0) const;
    Rank regularSearch(const T& e, Rank lo, Rank hi) const;
    Rank binarySearch(const T& e, Rank lo, Rank hi) const;
    T& operator[](Rank r) const;    //
    myVector<T> & operator=(const myVector<T> &);   //
    T remove(Rank r);   //
    int remove(Rank lo, Rank hi);   //
    Rank insert(Rank r, const T& e);    //
    Rank insert(const T& e) { return insert(_size, e); }    //
    void sort(Rank lo, Rank hi, int method = 0);
    void sort() { return sort(0, _size); }
    void unsort(Rank lo, Rank hi);  //
    void unsort() { unsort(0, _size); }
    int deduplicate();  //
    void savetxt(std::ostream&);
    //int uniquify();
    void traverse(void (*)(T&));
    template <typename VST> void traverse(VST&);
};

// protected:
template <typename T>
void myVector<T>::copy_from(T* A, int lo, int hi)
{
    if(_capacity < 2*(hi - lo))
        _capacity = 2 * (hi - lo);
    _elem = new T[_capacity];
    _size = 0;
    while(lo < hi)
        _elem[_size++] = A[lo++];
}

template <typename T>
void myVector<T>::expand()
{
    if (_size < _capacity)
        return;
    while (_capacity < 2*_size)
        _capacity <<= 1;
    T* oldElem = _elem;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; ++i)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template <typename T>
void myVector<T>::shrink()
{
    if (_size > (_capacity >> 2))
        return;
    _capacity = (_capacity/2 > DEFAULT_CAPACITY) ? (_capacity/2) : DEFAULT_CAPACITY;
    T* oldElem = _elem;
    _elem = new T[_capacity];
    for (int i = 0; i < _size; ++i)
        _elem[i] = oldElem[i];
    delete[] oldElem;
}

template <typename T>
void myVector<T>::bubbleSort(Rank lo, Rank hi)
{
    hi = (hi == -1) ? _size : hi;
    if (hi < 0 || lo < 0 || hi < lo)
        throw std::invalid_argument("bad argument");
    for (int i = lo; i < hi; ++i)
        for (int j = hi-1; j > lo; --j)
            if (_elem[j] < _elem[j-1])
                std::swap(_elem[j], _elem[j-1]);
}

template <typename T>
void myVector<T>::merge(Rank lo, Rank mi, Rank hi)
{
    Rank r1 = lo, r2 = mi;
    T* temp = new T[hi - lo];
    Rank now = 0;

    while (r1 < mi && r2 < hi) {
        temp[now++] = (_elem[r1] > _elem[r2]) ? _elem[r2++] : _elem[r1++];
    }
    while (r1 < mi)
        temp[now++] = _elem[r1++];
    while (r2 < hi)
        temp[now++] = _elem[r2++];
    for (int i = 0; i < hi - lo; ++i)
        _elem[lo + i] = temp[i];
}

template <typename T>
void myVector<T>::mergeSort(Rank lo, Rank hi)
{
    if (lo == hi - 1 || lo == hi)
        return;
    Rank mi = static_cast<Rank>((hi + lo) / 2);
    mergeSort(lo, mi);
    mergeSort(mi, hi);

    merge(lo, mi, hi);
}

template <typename T>
void myVector<T>::quickSort(Rank lo, Rank hi)
{
    if (hi - lo < 2)
        return;
    Rank lowRank = lo, highRank = hi;
    T pivot = _elem[hi - 1];
    for (; lowRank < highRank; ++lowRank) {
        if (_elem[lowRank] > pivot)
            for (; highRank > lowRank; --highRank) {
                if (_elem[highRank] <= pivot){
                    std::swap(_elem[highRank], _elem[lowRank]);
                    break;
                }
            }
    }
    Rank md = static_cast<Rank>((lo + hi) >> 1);
    quickSort(lo, md);
    quickSort(md, hi);
}
// public:
template <typename T>
myVector<T>::myVector(std::istream& ifs)
{
    if (_elem != nullptr)
        delete[] _elem;
    _capacity = DEFAULT_CAPACITY;
    _elem = new T[_capacity];
    _size = 0;
    T ele;
    Rank r = 0;
    while(ifs >> ele){
        _elem[r] = ele;
        _size++;
        r++;
        if (_size > (_capacity >> 1))
            expand();
    }
}

template <typename T>
int myVector<T>::disordered()
{
    int n = 0;
    for (int i = 0; i < _size; ++i)
        if (_elem[i] > _elem[i+1])
            n++;
    return n;
}

template <typename T>
Rank myVector<T>::find(const T& e, Rank lo, Rank hi) const
{
    for(int i = hi - 1; i > lo; --i)
    {
        if (_elem[i] == e)
            return static_cast<Rank>(i);
    }
    return -1;
}

template <typename T>
inline Rank myVector<T>::regularSearch(const T&e, Rank lo, Rank hi) const
{
    for (int i = lo; i < hi; ++i)
        if (_elem[i] == e) {
            return i;
        }
    return -1;
}

template <typename T>
Rank myVector<T>::binarySearch(const T& e, Rank lo, Rank hi) const
{
    Rank md;
    while(true){
        md = static_cast<Rank>((lo + hi) / 2);
        if (_elem[md] == e)
            return md;
        if (lo == hi || lo == hi-1)
            return -1;
        (_elem[md] < e) ? (lo = md) : (hi = md);
    }
}
template <typename T>
Rank myVector<T>::search(const T&e, Rank lo, Rank hi, int method) const
{
    switch (method) {
    case 0:
        regularSearch(e, lo, hi);
        break;

    }
}

template <typename T>
T& myVector<T>::operator[](Rank r) const
{
    return (r < 0) ? _elem[_size + r] : _elem[r];
}

template<typename T>
myVector<T>& myVector<T>::operator=(const myVector<T> &V)
{
    int s = V.size();
    if (_size < s)
        _capacity = 2 * s;
    if (!this->empty())
        delete[] _elem;
    _size = 0;
    copy_from(V._elem, 0, s);
}

template <typename T>
T myVector<T>::remove(Rank r)
{
    if (r >= _size)
        throw std::range_error("out of range");
    T e = _elem[r];
    for (Rank i = r; i < _size; ++i)
        _elem[i] = _elem[i+1];
    _size--;
    shrink();
    return e;
}

template <typename T>
int myVector<T>::remove(Rank lo, Rank hi)
{
    if(lo < 0 || hi > _size || lo > hi)
        throw std::invalid_argument("bad argument");
    Rank span = hi - lo;
    for (int i = lo; i + span < _size; ++i)
        _elem[i] = _elem[i + span];
    _size -= span;
    shrink();
    return span;
}

template <typename T>
Rank myVector<T>::insert(Rank r, const T& e)
{
    expand();

    T* bg = _elem + r;
    for(Rank i = _size; i > r; --i)
        _elem[i] = _elem[i-1];
    _elem[r] = e;
    _size++;
    return r;
}

template <typename T>
void myVector<T>::sort(Rank lo, Rank hi, int method)
{
    switch (method) {
    case 0:
        bubbleSort(lo, hi);
        break;
    case 1:
        mergeSort(lo, hi);
    case 2:
        quickSort(lo, hi);
    }
}

template <typename T>
void myVector<T>::unsort(Rank lo, Rank hi)
{
    T* V = _elem + lo;
    for (int i = hi - 1; i > lo; --i)
        std::swap(V[i], V[std::rand() * i]);
}

template <typename T>
int myVector<T>::deduplicate()
{
    int oldSize = _size;
    for (int i = 0; i < _size;)
        (find(_elem[i], 0, i) < 0) ? i++ : remove(find(_elem[i], 0, i));
    return oldSize - _size;
}

template <typename T>
void myVector<T>::savetxt(std::ostream& ofs)
{
    for (Rank i =0; i < _size; ++i)
        ofs << _elem[i] << std::endl;
}
template <typename T>
void myVector<T>::traverse(void (*visit)(T&))
{
    for(int i = 0; i < _size; ++i)
        visit(_elem[i]);
}

template <typename T>
template <typename VST>
void myVector<T>::traverse(VST& visit)
{
    for(int i = 0; i < _size; ++i)
        visit(_elem[i]);
}

//non-member
template <typename T>
void permute(myVector<T> V)
{
    for (int i = V.size() - 1; i > 0; --i)
        std::swap(V[i], V[std::rand()%i]);
}


#endif // MYVECTOR_H
