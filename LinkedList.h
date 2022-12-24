#pragma once

#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T value;
        Node *next;
    };
    Node *head;

public:
    LinkedList()
    {
        head = NULL;
    }
    void Insert(T Value)
    {
        Node *newPtr = new Node;
        if(head == NULL)
        {
            newPtr->value = Value;
            newPtr->next = NULL;
            head = newPtr;
            return;
        }
        Node *temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        newPtr->value = Value;
        newPtr->next = NULL;
        temp->next = newPtr;
        return;
    }
    T DeleteFront()
    {
        Node *temp = head;
        T val = temp->value;
        head = head->next;
        delete temp;
        return val;
    }
    bool search(T Value)
    {
        Node *temp = head;
        while(temp != NULL)
        {
            if(temp->value == Value)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    void Delete(T value)
    {
        Node *temp = head;
        while(temp != NULL)
        {
            if(head->value == value)
            {
                head = head->next;
                return;
            }
            if(temp->next->value == value)
            {
                temp->next = temp->next->next;
                return;
            }
            temp = temp->next;
        }
    }
    Node searchNode(T Value)
    {
        Node *temp = head;
        while(temp != NULL)
        {
            if(temp->value == Value)
            {
                return temp;
            }
            temp = temp->next;
        }
        return NULL;
    }
    T showFront()
    {
        return head->value;
    }
    void Display()
    {
        Node *temp = head;
        while(temp != NULL)
        {
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
    }

};