#pragma once
#include<iostream>
#include<fstream>
using namespace std;

const int SIZE = 27;

class Trie
{
private:
    struct Tries
    {
        bool EndOfWord;
        Tries *child[SIZE];
    };

    Tries *root;

    void insert(Tries *root, string key)
    {
        Tries *temp = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'A';
            if (!temp->child[index])
                temp->child[index] = getNode();

            temp = temp->child[index];
        }
        temp->EndOfWord = true;
        return;
    }

    bool searchTrie(struct Tries *root, string key)
    {
        Tries *temp = root;

        for (int i = 0; i < key.length(); i++)
        {
            int index = key[i] - 'A';
            if (!temp->child[index])
                return false;

            temp = temp->child[index];
        }

        return (temp->EndOfWord);
    }

public:
    Trie()
    {
        root = getNode();
    }

    Tries *getNode()
    {
        Tries *pNode = new Tries;

        pNode->EndOfWord = false;

        for (int i = 0; i < SIZE; i++)
            pNode->child[i] = NULL;

        return pNode;
    }

    bool searchString(string word)
    {
        return searchTrie(root, word);
    }

    void initialise()
    {
        fstream readfile;
        readfile.open("Words.txt", ios::in);

        while (!readfile.eof())
        {
            string temp;
            readfile >> temp;
            insert(root, temp);
        }
        return;
    }

    void check()
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