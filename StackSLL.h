#ifndef STACKSLL_H
#define STACKSLL_H
#include "SLL.h"

template<class T>
class StackSLL{
    SLL<T> list;
public:
    StackSLL(){};

    void push(T elem){
        list.addtoHead(elem);
    }

    T pop(){
        T temp = list.getValueAtHead();
        list.removeFromHead();
        return temp;
    }

    T top(){
        return list.getValueAtHead();
    }

    bool isEmpty(){
        return (list.isEmpty());
    }

    void clear(){
        list.clear();
    }

};

#endif