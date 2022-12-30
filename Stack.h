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
    Node *top;     //Pointer to the top element of a stack

public:
    //Initially set the empty stack parameters
    Stack()                          //Counstructor
    {
        top = NULL;
    }
    //Function to insert data into stack
    void insert(T Value)
    {
        Node *newPtr = new Node;
        newPtr->data = Value;
        newPtr->next = NULL;
        if(top == NULL)    //If the stack is empty
        {
            // newPtr->next = NULL;
            top = newPtr;
            return;
        }
        newPtr->next = top;
        // top->next  = NULL;
        top = newPtr;
    }
    //Function to remove data from top of the stack
    void pop()
    {
        top = top->next;
    }
    T getTop()
    {
        return top->data;
    }
    //Function to display   stack
    void Display()
    {
        Node *temp = top;
        while(temp != NULL)
        {
            // temp->data.display();
            // cout << temp->data<<endl;
            temp =temp->next;
        }
    }
};
