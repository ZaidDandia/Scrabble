#pragma once

#include<iostream>
using namespace std;
template<typename T>
class Stack
{
private:
    struct Node {
        T data;
        Node *next;
    };
    Node *top;

public:
    Stack()
    {
        top = NULL;
    }
    void insert(T Value)
    {
        Node *newPtr = new Node;
        newPtr->data = Value;
        if(top == NULL)
        {
            newPtr->next = NULL;
            top = newPtr;
        }
        newPtr->next = top;
        top = newPtr;
    }
    void pop()
    {
        top = top->next;
    }
    T getTop()
    {
        return top->data;
    }
};