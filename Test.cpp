#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <algorithm>
using namespace std;
#include "Tries.h"
#include "LinkedList.h"
#include "Queue.h"
#include "Stack.h"

struct Coordinates
{
    int Row;
    int Column;
};
bool searchWord(Trie t, char arr[15][15], Trie C)
{
    bool found = false;
    bool already = false;
    t.initialise();

    // horizontal right
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            string temp = "";
            for (int k = j; k < 15; k++)
            {
                if (arr[i][k] != ' ')
                    temp += arr[i][k];
                else
                {
                    continue;
                }
                if (t.searchString(temp))
                {
                    if (!C.searchString(temp))
                    {
                        C.Insert(temp);
                        found = true;
                    }
                    else
                    {
                        already = true;
                    }
                }
            }
        }
    }
    for (int j = 0; j < 15; j++)
    {
        for (int i = 0; i < 15; i++)
        {
            string temp = "";
            for (int k = i; k < 15; k++)
            {
                if (arr[k][j] != ' ')
                    temp += arr[k][j];
                else
                {
                    continue;
                }
                if (t.searchString(temp))
                {
                    if (!C.searchString(temp))
                    {
                        found = true;
                    }
                    else
                    {
                        already = true;
                    }
                }
            }
        }
    }
    return found;
}
class Scrabble
{
private:
    Trie t;
    Trie CompletedWords;
    Queue<char> Inventory;
    int players;
    char array[101] = {'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'A', 'B', 'B', 'C', 'C', 'D', 'D', 'D', 'D', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'E', 'F', 'F', 'F', 'G', 'G', 'G', 'H', 'H', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'I', 'J', 'K', 'L', 'L', 'L', 'L', 'M', 'M', 'N', 'N', 'N', 'N', 'N', 'N', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'O', 'P', 'P', 'Q', 'Q', 'R', 'R', 'R', 'R', 'R', 'R', 'S', 'S', 'S', 'S', 'T', 'T', 'T', 'T', 'T', 'T', 'U', 'U', 'U', 'U', 'V', 'V', 'W', 'W', 'X', 'Y', 'Y', 'Z', 'Z'};
    int Points[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    LinkedList<int> l;
    LinkedList<char> *Words = new LinkedList<char>[players];
    char Board[15][15];
    int *Score = new int[players];
    int *turn;
public:
    Scrabble()
    {
        t.initialise();
        srand(time(0));
        random_shuffle(array, array + 100);
        for (int i = 0; i < 100; i++)
        {
            Inventory.enQueue(array[i]);
        }
        cout << "Enter the number of players: ";
        cin >> players;
        while (players > 4 || players <= 1)
        {
            cout << "Please Enter a number between 2 and 4: ";
            cin >> players;
        }
        Score = {0};
        
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
        l.Insert(position);
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

        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                Board[i][j] = ' ';
            }
        }
    }
    void PrintBoard()
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                cout << "| " << Board[i][j] << " ";
            }
            cout << "|" << endl;
        }
    }
    void playGame()
    {
        while (1)
        {
            Queue<char> CurrentWord;
            char choice = 'Y';
            int CurrentTurn = l.showFront();
            l.DeleteFront();
            l.Insert(CurrentTurn);
            cout << "Player " << CurrentTurn << " turn: " << endl;
            cout << "Your Word Inventory: ";
            Words[CurrentTurn - 1].Display();
            int row, column;
            char c;
            Stack<Coordinates> Stored;
            while (1)
            {
                cout << "Enter row: ";
                cin >> row;
                cout << "Enter Column: ";
                cin >> column;
                cin >> c;

                while (Board[row - 1][column - 1] != ' ')
                {
                    cout << "Already Full. Try again" << endl;
                    cout << "Enter row: ";
                    cin >> row;
                    cout << "Enter column: ";
                    cin >> column;
                    cout << "Enter the Letter: ";
                    cin >> c;
                }
                while (!Words[CurrentTurn - 1].search(c))
                {
                    cout << "Letter not in your inventory! Please try again." << endl;
                    cout << "Enter the Letter : " << endl;
                    cin >> c;
                }
                {
                    Coordinates C;
                    C.Row = row - 1;
                    C.Column = column - 1;
                    Stored.insert(C);
                    CurrentWord.enQueue(c);
                    Board[row - 1][column - 1] = c;
                    cout << "Do you want Enter again(Y/N): ";
                    cin >> choice;

                    if (choice == 'N')
                    {
                        if (searchWord(t, Board, CompletedWords))
                        {
                            int temp1 = CurrentWord.getLength();
                            for (int i = 0; i < temp1; i++)
                            {
                                Words[CurrentTurn - 1].Delete(CurrentWord.getFront());
                                Words[CurrentTurn - 1].Insert(Inventory.getFront());
                                Inventory.deQueue();
                                int Letter = Points[int(CurrentWord.getFront() - 'A')];
                                Score[CurrentTurn - 1] += Letter;
                                CurrentWord.deQueue();
                            }
                            break;
                        }
                        else
                        {
                            choice = 'Y';
                            cout << "The word Entered is not in the Dictionary Please try another word." << endl;
                            int temp1 = CurrentWord.getLength();
                            Stored.Display();
                            for (int i = 0; i < temp1; i++)
                            {
                                Coordinates temp = Stored.getTop();
                                Stored.pop();
                                Board[temp.Row][temp.Column] = ' ';
                                CurrentWord.deQueue();
                            }
                            PrintBoard();
                        }
                    }
                }
            }
            cout <<"Score: "<<Score[CurrentTurn - 1] << endl;
            PrintBoard();
            if (Inventory.isEmpty())
            {
                break;
            }
        }
        int max = 0;
        int Winner = 0;
        for (int i = 0; i < players; i++)
        {
            if (Score[i] > max)
            {
                max = Score[i];
                Winner = i;
            }
        }
        cout << "Winner is: " << Winner + 1 << endl;
    }
};
int main()
{
    Scrabble S;
    S.playGame();
}