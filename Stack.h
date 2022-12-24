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
        newPtr->next = NULL;
        if(top == NULL)
        {
            // newPtr->next = NULL;
            top = newPtr;
            return;
        }
        newPtr->next = top;
        // top->next  = NULL;
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
    void Display()
    {
        Node *temp = top;
        while(temp != NULL)
        {
            temp->data.display();
            // cout << temp->data<<endl;
            temp = temp->next;
        }
    }
};