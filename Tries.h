#pragma once
#include<iostream>
#include<fstream>
using namespace std;

const int SIZE = 27; // no of node in a tires 

class Trie
{
private:
    struct Tries
    {
        bool EndOfWord;// bool to identifiy end of word 
        Tries *child[SIZE];
    };

    Tries *root;

    void insert(Tries *root, string key) // this a function to insert a char  or any data type for that matter into a trie 
    {                                   // it will take a tring then break it down to store it in the trie character by character
        Tries *temp = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'A';
            if (!temp->child[index])
                temp->child[index] = getNode();

            temp = temp->child[index];
        }
        temp->EndOfWord = true; // our bool true so that we can mark our end of our acceptable word
        return;
    }

    bool searchTrie(struct Tries *root, string key) // function to search our key in the tries
    {
        Tries *temp = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'A';
            if (!temp->child[index]) // if word is not there it returns false 
                return false;

            temp = temp->child[index];
        }

        return (temp->EndOfWord); // if word does not exist then the falsee is returned other wise true 
    }

public:
    Trie()
    {
        root = getNode();
    }

    Tries *getNode() // it initailizes the bnjode for the user to manipulate it afterwards or use it a root 
    {
        Tries *pNode = new Tries;

        pNode->EndOfWord = false;

        for (int i = 0; i < SIZE; i++)
            pNode->child[i] = NULL;

        return pNode;
    }

    bool searchString(string word) // runns the code for finding a word 
    {
        return searchTrie(root, word);
    }

    void initialise()
    {
        fstream readfile;
        readfile.open("Words.txt", ios::in);

        while (!readfile.eof()) // it reads the file of all acceptable words or any file if  strings and readss it till end of the file and store 
        {                       // in the tries 
            string temp;
            readfile >> temp;
            insert(root, temp);
        }
        return;
    }
    void Insert(string word) // to insert a single string in the tries 
    {
        insert(root, word);
    }
    void check() // it is to check if the word , string exists in the trie 
    {
        int found = 0;
        ifstream readfile;
        readfile.open("Words.txt");

        while (!readfile.eof())
        {
            string temp;
            readfile >> temp;
            if (searchTrie(root, temp))
                found++;
            else
                cout << temp << " not found\n";
        }
        cout << found;
        return;
    }
};