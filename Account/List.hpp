//
//  List.hpp
//  Created by Concyclics
//  List template, Queue and Stack based on List
//
#ifndef List_hpp
#define List_hpp

#include <stdio.h>
#include <iostream>
#include <string>


template <class T>
class list_node
{
public:
    list_node();
    list_node* pre;
    list_node* next;
    T data;
};


template <class T>
class List
{
private:
    list_node<T>* connectNode;
    int list_len;
    
public:
    
    List();
    
    void pushBack(T data);
    void pushFront(T data);
    void pushCmp(T data,bool(*cmp)(T,T));
    bool swapNode(list_node<T>*,list_node<T>*);
    bool del(list_node<T>*);
    list_node<T>* partition(list_node<T>*,list_node<T>*,bool(*cmp)(T,T));
    void listSort(list_node<T>*,list_node<T>*,bool(*cmp)(T,T));
    
    list_node<T>* begin() const;
    list_node<T>* end() const;
    
    int size() const;
    bool empty() const;
    
    
};

template <class T>
class Queue: public List<T>
{
    public:
        Queue();
    
        void push(T data);
        void pop();
    
        T front();
        T back();
    
};

template <class T>
class Stack: public List<T>
{
    public:
        Stack();
    
        void push(T data);
        void pop();
    
        T top();
    
};
#endif /* List_hpp */

// Thanks for downloading, hoping these codes can help you
// Concyclics 20201015