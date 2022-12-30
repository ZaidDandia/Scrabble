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
    Node *front, *rear;    //Pointer declaraction
public:
    //Initially set the empty Queue Parameters
    Queue()                       //Constructor
    {
        front = rear = NULL;
    }
    //Function to add data to the Queue
    void enQueue(T Value)
    {
        if(front == NULL)    //If the Queue is Empty
        {
            Node *tempPtr = new Node;   //Create a new node to be added 
            tempPtr->value = Value;     //Assigns a value
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
    //Function to remove data from the Queue
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
            l++;      //Keeps on incrementing the length while Queue is not Empty
            temp = temp->next;
        }
        return l;
    }
     //Function to display the Queue
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
     //Funtion to find if the Queue is Empty  or NOT
    bool isEmpty()
    {
        if(front == NULL) //The Queue is Empty
        {
            return true;
        }
        else
            return false;
    }
};
