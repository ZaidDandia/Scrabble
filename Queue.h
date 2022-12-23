#pragma once
#include<iostream>
using namespace std;

template<typename T>
class Queue
{
private:
    struct Node {
        T value;
        Node *next;
    };
    Node *front, *rear;
public:
    Queue()
    {
        front = rear = NULL;
    }
    void enQueue(T Value)
    {
        if(front == NULL)
        {
            Node *tempPtr = new Node;
            tempPtr->value = Value;
            tempPtr->next = NULL;
            front = rear = tempPtr;
            return;
        }
        Node *tempPtr = new Node;
        tempPtr->value = Value;
        Node *temp = front;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = tempPtr;
        rear = tempPtr;
        rear->next = NULL;
        return;
    }
    void deQueue()
    {
        if(front != NULL)
            front = front->next;
    }
    T getFront()
    {
        return front->value;
    }
    int getLength()
    {
        int l = 0;
        Node *temp = front;
        while(temp != NULL)
        {
            l++;
            temp = temp->next;
        }
        return l;
    }
    void Display()
    {
        Node *temp = front;
        while(temp != NULL)
        {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};