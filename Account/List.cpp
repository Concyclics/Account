//
//  List.cpp
//  Created by Concyclics
//  List template, Queue and Stack based on List
//

#include "List.hpp"

template <class T>
list_node<T>::list_node()
{
    pre=NULL;
    next=NULL;
}

template <class T>
List<T>::List()
{
    connectNode=new list_node<T>;
    connectNode->next=connectNode;
    connectNode->pre=connectNode;
    list_len=0;
}

template <class T>
void List<T>::pushBack(T data)
{
    list_node<T>* thisNode=new list_node<T>;
    thisNode->pre=connectNode->pre;
    connectNode->pre->next=thisNode;
    thisNode->next=connectNode;
    connectNode->pre=thisNode;
    thisNode->data=data;
    list_len++;
    return;
}

template <class T>
void List<T>::pushFront(T data)
{
    list_node<T>* thisNode=new list_node<T>;
    thisNode->next=connectNode->next;
    connectNode->next->pre=thisNode;
    thisNode->pre=connectNode;
    connectNode->next=thisNode;
    thisNode->data=data;
    list_len++;
    return;
}

template <class T>
void List<T>::pushCmp(T data,bool(*cmp)(T,T))
{
    if(size()==0)
    {
        pushFront(data);
        return;
    }
    list_node<T>* thisNode=new list_node<T>;
    thisNode->data=data;
    
    for(list_node<T>* i=begin();i!=end();i=i->next)
    {
        if(cmp(data,i->data))
        {
            thisNode->next=i;
            thisNode->pre=i->pre;
            i->pre->next=thisNode;
            i->pre=thisNode;
            list_len++;
            return;
        }
    }
    
    thisNode->pre=connectNode->pre;
    connectNode->pre->next=thisNode;
    thisNode->next=connectNode;
    connectNode->pre=thisNode;
    list_len++;
    return;
}

template <class T>
list_node<T>* List<T>::begin() const
{
    return connectNode->next;
}

template <class T>
list_node<T>* List<T>::end() const
{
    return connectNode;
}

template <class T>
int List<T>::size() const
{
    return list_len;
}


template <class T>
bool List<T>::empty() const
{
    return this->begin()==this->end();
}

template <class T>
bool List<T>::del(list_node<T>* node)
{
    if(node==connectNode)return 1;
    node->pre->next=node->next;
    node->next->pre=node->pre;
    delete node;
    list_len--;
    return 0;
}

template <class T>
bool List<T>::swapNode(list_node<T>* a,list_node<T>* b)
{
    if(a==connectNode||b==connectNode)return 1;
    T data=a->data;
    a->data=b->data;
    b->data=data;
    return 0;
}

template <class T>
list_node<T>* List<T>::partition(list_node<T>* left,list_node<T>* right,bool(*cmp)(T,T))
{
    list_node<T>* slow=left;
    list_node<T>* fast=left->next;
    T val=left->data;
    while (fast!=right)
    {
        if (cmp(fast->data,val))
        {
            slow=slow->next;
            swapNode(slow,fast);
        }
        fast=fast->next;
    }
    swapNode(left,slow);
    return slow;
}

template <class T>
void List<T>::listSort(list_node<T>* left,list_node<T>* right,bool(*cmp)(T,T))
{
    if (left!=right)
    {
        list_node<T>* tmp=partition(left,right,cmp);
        listSort(left,tmp,cmp);
        listSort(tmp->next,right,cmp);
    }
}
// define of List class

template <class T>
Queue<T>::Queue()
:List<T>()
{
    
}

template <class T>
void Queue<T>::push(T data)
{
    List<T>::pushBack(data);
}
template <class T>
void Queue<T>::pop()
{
    if(!List<T>::empty())
    {
        List<T>::del(List<T>::begin());
    }
}
template <class T>
T Queue<T>::front()
{
    if(!List<T>::empty())
    {
        return List<T>::begin()->data;
    }
    else
    {
        throw "empty queue!\n";
        //return T();
    }
}
template <class T>
T Queue<T>::back()
{
    if(!List<T>::empty())
    {
        return List<T>::end()->pre->data;
    }
    else
    {
        throw "empty queue!\n";
        //return T();
    }
}
// define of Queue from List

template <class T>
Stack<T>::Stack()
:List<T>()
{
    
}

template <class T>
void Stack<T>::push(T data)
{
    List<T>::pushFront(data);
}
template <class T>
void Stack<T>::pop()
{
    if(!List<T>::empty())
    {
        List<T>::del(List<T>::begin());
    }
}
template <class T>
T Stack<T>::top()
{
    if(!List<T>::empty())
    {
        return List<T>::begin()->data;
    }
    else
    {
        throw "empty stack!\n";
        //return T();
    }
}
// define of Stack from List


// Thanks for downloading, hoping these codes can help you
// Concyclics 20201015
