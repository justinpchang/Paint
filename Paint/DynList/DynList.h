//
//  DynList.h
//  Paint
//
//  Created by Justin on 6/29/16.
//  Copyright © 2016 Justin Chang. All rights reserved.
//

#ifndef DynList_h
#define DynList_h
#include <cassert>

template <class T>
class DynList {
    T *_arr;
    int _count;
public:
    // default constructor
    explicit DynList<T>(): _count(0) {
        _arr = new T[_count];
    };
    
    // copy constructor
    DynList<T>(const DynList<T> &model): _count(model._count) {
        _arr = new T[_count];
        for(int i = 0; i < model._count; i++) {
            _arr[i] = model._arr[i];
        }
    };
    
    // destructor
    ~DynList<T>() {
        if(_arr != nullptr)
            delete[] _arr;
    };
    
    // returns the number of items in the array
    int getCount() {
        return _count;
    }
    
    // overload assignment operator
    DynList<T>& operator=(const DynList<T>& rh) {
        if(this != &rh) {
            if(_arr != nullptr)
                delete[] _arr;
            _arr = new T[rh._count];
            for(int i = 0; i < rh._count; i++) {
                _arr[i] = rh._arr[i];
            }
            _count = rh._size;
        }
        return *this;
    }
    
    // overload subscript operator for assignment
    T& operator[](int index) {
        assert(index >= 0 && index < _count);
        return _arr[index];
    }
    
    // overload subscript operator for access
    const T& operator[](int index) const {
        assert(index >= 0 && index < _count);
        return _arr[index];
    }
    
    // adds given value to the array
    // if no more space, creates a new array
    void add(T val) {
        _count++;
        T *_arr2(_arr);
        delete[] _arr;
        _arr = new T[_count];
        for(int i = 0; i < _count - 1; i++) {
            _arr[i] = _arr2[i];
        }
        _arr[_count-1] = val;
    }
    
    // removes given value
    void remove(T val) {
        _count--;
        T *_arr2(_arr);
        delete[] _arr;
        _arr = new T[_count];
        int i = 0;
        while(_arr2[i] != val) {
            _arr[i] = _arr2[i];
            i++;
        }
        for(int j = i; j < _count; j++) {
            _arr[i] = _arr2[i-1];
        }
    }
    
    // removes given index
    void remove(int idx) {
        _count--;
        T *_arr2(_arr);
        delete[] _arr;
        _arr = new T[_count];
        int i = 0;
        while(i != idx) {
            _arr[i] = _arr2[i];
            i++;
        }
        for(int j = i; j < _count; j++) {
            _arr[i] = _arr2[i-1];
        }
    }
};

#endif /* DynList_h */
