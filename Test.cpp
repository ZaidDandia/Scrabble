#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <algorithm>
using namespace std;
#include "Tries.h"
#include "LinkedList.h"
#include "Queue.h"
bool searchWord(Trie t, char arr[15][15])
{
    bool found = false;
    ofstream fOut;
    fOut.open("result.txt");
    t.initialise();

    // horizontal right
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            string temp = "";
            for (int k = j; k < 15; k++)
            {
                temp += arr[i][k];
                if (t.searchString(temp))
                {
                    found = true;
                    fOut << temp << " (" << i + 1 << " , " << j + 1 << ") "
                         << "(" << i + 1 << " , " << k + 1 << ") " << endl;
                }
            }
        }
    }
    return found;
}
int main()
{
    Trie t;
    t.initialise();
    Queue<char> Inventory;
    char array[101] = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'D', 'D', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'F', 'F', 'F', 'G', 'G', 'G', 'H', 'H', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'J', 'K', 'L', 'L', 'L', 'L', 'M', 'M', 'N', 'N', 'N', 'N', 'N', 'N', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'P', 'P', 'Q', 'Q', 'R', 'R', 'R', 'R', 'R', 'R', 'S', 'S', 'S', 'S', 'T', 'T', 'T', 'T', 'T', 'T', 'U', 'U', 'U', 'U', 'V', 'V', 'W', 'W', 'X', 'Y', 'Y', 'Z', 'Z'};
    int Points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    srand(time(0));
    random_shuffle(array, array + 100);
    for (int i = 0; i < 100; i++)
    {
        Inventory.enQueue(array[i]);
    }
    int players;
    cout << "Enter the number of players: ";
    cin >> players;
    while (players > 4 || players <= 1)
    {
        cout << "Please Enter a number between 2 and 4: ";
        cin >> players;
    }
    int Score[players] = {0};
    int *turn;
    int min = 1000;
    int position = 0;
    turn = new int[players];
    for (int i = 0; i < players; i++)
    {
        int temp = rand() % 26;
        turn[i] = temp;
        char c = temp + 97;
        if (turn[i] < min)
        {
            min = turn[i];
            position = i + 1;
        }
    }
    cout << "Player " << position << " plays first" << endl;
    LinkedList<int> l;
    l.Insert(position);
    LinkedList<char> *Words = new LinkedList<char>[players];
    for (int i = 0; i < players; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            Words[i].Insert(Inventory.getFront());
            Inventory.deQueue();
        }
    }
    for (int i = 0; i < players; i++)
    {
        if (i + 1 != position)
            l.Insert(i + 1);
    }
    char Board[15][15];
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            Board[i][j] = ' ';
        }
    }
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            cout << "| " << Board[i][j] << " ";
        }
        cout << "|" << endl;
    }
    while (1)
    {
        Queue<char> CurrentWord;
        char choice = 'Y';
        int CurrentTurn = l.showFront();
        l.DeleteFront();
        l.Insert(CurrentTurn);
        cout << "Player " << CurrentTurn << " turn: " << endl;
        cout << "Your Word Inventory: ";
        Words[CurrentTurn].Display();
        int row, column;
        char c;
        while (1)
        {   
            cout << "Enter row: ";
            cin >> row;
            cout << "Enter Column: ";
            cin >> column;
            cin >> c;
            while (Board[row-1][column-1] != ' ')
            {
                cout << "Already Full. Try again" << endl;
                cout << "Enter row: ";
                cin >> row;
                cout << "Enter column: ";
                cin >> column;
                cout << "Enter the Letter: ";
                cin >> c;
            }
            while (!Words[CurrentTurn].search(c))
            {
                cout << "Letter not in your inventory! Please try again." << endl;
                cout << "Enter the Letter : " << endl;
                cin >> c;
            }
            {
                Board[row - 1][column - 1] = c;
                cout << Board[row-1][column-1] << endl;
                cout << "Do you want Enter again(Y/N): ";
                cin >> choice;
                CurrentWord.enQueue(c);

                if (choice == 'N')
                {
                    if(searchWord(t, Board))
                    {
                        for(int i =0; i<CurrentWord.getLength(); i++)
                        {
                            Words[CurrentTurn].DeleteFront();
                            Words[CurrentTurn].Insert(Inventory.getFront());
                            Inventory.deQueue();
                            int Letter = CurrentWord.getFront() - 'A';
                            Score[CurrentTurn] += Letter;
                            CurrentWord.deQueue();
                        }
                    }
                    else
                    {
                        choice = 'Y';
                        cout << "The word Entered is not in the Dictionary Please try another word."<<endl;
                        for(int i =0; i<CurrentWord.getLength(); i++)
                        {
                            CurrentWord.deQueue();
                        }
                    }
                    break;
                }
                
            }

        }
        cout << Score[CurrentTurn] << endl;
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                cout << "| " << Board[i][j] << " ";
            }
            cout << "|" << endl;
        }
    }
}