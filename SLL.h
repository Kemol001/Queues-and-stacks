#ifndef SLL_H
#define SLL_H
#include<iostream>

template<class T>
class Node{
    T info;
    Node* next;
public:
    Node(T _info, Node* _next=0){info=_info ; next=_next ;};
    Node* getNext(){return next;};
    void setNext(Node* _next){next=_next;};
    T getInfo (){return info;};
    void setInfo (T _info){info=_info;};
};

template<class T>
class SLL{
    Node<T> *head, *tail;
public:
    SLL(){head = tail = 0;}

    void addtoHead(T _info){
        Node<T> *node = new Node<T>(_info,head);
        if(head==NULL)
            head=tail=node;
        else head=node;
    };

    void addtoTail(T _info){
        Node<T> *node = new Node<T>(_info);
        if(tail==NULL)
            head=tail=node;
        else{
            tail->setNext(node);
            tail=node;
        }
    };

    void removeFromTail(){
        if(head==tail){
            delete head,tail;
            head=tail=NULL;
        }
        else{
            Node<T> *current=head;
            for(;current->getNext()!=tail;current=current->getNext());
            delete tail;
            tail=current;
            tail->setNext(NULL);
        }
    };

    void removeFromHead(){
        if(head==tail){
            delete head,tail;
            head=tail=NULL;
        }
        else{
            Node<T> *current=head;
            head=head->getNext();
            delete current;
        }
    };

    //a function that returns the value at head without deleting it
    T getValueAtHead(){
        return(head->getInfo());
    };

    bool isEmpty(){
        return(head==tail&&tail==NULL);
    };

    void clear(){
        while(head!=NULL){
            removeFromHead();
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const SLL<T>& obj){
        if (obj.head==NULL) os<<"Empty\n";
        Node<T> *current=obj.head;
        while(current!=NULL){
            os<<current->getInfo();
            current->getNext()!=NULL ? os<<" -> " : os<<"";
            current=current->getNext();
        }
        return os;
    };
};


#endif