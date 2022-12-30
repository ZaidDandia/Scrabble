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
        Node *next;  //Pointer for next node of the linked list
    };
    Node *head;    //Pointer to the starting node of the list


public:
    //Initially set the empty list parameters
    LinkedList()          //Counstructor
    {
        head = NULL;
    }
    void Insert(T Value)                  //Function to insert nodes in a list
    {
        Node *newPtr = new Node;          //Create new node to be added
        if(head == NULL)                  //If initially the list is empty
        {
            newPtr->value = Value;         //Assign a value
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
        temp->next = newPtr;              //Temp next pointer is updated as new node
        return;
    } 
    T DeleteFront()              //Function to delete from the front of linked list
    {
        Node *temp = head;
        T val = temp->value;
        head = head->next;
        delete temp;
        return val;
    }
    bool search(T Value)      //Funtion to search value in a linked list
    {
        Node *temp = head;
        while(temp != NULL)
        {
            if(temp->value == Value)       //When head node value becomes equal to the value to search
            {
                return true;          //Value is found
            }
            temp = temp->next;
        }
        return false;         //Value is NOT found
    }
    }
    void Delete(T value)     //Function to delete a node from list
    {
        Node *temp = head;
        while(temp != NULL)
        {
            if(head->value == value)       //Value to delete is at head
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
    Node searchNode(T Value)        //Searching the value of node
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
    void Display()        //Displaying linked list nodes
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
