#ifndef QUEUESLL_H
#define QUEUESLL_H
#include "SLL.h"

template<class T>
class QueueSLL{
    SLL<T> list;
public:
    void enqueue(T elem){
        list.addtoTail(elem);
    };

    T dequeue(){
        T temp = list.getValueAtHead();
        list.removeFromHead();
        return temp;
    };

    T front(){
        return list.getValueAtHead();
    }

    bool isEmpty(){
        return(list.isEmpty());
    }

    void clear(){
        list.clear();
    }
};

#endif